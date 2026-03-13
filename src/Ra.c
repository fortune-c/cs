#include "Ra.h"
#include <stdlib.h>

uint8_t ways = 0;

void SetWays(uint8_t numOfWays) {
    ways = numOfWays;
}

uint8_t GetVictim() {
    // Placeholder implementation for victim selection logic
    // In a real implementation, this would involve more complex logic based on the replacement policy
    return rand() % ways; // Return a dummy victim index for now
}

// ra also know as replacement algorithm determines which cache line to evict when a new line needs to be loaded into the cache. The "ways" variable represents the number of ways in a set-associative cache, and the GetVictim function is a placeholder for the actual victim selection logic based on the replacement policy being implemented.