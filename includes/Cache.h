#ifndef CACHE_H
#define CACHE_H

#include <stdbool.h>

#include "MainMemory.h"
#include "Ra.h"

#define MEMOMRY_ADDRESS_SIZE 32u
#define CACHE_LINE_SIZE 64u
#define CACHE_SETS 64u
#define CACHE_WAYS 4u

#define CACHE_LINE_BYTE_OFFSET_SIZE 6u
#define CACHE_LINE_SET_INDEX_SIZE 6u
#define CACHE_LINE_TAG_SIZE 20u

typedef struct CacheLine {
    uint32_t tag;
    uint8_t data[CACHE_LINE_SIZE];
    bool valid;
} CacheLine;

typedef struct AddressParts {
    uint32_t tag;
    uint32_t setIndex;
    uint32_t byteOffset;

} AddressParts;

static inline AddressParts AddressParts_FromAddress(uint32_t address) {
    AddressParts parts;
    parts.byteOffset = address & (CACHE_LINE_SIZE - 1u);
    parts.setIndex = (address >> CACHE_LINE_BYTE_OFFSET_SIZE) & ((1u << CACHE_LINE_SET_INDEX_SIZE) - 1u);
    parts.tag = (address >> (CACHE_LINE_BYTE_OFFSET_SIZE + CACHE_LINE_SET_INDEX_SIZE)) & ((1u << CACHE_LINE_TAG_SIZE) - 1u);
    return parts;
}

typedef struct CacheSet {
    CacheLine lines[CACHE_WAYS]; // Array of cache lines in the set
    Ra* replacementAlgorithm; // Random Replacement algorithm for the set
} CacheSet;

void CacheSet_Init(CacheSet* set);
void CacheSet_Destroy(CacheSet* set);

struct CacheLine* CacheSet_FindLine(CacheSet* set, uint32_t tag);
struct CacheLine* CacheSet_ReplaceLine(CacheSet* set, uint32_t tag, uint8_t* sourceData);

typedef struct Cache {
    CacheSet sets[CACHE_SETS]; // Array of cache sets
    MainMemory* mainMemory; // Pointer to the main memory
} Cache;

void Cache_Init(Cache* cache, MainMemory* mainMemory);
uint32_t Cache_Read(Cache* cache, uint32_t address, MainMemory* mainMemory);
void Cache_Write(Cache* cache, uint32_t address, uint32_t data);

#endif /* CACHE_H */