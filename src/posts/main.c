#include <stdio.h>
#include <windows.h>

// Typedef for the function pointers to the functions in the DLLs
typedef void (*print_func)();

int main() {
    HINSTANCE hDll1, hDll2; // Handles for the loaded DLLs
    print_func print_two, print_number_two, print_three, print_number_three; // Function pointers for the DLL functions

    // Print from the main executable
    printf("One is my number\n"); // Prints "One" from the main executable

    // Load the first DLL (dll1.dll)
    hDll1 = LoadLibrary("dll1.dll");
    if (hDll1 == NULL) {
        printf("Could not load dll1.dll\n");
        return 1; // Exit if the DLL cannot be loaded
    }

    // Load the second DLL (dll2.dll)
    hDll2 = LoadLibrary("dll2.dll");
    if (hDll2 == NULL) {
        printf("Could not load dll2.dll\n");
        FreeLibrary(hDll1); // Free the first DLL before exiting
        return 1; // Exit if the DLL cannot be loaded
    }

    // Get the address of the print_two function from dll1.dll
    print_two = (print_func)GetProcAddress(hDll1, "print_two");
    // Get the address of the print_number_two function from dll1.dll
    print_number_two = (print_func)GetProcAddress(hDll1, "print_number_two");
    // Get the address of the print_three function from dll2.dll
    print_three = (print_func)GetProcAddress(hDll2, "print_three");
    // Get the address of the print_number_three function from dll2.dll
    print_number_three = (print_func)GetProcAddress(hDll2, "print_number_three");

    // Check if the functions were successfully located
    if (!print_two || !print_number_two || !print_three || !print_number_three) {
        printf("Could not locate functions\n");
        FreeLibrary(hDll1); // Free the first DLL
        FreeLibrary(hDll2); // Free the second DLL
        return 1; // Exit if the functions cannot be found
    }

    // Call the functions from the DLLs
    // Skip print_two() and print_three() calls as requested
    print_number_two(); // Call the function from dll1.dll to print the number 2
    print_number_three(); // Call the function from dll2.dll to print the number 3

    // Free the loaded DLLs
    FreeLibrary(hDll1); // Free the first DLL
    FreeLibrary(hDll2); // Free the second DLL

    return 0; // Exit the program
}
