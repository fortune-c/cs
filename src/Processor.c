#include "../includes/Processor.h"
#include <stddef.h>

void Processor_Init(Processor* processor) {
    if (processor == NULL) {
        return;
    }

    Cache_Init(processor->cache, processor->mainMemory);
}

void Processor_Destroy(Processor* processor) {
    (void)processor;
    
}

uint32_t Processor_Read(Processor* processor, uint32_t address) {
    if (processor == NULL || processor->cache == NULL) {
        return 0;
    }

    return Cache_Read(processor->cache, address, processor->mainMemory);
}

void Processor_Write(Processor* processor, uint32_t address, uint32_t data) {
    if (processor == NULL || processor->cache == NULL) {
        return;
    }

    Cache_Write(processor->cache, address, data);
}

void Processor_PrintMainMemory(Processor* processor) {
    if (processor == NULL || processor->mainMemory == NULL) {
        return;
    }

    MainMemory_Print(processor->mainMemory);
}