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
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>

#include "SPDLogger.h"
#include "SPDLoggerManager.h"
#include "SlimenanoEngine/Core/Log/ILogger.h"

namespace Slimenano::Core::Log {

class SPDLoggerManager::Impl {
    friend SPDLoggerManager;
    explicit Impl(SPDLoggerManager* pLoggerManager) :
        m_pInterface(pLoggerManager) {}
    ~Impl() {
        std::unique_lock lock(m_mutex);
        m_loggers.clear();
    };

    auto GetLogger(const char* name) -> ILogger* {
        if (name == nullptr || *name == '\0') {
            return nullptr;
        }

        const auto sName = std::string(name);

        {
            std::shared_lock readLock(m_mutex);
            if (auto it = m_loggers.find(sName); it != m_loggers.end()) {
                return it->second.get();
            }
        }

        auto pLogger = std::make_unique<SPDLogger>(sName.c_str());

        {
            std::unique_lock lock(m_mutex);
            if (auto it = m_loggers.find(sName); it != m_loggers.end()) {
                return it->second.get();
            }

            pLogger->SetLevel(m_defaultLevel);
            auto [it, inserted] = m_loggers.emplace(sName, std::move(pLogger));

            return it->second.get();
        }
    }

    auto FreeLogger(ILogger* logger) -> Slimenano::Core::Base::Status {

        if (logger == nullptr) {
            return {
                m_pInterface->GetModuleStatusCategory(),
                Slimenano::Core::Base::Status::Code::InvalidParameter,
                "Cannot free a nullptr logger pointer"
            };
        }

        if (logger->GetName() == nullptr) {
            return {
                m_pInterface->GetModuleStatusCategory(),
                Slimenano::Core::Base::Status::Code::InvalidParameter,
                "Cannot free logger with nullptr name"
            };
        }

        const auto sName = std::string(logger->GetName());
        std::unique_lock lock(m_mutex);

        auto it = m_loggers.find(sName);
        if (it == m_loggers.end()) {
            return {
                m_pInterface->GetModuleStatusCategory(),
                Slimenano::Core::Base::Status::Code::NotFound,
                "Logger not found."
            };
        }

        if (it->second.get() != logger) {
            return {
                m_pInterface->GetModuleStatusCategory(),
                Slimenano::Core::Base::Status::Code::NotPermitted,
                "Logger is not owner."
            };
        }

        m_loggers.erase(it);
        return Slimenano::Core::Base::Status::Success(m_pInterface->GetModuleStatusCategory());
    }

    auto SetDefaultLevel(ILogger::Level level) -> void {
        std::unique_lock<std::shared_mutex> lock(m_mutex);
        m_defaultLevel = level;
    }

    std::unordered_map<std::string, std::unique_ptr<SPDLogger>> m_loggers =
        std::unordered_map<std::string, std::unique_ptr<SPDLogger>>();
    SPDLoggerManager* m_pInterface = nullptr;
    ILogger::Level m_defaultLevel = ILogger::Level::Info;
    mutable std::shared_mutex m_mutex;
};

SPDLoggerManager::SPDLoggerManager() :
    m_pImpl(new Impl(this)) {
}

SPDLoggerManager::~SPDLoggerManager() {
    delete m_pImpl;
}

auto SPDLoggerManager::GetLogger(const char* name) -> ILogger* {
    return m_pImpl->GetLogger(name);
}
auto SPDLoggerManager::FreeLogger(ILogger* logger) -> Slimenano::Core::Base::Status {
    return m_pImpl->FreeLogger(logger);
}
auto SPDLoggerManager::OnInit() -> Slimenano::Core::Base::Status {
    return Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Logger);
}
auto SPDLoggerManager::OnShutdown() -> Slimenano::Core::Base::Status {
    return Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Logger);
}
auto SPDLoggerManager::OnUpdate() -> Slimenano::Core::Base::Status {
    return Slimenano::Core::Base::Status::Success(Slimenano::Core::Base::Status::Category::Logger);
}
void SPDLoggerManager::SetDefaultLevel(const ILogger::Level& level) {
    m_pImpl->SetDefaultLevel(level);
}
auto SPDLoggerManager::GetModuleName() const -> const char* {
    return "SPDLoggerManager";
}
} // namespace Slimenano::Core::Log
