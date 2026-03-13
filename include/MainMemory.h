//
// Created by fortune on 3/13/26.
//

#ifndef MAIN_MEMORY_H
#define MAIN_MEMORY_H

#include <stdint.h>

#define MAIN_MEMORY_SIZE (4 * 1024 * 1024)

typedef struct MainMemory MainMemory;

MainMemory* MainMemory_Create(void);
void MainMemory_Destroy(MainMemory* memory);

void MainMemory_Read(MainMemory* memory, uint32_t startAddress, uint8_t size, uint8_t* destination);
void MainMemory_Write(MainMemory* memory, uint32_t startAddress, uint8_t size, uint8_t* source);
void MainMemory_Print(const MainMemory* memory);

#endif /* MAIN_MEMORY_H */