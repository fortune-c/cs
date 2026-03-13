#include "../includes/Cache.h"
#include <stddef.h>
#include <string.h>

struct CacheLine;

void CacheSet_Init(CacheSet *set)
{
    if (set == NULL)
    {
        return;
    }

    SetWays((uint8_t)CACHE_WAYS);
    set->replacementAlgorithm = NULL;
}

void CacheSet_Destroy(CacheSet *set)
{
}

struct CacheLine *CacheSet_FindLine(CacheSet *set, uint32_t tag)
{
    if (set == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < CACHE_WAYS; i++)
    {
        if (set->lines[i].valid && set->lines[i].tag == tag)
        {
            return &set->lines[i];
        }
    }
    // cache line wasn't found
    return NULL;
}

struct CacheLine *CacheSet_ReplaceLine(CacheSet *set, uint32_t tag, uint8_t *sourceData)
{
    // choose a victom line to replace
    uint8_t victim = GetVictim();

    // set new cache line attributes
    set->lines[victim].tag = tag;
    set->lines[victim].valid = true;

    // copy 64 byte data from main memory to the cache line
    memcpy(set->lines[victim].data, sourceData, CACHE_LINE_SIZE);

    return &set->lines[victim];
}

void Cache_Init(Cache *cache, MainMemory *mainMemory)
{
    if (cache == NULL || mainMemory == NULL)
    {
        return;
    }

    cache->mainMemory = mainMemory;
}

uint32_t Cache_Read(Cache *cache, uint32_t address, MainMemory *mainMemory)
{
    if (cache == NULL)
    {
        return 0;
    }

    if (mainMemory == NULL)
    {
        mainMemory = cache->mainMemory;
    }

    if (mainMemory == NULL)
    {
        return 0;
    }

    AddressParts addressParts = AddressParts_FromAddress(address);

    // Find the requested cache line
    CacheLine *line = CacheSet_FindLine(&cache->sets[addressParts.setIndex], addressParts.tag);
    if (line != NULL)
    {
        // Cache hit: return the requested data from the cache line
        // Reinterpret the memory as a 32-bit integer
        uint32_t value;
        memcpy(&value, &line->data[addressParts.byteOffset], sizeof(value));
        return value;
    }
    else
    {
        // Cache miss: read the corresponding block from main memory and update the cache
        // Find the begining of the cache line
        uint32_t lineStart = address & ~(CACHE_LINE_SIZE - 1u);
        //Allocate data buffer
        uint8_t dataBuffer[CACHE_LINE_SIZE];
        // Read the cache line from main memory into the data buffer
        MainMemory_Read(mainMemory, lineStart, (uint8_t)CACHE_LINE_SIZE, dataBuffer);
        // Read the cache line in the set
        CacheLine *newLine = CacheSet_ReplaceLine(&cache->sets[addressParts.setIndex], addressParts.tag, dataBuffer);

        if (newLine == NULL)
        {
            return 0;
        }

        // Return 32-bit value from the cache line bytes
        uint32_t value;
        memcpy(&value, &newLine->data[addressParts.byteOffset], sizeof(value));
        return value;
    }
}

void Cache_Write(Cache *cache, uint32_t address, uint32_t data)
{
    if (cache == NULL)
    {
        return;
    }

    AddressParts addressParts = AddressParts_FromAddress(address);

    // Find the requested cache line
    CacheLine *line = CacheSet_FindLine(&cache->sets[addressParts.setIndex], addressParts.tag);
    if (line != NULL)
    {
        // Cache hit: write the data to the cache line
        memcpy(&line->data[addressParts.byteOffset], &data, sizeof(data));
    }
    else
    {
        // Cache miss: write the data directly to main memory
        MainMemory_Write(cache->mainMemory, address, sizeof(data), (uint8_t *)&data);
    }
}