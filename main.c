//
// Created by fortune on 3/13/26.
//

#include <stdio.h>

#include "includes/MemorySystem.h"

int main(void) {
    MemorySystem memorySystem;

    MemorySystem_Init(&memorySystem, NULL);

    // print a slice of the main memory (for debugging purposes)
    MainMemory_Print(memorySystem.mainMemory);

    // Expected: read from main memory at address 0x00 (64 bytes) the value 0x00
    uint32_t data_1 = MemorySystem_Read(&memorySystem, 0, 0x20);
    printf("Value: 0x%x\n", data_1);

    // Expected: read from cache address 0x20 the value 0x00
    data_1 = MemorySystem_Read(&memorySystem, 0, 0x20);
    printf("Value: 0x%x\n", data_1);

    // Expected: write to both cache and main memory (write-throug) the value 0x6139 at address 0x20
    MemorySystem_Write(&memorySystem, 0, 0x20, 0x6139);

    // Expected: read from cache the value 0x6139 at address 0x20
    uint32_t data_2 = MemorySystem_Read(&memorySystem, 0, 0x20);
    printf("Value: 0x%x\n", data_2);


    // Expected: write to both cache and main memory (write-through)
    MemorySystem_Write(&memorySystem, 0, 0x10, 0x12345678);
    MemorySystem_Write(&memorySystem, 0, 0x10, 0x77777777);
    MemorySystem_Write(&memorySystem, 0, 0x10, 0x52690723);

    // Expected: readfrom cache at address 0x10 the value 0x52690723
    uint32_t data3 = MemorySystem_Read(&memorySystem, 0, 0x10);
    printf("Value: 0x%x\n", data3);

    // Thrashing
    for (uint8_t i = 0; i < 4; i++){
        // Expected: first loop reads from main memory and updates cache
        // Second loop reads from cache only
        MemorySystem_Read(&memorySystem, 0, 0x0040);
        MemorySystem_Read(&memorySystem, 0, 0x1040);
        MemorySystem_Read(&memorySystem, 0, 0x2040);
        MemorySystem_Read(&memorySystem, 0, 0x3040);
        MemorySystem_Read(&memorySystem, 0, 0x4040); // Causes an eviction and cache miss (reads from main memory)
    }

    MainMemory_Print(memorySystem.mainMemory);

    MemorySystem_Destroy(&memorySystem);
    return 0;
}
