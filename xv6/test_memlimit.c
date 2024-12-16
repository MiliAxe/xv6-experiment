#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) {
    int alloc_val = 510 * sizeof(char); // Allocate 510 bytes

    printf(1, "------------------------------------------\n");

    // Set memory quota to 1024 bytes
    if (set_mem_limit(1024) >= 0)
        printf(1, "Memory limit set to 1024 bytes.\n");
    else
        printf(1, "Memory limit could not be set.\n");

    // Allocate memory and test enforcement
    if (malloc(alloc_val))
        printf(1, "%d bytes were allocated.\n", alloc_val);
    else
        printf(1, "Allocation failed at %d bytes.\n", alloc_val);

    if (malloc(alloc_val))
        printf(1, "%d bytes were allocated.\n", alloc_val);
    else
        printf(1, "Allocation failed at %d bytes.\n", alloc_val);

    // This allocation should fail due to the memory quota
    if (malloc(alloc_val))
        printf(1, "%d bytes were allocated (unexpected).\n", alloc_val);
    else
        printf(1, "Allocation failed as expected (quota exceeded).\n");

    // printf(1, "------------------------------------------\n");

    exit();
}