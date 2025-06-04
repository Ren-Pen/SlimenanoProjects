//
// Created by xzy54 on 25-6-2.
//

#include <stdexcept>
#include "slimenano/gc/GarbageCollectorManager.hpp"

namespace slimenano {
namespace gc {

auto GarbageCollectorManager::Initialize() -> void {
    GarbageCollectorManager::Initialize(GarbageCollectorConfig());
}

auto GarbageCollectorManager::Initialize(GarbageCollectorConfig&& config) -> void {
    GarbageCollectorManager::Initialize(config);
}

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
        config.Put("gc_type", gc_name);
        
        GetGarbageCollector().Start();
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to initialize garbage collector: \n" + std::string(e.what()));
    }
}

auto GarbageCollectorManager::RegisterFactory(const std::string& name, const GarbageCollectorFactoryFunc& factory) -> void {
    factories()[name] = factory;
}

auto GarbageCollectorManager::AvailableGarbageCollectors() -> std::vector<std::string> {
    std::vector<std::string> result;
    for (const auto& pair : factories()) {
        result.push_back(pair.first);
    }
    return result;
}

auto GarbageCollectorManager::GetGarbageCollector() -> IGarbageCollector& {
    auto& ptr = instance();
    if (!ptr) {
        throw std::runtime_error("Garbage collector not initialized");
    }
    return *ptr;
}

auto GarbageCollectorManager::Release() -> void{
    GetGarbageCollector().Shutdown();
}

auto GarbageCollectorManager::instance() -> std::unique_ptr<IGarbageCollector>& {
    static std::unique_ptr<IGarbageCollector> instance;
    return instance;
}
auto GarbageCollectorManager::factories() -> std::unordered_map<std::string, GarbageCollectorFactoryFunc>& {
    static std::unordered_map<std::string, GarbageCollectorFactoryFunc> factories;
    return factories;
}

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
