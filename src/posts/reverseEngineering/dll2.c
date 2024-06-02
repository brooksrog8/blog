#include <stdio.h>
#include <windows.h>

// This function will be exported and called by the main executable
__declspec(dllexport) void print_three() {
    printf("Three is my number\n"); // Prints "Three" when called
}

// New function to print the number 3
__declspec(dllexport) void print_number_three() {
    printf("333333333333333333333333333333\n"); // Prints the number 3 when called
}

// Entry point for the DLL, called by the system when the DLL is loaded or unloaded
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    return TRUE; // Always returns TRUE, no specific initialization needed
}
