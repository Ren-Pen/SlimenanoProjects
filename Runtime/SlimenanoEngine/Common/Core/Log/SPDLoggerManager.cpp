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
#include <ranges>

#include "SPDLogger.h"
#include "SPDLoggerManager.h"

namespace Slimenano::Core::Log {

using Base::Status;

class SPDLoggerManager::Impl {
    friend SPDLoggerManager;
    explicit Impl(SPDLoggerManager* pLoggerManager) : m_pInterface(pLoggerManager) {}
    ~Impl() {
        for (const auto& logger : m_loggers | std::views::values) {
            delete logger;
        }
        m_loggers.clear();
    };

    auto GetLogger(const char* name) -> ILogger* {
        if (name == nullptr) {
            return nullptr;
        }
        const auto sName = std::string(name);
        if (m_loggers.contains(sName)) {
            return m_loggers[sName];
        }
        const auto pLogger = new SPDLogger(name);
        m_loggers[sName] = pLogger;
        pLogger->SetLevel(m_defaultLevel);
        return pLogger;
    }

    auto FreeLogger(const ILogger* logger) -> Status {

        if (logger == nullptr) {
            return Status::NullPointerException(m_pInterface->GetModuleStatusCategory());
        }

        if (logger->GetName() == nullptr) {
            return Status::NullPointerException(m_pInterface->GetModuleStatusCategory());
        }

        if (const auto sName = std::string(logger->GetName()); m_loggers.contains(sName)) {
            if (m_loggers[sName] == logger) {
                m_loggers.erase(sName);
                delete logger;
                return Status::Success(m_pInterface->GetModuleStatusCategory());
            } else {
                return {m_pInterface->GetModuleStatusCategory(), Status::Code::NotPermitted, "Logger is not owner."};
            }
        }

        return {m_pInterface->GetModuleStatusCategory(), Status::Code::NotFound, "Logger not found."};
    }

    std::unordered_map<std::string, ILogger*> m_loggers = std::unordered_map<std::string, ILogger*>();
    SPDLoggerManager* m_pInterface = nullptr;
    ILogger::Level m_defaultLevel = ILogger::Level::Info;
};

SPDLoggerManager::SPDLoggerManager() : m_pImpl(new Impl(this)) {
}

SPDLoggerManager::~SPDLoggerManager() {
    delete m_pImpl;
}

auto SPDLoggerManager::GetLogger(const char* name) -> ILogger* {
    return m_pImpl->GetLogger(name);
}
auto SPDLoggerManager::FreeLogger(ILogger* logger) -> Status {
    return m_pImpl->FreeLogger(logger);
}
auto SPDLoggerManager::OnInit() -> Status {
    return Status::Success(Status::Category::Logger);
}
auto SPDLoggerManager::OnShutdown() -> Status {
    return Status::Success(Status::Category::Logger);
}
auto SPDLoggerManager::OnUpdate() -> Status {
    return Status::Success(Status::Category::Logger);
}
void SPDLoggerManager::SetDefaultLevel(const ILogger::Level& level) {
    m_pImpl->m_defaultLevel = level;
}
auto SPDLoggerManager::GetModuleName() const -> const char* {
    return "SPDLoggerManager";
}
} // namespace Slimenano::Core::Log
