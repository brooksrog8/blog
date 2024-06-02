#include <stdio.h>
#include <windows.h>

// This function will be exported and called by the main executable
__declspec(dllexport) void print_two() {
    printf("Two is my number\n"); // Prints "Two" when called
}

// New function to print the number 2
__declspec(dllexport) void print_number_two() {
    printf("222222222222222222\n"); // Prints the number 2 when called
}

// Entry point for the DLL, called by the system when the DLL is loaded or unloaded
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    return TRUE; // Always returns TRUE, no specific initialization needed
}
