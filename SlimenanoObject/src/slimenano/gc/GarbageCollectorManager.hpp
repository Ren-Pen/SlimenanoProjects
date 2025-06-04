//
// Created by xzy54 on 25-6-2.
//
#pragma once
#ifndef SLIMENANO_GC_GARBAGE_COLLECTOR_MANAGER_H
#    define SLIMENANO_GC_GARBAGE_COLLECTOR_MANAGER_H
#    include <functional>
#    include <memory>
#    include <string>
#    include <unordered_map>
#    include <vector>

#    include "slimenano/gc/IGarbageCollector.hpp"

namespace slimenano {
namespace gc {
class GarbageCollectorManager {
  public:
    using GarbageCollectorFactoryFunc = std::function<auto()->std::unique_ptr<IGarbageCollector>>;
    class GarbageCollectorConfig;
    class GarbageCollectorFactory;
    static auto Initialize() -> void;
    static auto Initialize(GarbageCollectorConfig& config) -> void;
    static auto Initialize(GarbageCollectorConfig&& config) -> void;
    static auto RegisterFactory(const std::string& name, const GarbageCollectorFactoryFunc& factory) -> void;
    static auto AvailableGarbageCollectors() -> std::vector<std::string>;
    static auto GetGarbageCollector() -> IGarbageCollector&;
    static auto Release() -> void;

  private:
    static auto instance() -> std::unique_ptr<IGarbageCollector>&;
    static auto factories() -> std::unordered_map<std::string, GarbageCollectorFactoryFunc>&;
    GarbageCollectorManager() = default;
    ~GarbageCollectorManager() = default;
};

class GarbageCollectorManager::GarbageCollectorConfig {
  public:
    GarbageCollectorConfig() = default;
    ~GarbageCollectorConfig() = default;

    auto Get(const std::string& key) const -> std::string;
    auto Put(const std::string& key, const std::string& value) -> GarbageCollectorConfig&;
    auto Remove(const std::string& key) -> GarbageCollectorConfig&;

  private:
    std::unordered_map<std::string, std::string> m_config;
};
} // namespace gc
} // namespace slimenano

#endif // SLIMENANO_GC_GARBAGE_COLLECTOR_MANAGER_H
