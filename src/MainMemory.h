//
// Created by fortune on 3/13/26.
//

#include <stdint.h>

#ifndef MAIN_MEMORY_H
#define MAIN_MEMORY_H

#include <stdint.h>
#include "SystemDefinitions.h"

// 1. The Class Data (State)
typedef struct {
    uint8_t* m_memory;
} MainMemory;

// 2. Lifecycle Functions (Constructor & Destructor)
MainMemory* MainMemory_Create(void);
void MainMemory_Destroy(MainMemory* instance);

// 3. Member Functions (Methods)
// Notice how we must pass `MainMemory* instance` as the first parameter to every function
DataPacket MainMemory_Read(MainMemory* instance, uint32_t startAddress);

DataBlock MainMemory_ReadBlock(MainMemory* instance, uint32_t startAddress);

// In C++, you passed `sourceData` by reference (&).
// Since C does not have references, we pass it by constant pointer (*).
void MainMemory_Write(MainMemory* instance, uint32_t startAddress, const DataPacket* sourceData);

#endif /* MAIN_MEMORY_H */