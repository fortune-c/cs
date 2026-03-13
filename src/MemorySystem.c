#include <stddef.h>
#include <stdlib.h>

#include "../includes/MemorySystem.h"

void MemorySystem_Init(MemorySystem* memorySystem, const CacheConfiguration* cacheConfiguration)
{
    if (memorySystem == NULL) {
        return;
    }

    (void)cacheConfiguration;

    memorySystem->cacheDetailedStatistics = NULL;

    memorySystem->mainMemory = MainMemory_Create();
    if (memorySystem->mainMemory == NULL) {
        memorySystem->cache = NULL;
        return;
    }

    memorySystem->cache = (Cache*)malloc(sizeof(Cache));
    if (memorySystem->cache == NULL) {
        MainMemory_Destroy(memorySystem->mainMemory);
        memorySystem->mainMemory = NULL;
        return;
    }

    Cache_Init(memorySystem->cache, memorySystem->mainMemory);
}

void MemorySystem_Destroy(MemorySystem* memorySystem)
{
    if (memorySystem == NULL) {
        return;
    }

    free(memorySystem->cache);
    memorySystem->cache = NULL;

    MainMemory_Destroy(memorySystem->mainMemory);
    memorySystem->mainMemory = NULL;

    memorySystem->cacheDetailedStatistics = NULL;
}

uint32_t MemorySystem_Read(MemorySystem* memorySystem, size_t id, uint32_t address)
{
    (void)id;

    if (memorySystem == NULL || memorySystem->cache == NULL || memorySystem->mainMemory == NULL) {
        return 0u;
    }

    uint32_t alignedAddress = address;

    if (!MemorySystem_IsAligned(memorySystem, address)) {
        alignedAddress = MemorySystem_AlignMemoryAddress(memorySystem, address);
    }

    return Cache_Read(memorySystem->cache, alignedAddress, memorySystem->mainMemory);
}

void MemorySystem_Write(MemorySystem* memorySystem, size_t id, uint32_t address, uint32_t value)
{
    (void)id;

    if (memorySystem == NULL || memorySystem->cache == NULL) {
        return;
    }

    uint32_t alignedAddress = address;

    if (!MemorySystem_IsAligned(memorySystem, address)) {
        alignedAddress = MemorySystem_AlignMemoryAddress(memorySystem, address);
    }

    Cache_Write(memorySystem->cache, alignedAddress, value);
}

const CacheDetailedStatistics* MemorySystem_GetCacheDetailedStatistics(const MemorySystem* memorySystem)
{
    if (memorySystem == NULL) {
        return NULL;
    }

    return memorySystem->cacheDetailedStatistics;
}

bool MemorySystem_IsAligned(const MemorySystem* memorySystem, uint32_t address)
{
    (void)memorySystem;
    return (address & ADDRESS_ALIGNMENT_BITS) == 0u;
}

uint32_t MemorySystem_AlignMemoryAddress(const MemorySystem* memorySystem, uint32_t address)
{
    (void)memorySystem;
    return address & ~(ADDRESS_ALIGNMENT_BITS);
}