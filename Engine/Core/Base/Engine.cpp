#include "Engine.h"

#include "IApplication.h"
#include "../Provider/ProviderManager.h"

auto slimenano::Engine::GetInstance() -> Engine& {
    static Engine instance;
    return instance;
}

auto slimenano::Engine::Initialize() -> void {
    auto& pm = ProviderManager::GetInstance();
    auto& p_App = pm.GetProvider<IApplication>();
    const auto app = p_App.provide();
    app->Initialize();
}
