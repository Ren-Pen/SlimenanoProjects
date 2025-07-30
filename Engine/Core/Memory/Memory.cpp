#include "Memory.h"

#include "../Provider/ProviderManager.h"

namespace slimenano {

std::unique_ptr<IMemoryManager> Memory::m_MemoryManager = nullptr;

auto Memory::Initialize() -> void {
    if (const auto providerPtr = ProviderManager::GetProvider<IMemoryManager>(); providerPtr != nullptr) {
        m_MemoryManager = providerPtr->Provide();
    }
}

auto Memory::Malloc(size_t size, size_t alignment) -> void* {
    return m_MemoryManager->Malloc(size, alignment);
}

auto Memory::Free(void* ptr) -> void {
    m_MemoryManager->Free(ptr);
}

} // namespace slimenano
