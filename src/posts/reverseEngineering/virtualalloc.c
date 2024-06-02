#include <stdio.h>
#include <Windows.h>

int main() {
    // Define the size of the memory block to allocate
    SIZE_T size = 4096; // 4KB

    printf("Size of the memory block to allocate: %d\n", size);

    // Allocate a region of memory
    LPVOID memory = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    
    printf("address where memory block is located in memory: %d\n", memory);
    if (memory != NULL) {
        // Memory allocation successful
        printf("Memory allocated successfully at address: %d\n", memory);
        
        // Write some data to the allocated memory
        char* data = "Hello, VirtualAlloc!";
        memcpy(memory, data, strlen(data) + 1);
        
        // Read and print the data from the allocated memory
        printf("Data from allocated memory: %s\n", (char*)memory);
        
        // Free the allocated memory
        VirtualFree(memory, 0, MEM_RELEASE);
        printf("Memory freed successfully.\n");
    } else {
        // Memory allocation failed
        fprintf(stderr, "Failed to allocate memory.\n");
    }

    // Additional print statements
    printf("End of program.\n");

    return 0;
}
