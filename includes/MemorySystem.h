#ifndef MEMORY_SYSTEM_H
#define MEMORY_SYSTEM_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "MainMemory.h"
#include "Cache.h"

#define ADDRESS_ALIGNMENT_BITS 0x03u

typedef struct CacheConfiguration CacheConfiguration;
typedef struct CacheDetailedStatistics CacheDetailedStatistics;

typedef struct MemorySystem {
	MainMemory* mainMemory;
	Cache* cache;
	CacheDetailedStatistics* cacheDetailedStatistics;
} MemorySystem;

void MemorySystem_Init(MemorySystem* memorySystem, const CacheConfiguration* cacheConfiguration);
void MemorySystem_Destroy(MemorySystem* memorySystem);

uint32_t MemorySystem_Read(MemorySystem* memorySystem, size_t id, uint32_t address);
void MemorySystem_Write(MemorySystem* memorySystem, size_t id, uint32_t address, uint32_t value);

const CacheDetailedStatistics* MemorySystem_GetCacheDetailedStatistics(const MemorySystem* memorySystem);

bool MemorySystem_IsAligned(const MemorySystem* memorySystem, uint32_t address);
uint32_t MemorySystem_AlignMemoryAddress(const MemorySystem* memorySystem, uint32_t address);

#endif /* MEMORY_SYSTEM_H */
