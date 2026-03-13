//
// Created by fortune on 3/13/26.
//

#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "Cache.h"



typedef struct Processor {
    MainMemory* mainMemory; // Pointer to the main memory
    Cache* cache; // Pointer to the cache
} Processor;

void Processor_Init(Processor* processor);
void Processor_Destroy(Processor* processor);

uint32_t Processor_Read(Processor* processor, uint32_t address);
void Processor_Write(Processor* processor, uint32_t address, uint32_t data);
void Processor_PrintMainMemory(Processor* processor);


#endif /* PROCESSOR_H */