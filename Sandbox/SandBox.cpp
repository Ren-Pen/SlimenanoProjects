/*
Slimenano Engine
    Copyright (C) 2025  zyu.xiao

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include "SlimenanoEngine/Core/Base/Status.h"
#include <SlimenanoEngine/Common/Core/Log/SPDLoggerManager.h>
#include <SlimenanoEngine/Core/Base/Result.h>
#include <cmath>
#include <iostream>
#include <windows.h>
#include <glad/gl.h>
#include <glad/wgl.h>

// #include "SandBoxApplication.h"
// #include "SandBoxLoggerManager.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 vColor;

uniform mat4 uMVP;

void main() {
    vColor = aColor;
    gl_Position = uMVP * vec4(aPos, 1.0);
}
)";

const char* fragmentShaderSrc = R"(
#version 330 core
in vec3 vColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(vColor, 1.0);
}
)";

GLuint compileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info[512];
        glGetShaderInfoLog(shader, 512, nullptr, info);
        std::cerr << "Shader compile error: " << info << std::endl;
    }
    return shader;
}

GLuint createProgram(const char* vs, const char* fs) {
    GLuint v = compileShader(GL_VERTEX_SHADER, vs);
    GLuint f = compileShader(GL_FRAGMENT_SHADER, fs);
    GLuint prog = glCreateProgram();
    glAttachShader(prog, v);
    glAttachShader(prog, f);
    glLinkProgram(prog);
    glDeleteShader(v);
    glDeleteShader(f);
    return prog;
}

struct Mat4 {
    float m[16];
};
Mat4 identity() {
    Mat4 r{};
    for (int i = 0; i < 16; i++) r.m[i] = (i % 5 == 0) ? 1.f : 0.f;
    return r;
}
Mat4 perspective(float fovy, float aspect, float nearZ, float farZ) {
    Mat4 r{};
    float t = tanf(fovy * 0.5f * 3.14159f / 180.f);
    r.m[0] = 1.f / (aspect * t);
    r.m[5] = 1.f / t;
    r.m[10] = -(farZ + nearZ) / (farZ - nearZ);
    r.m[11] = -1.f;
    r.m[14] = -(2.f * farZ * nearZ) / (farZ - nearZ);
    return r;
}
Mat4 rotateY(float angle) {
    Mat4 r = identity();
    r.m[0] = cosf(angle); r.m[2] = sinf(angle);
    r.m[8] = -sinf(angle); r.m[10] = cosf(angle);
    return r;
}
Mat4 translate(float x, float y, float z) {
    Mat4 r = identity();
    r.m[12] = x; r.m[13] = y; r.m[14] = z;
    return r;
}
Mat4 mul(const Mat4& a, const Mat4& b) {
    Mat4 r{};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            r.m[i + j*4] =
                a.m[0+i]*b.m[j*4+0] +
                a.m[4+i]*b.m[j*4+1] +
                a.m[8+i]*b.m[j*4+2] +
                a.m[12+i]*b.m[j*4+3];
        }
    }
    return r;
}

auto main(const int argc, const char** argv) -> int {

    auto result = Slimenano::Core::Base::Result<int>(
        Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Application),
        10
    );

    if (result.IsSuccess()){
        std::cout << "Success" << std::endl;
        if (result.HasValue()){
            std::cout << result.GetValue() << std::endl;
        }
    }else{
        std::cout << "Failure:" << result.GetStatus().GetCode() << std::endl;
    }

    // auto engine = Slimenano::Core::Engine::Engine();

    // auto loggerManager = Slimenano::Core::Log::SPDLoggerManager();
    // std::cout << loggerManager.GetModuleName() << " " << engine.Install(&loggerManager).GetState() << std::endl;

    // auto sandboxLoggerManager = Slimenano::SandBox::SandBoxLoggerManager();
    // std::cout << sandboxLoggerManager.GetModuleName() << " " << engine.Install(&sandboxLoggerManager).GetState() << std::endl;

    // auto sandbox = Slimenano::SandBox::SandBoxApplication();
    // std::cout << engine.Install(&sandbox).GetState() << std::endl;

    // engine.Start();

    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "WglDemo";
    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        "WglDemo",
        "WGL Demo",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    HDC hdc = GetDC(hwnd);

    PIXELFORMATDESCRIPTOR pfd = {
        .nSize = sizeof(pfd),
        .nVersion = 1,
        .dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        .iPixelType = PFD_TYPE_RGBA,
        .cColorBits = 32
    };

    int pf = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pf, &pfd);

    HGLRC hglrc = wglCreateContext(hdc);
    if (!hglrc) {
        std::cerr << "Failed to create OpenGL context" << std::endl;
        return -1;
    }
    wglMakeCurrent(hdc, hglrc);

    if (!gladLoaderLoadGL()) {
        std::cerr << "Failed to initialize GLAD OpenGL loader!" << std::endl;
        return -1;
    }

    if (!gladLoaderLoadWGL(hdc)) {
        std::cerr << "Failed to initialize GLAD WGL loader!" << std::endl;
        return -1;
    }

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    ShowWindow(hwnd, SW_SHOW);

    glEnable(GL_DEPTH_TEST);

float vertices[] = {
        // positions          // colors
        -1,-1, 1,   1,0,0,
         1,-1, 1,   0,1,0,
         1, 1, 1,   0,0,1,
        -1, 1, 1,   1,1,0,
        -1,-1,-1,   1,0,1,
         1,-1,-1,   0,1,1,
         1, 1,-1,   1,1,1,
        -1, 1,-1,   0,0,0
    };
    unsigned int indices[] = {
        0,1,2, 2,3,0,  // front
        4,5,6, 6,7,4,  // back
        0,4,7, 7,3,0,  // left
        1,5,6, 6,2,1,  // right
        3,2,6, 6,7,3,  // top
        0,1,5, 5,4,0   // bottom
    };
GLuint vao,vbo,ebo;
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glGenBuffers(1,&ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    GLuint program = createProgram(vertexShaderSrc,fragmentShaderSrc);
    glUseProgram(program);

    int uMVP = glGetUniformLocation(program,"uMVP");

    float angle = 0.0f;
    const float angularSpeed = 30.0f * 3.14159f / 180.0f; // 30°/s 转成弧度
    const double frameTime = 1.0 / 60.0; // 60 fps

    LARGE_INTEGER freq, prev, now;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&prev);

    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            // 时间计算
            QueryPerformanceCounter(&now);
            double deltaTime = double(now.QuadPart - prev.QuadPart) / freq.QuadPart;
            prev = now;

            // 更新角度（弧度）
            angle += angularSpeed * (float)deltaTime;
            if (angle > 2 * 3.14159f) angle -= 2 * 3.14159f;

            // 清屏 & 绘制
            glClearColor(0.1f,0.2f,0.3f,1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            Mat4 proj = perspective(45.0f, 800.f/600.f, 0.1f, 100.f);
            Mat4 view = translate(0,0,-6);
            Mat4 model = rotateY(angle);
            Mat4 mvp = mul(proj,mul(view,model));

            glUniformMatrix4fv(uMVP,1,GL_FALSE,mvp.m);

            glBindVertexArray(vao);
            glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);

            SwapBuffers(hdc);

            // 帧率控制 (Sleep 剩余时间)
            QueryPerformanceCounter(&now);
            double frameElapsed = double(now.QuadPart - prev.QuadPart) / freq.QuadPart;
            double sleepTime = frameTime - frameElapsed;
            if (sleepTime > 0) {
                Sleep(DWORD(sleepTime * 1000));
            }
        }
    }

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hglrc);
    ReleaseDC(hwnd, hdc);
    DestroyWindow(hwnd);

    return 0;
}
