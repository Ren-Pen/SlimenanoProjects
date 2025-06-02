//
// Created by xzy54 on 25-6-2.
//

#include <stdexcept>
#include "slimenano/gc/GarbageCollectorManager.hpp"

namespace slimenano {
namespace gc {

auto GarbageCollectorManager::Initialize(GarbageCollectorConfig& config) -> void {
    if (AvailableGarbageCollectors().empty()) {
        throw std::runtime_error("No available garbage collector.");
    }
    const auto gc_type = config.Get("gc_type");

    auto iterator = factories().begin();

    if (!gc_type.empty()) {
        iterator = factories().find(gc_type);
    }

    const auto& gc_name = iterator->first;
    const auto& gc_factory = iterator->second;
    try {
        instance() = gc_factory();
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to create garbage collector: \n" + std::string(e.what()));
    }
    config.Put("gc_type", gc_name);

}

auto GarbageCollectorManager::RegisterFactory(const std::string& name, const GarbageCollectorFactoryFunc& factory) -> void {
    factories()[name] = factory;
}

auto GarbageCollectorManager::AvailableGarbageCollectors() -> std::vector<std::string> {
    std::vector<std::string> result;
    for (const auto& [name, _] : factories()) {
        result.push_back(name);
    }
    return result;
}
auto GarbageCollectorManager::instance() -> std::unique_ptr<IGarbageCollector>& {
    static std::unique_ptr<IGarbageCollector> instance;
    return instance;
}
auto GarbageCollectorManager::factories() -> std::unordered_map<std::string, GarbageCollectorFactoryFunc>& {
    static std::unordered_map<std::string, GarbageCollectorFactoryFunc> factories;
    return factories;
}

GarbageCollectorManager::GarbageCollectorConfig::GarbageCollectorConfig() : m_config() {
}

GarbageCollectorManager::GarbageCollectorConfig::GarbageCollectorConfig(const GarbageCollectorConfig& other) = default;

GarbageCollectorManager::GarbageCollectorConfig::GarbageCollectorConfig(GarbageCollectorConfig&& other) noexcept : m_config(std::move(other.m_config)) {
}

auto GarbageCollectorManager::GarbageCollectorConfig::operator=(const GarbageCollectorConfig& other) -> GarbageCollectorConfig& {
    if (this == &other) {
        return *this;
    }
    m_config = other.m_config;
    return *this;
}

auto GarbageCollectorManager::GarbageCollectorConfig::operator=(GarbageCollectorConfig&& other) noexcept -> GarbageCollectorConfig& {
    if (this == &other) {
        return *this;
    }
    m_config = std::move(other.m_config);
    return *this;
}

GarbageCollectorManager::GarbageCollectorConfig::~GarbageCollectorConfig() = default;

auto GarbageCollectorManager::GarbageCollectorConfig::Get(const std::string& key) const -> std::string {
    const auto value_iter = m_config.find(key);
    if (value_iter == m_config.end()) {
        return "";
    }
    return value_iter->second;
}

auto GarbageCollectorManager::GarbageCollectorConfig::Put(const std::string& key, const std::string& value) -> GarbageCollectorConfig& {
    m_config[key] = value;
    return *this;
}

auto GarbageCollectorManager::GarbageCollectorConfig::Remove(const std::string& key) -> GarbageCollectorConfig& {
    m_config.erase(key);
    return *this;
}

} // namespace gc
} // namespace slimenano
