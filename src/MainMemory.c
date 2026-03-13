//
// Created by fortune on 3/13/26.
//

#include "MainMemory.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct MainMemory {
    uint8_t* m_memory;
};

MainMemory* MainMemory_Create(void) {
    MainMemory* instance = (MainMemory*)malloc(sizeof(MainMemory));
    if (instance == NULL) {
        return NULL;
    }

    // calloc handles both the allocation AND the zero-fill in one step
    instance->m_memory = (uint8_t*)calloc(MAIN_MEMORY_SIZE, sizeof(uint8_t));
    if (instance->m_memory == NULL) {
        free(instance);
        return NULL;
    }

    return instance;
}

void MainMemory_Destroy(MainMemory* memory) {
    if (memory != NULL) {
        free(memory->m_memory);
        memory->m_memory = NULL;
        free(memory);
    }
}

void MainMemory_Read(MainMemory* memory, uint32_t startAddress, uint8_t size, uint8_t* destination) {
    printf("Reading from main memory (address: 0x%x)\n", startAddress);
    // Read the requested amount of memory and copy to destination
    memcpy(destination, &memory->m_memory[startAddress], size);
}

void MainMemory_Write(MainMemory* memory, uint32_t startAddress, uint8_t size, uint8_t* source) {
    printf("Writing to main memory (address: 0x%x)\n", startAddress);
    // copy the requested amount of memory from the source main memory
    memcpy(&memory->m_memory[startAddress], source, size);
}

void MainMemory_Print(const MainMemory* memory) {
    // print a slice of memory region (for debugging purposes)
    const uint32_t ROWS = 24;
    const uint32_t COLS = 12;

    if (memory == NULL || memory->m_memory == NULL) {
        return;
    }

    for (uint32_t row = 0; row < ROWS; row++){
        for (uint32_t col = 0; col < COLS; col++){
            uint32_t index = row * COLS + col;
            printf("0x%02x\t", memory->m_memory[index]);
        }
        printf("\n");
    }
    printf("\n");
    for (uint32_t dash = 0; dash < 80; dash++){
        printf("-\t");
    }
    printf("\n");
    
}