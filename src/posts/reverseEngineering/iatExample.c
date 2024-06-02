#include <stdio.h>
#include <windows.h> // Include Windows API header for MessageBox function

int main() {
    // Call MessageBox function from user32.dll to display a message box
    MessageBox(NULL, "Hello, IAT!", "IAT Example", MB_OK);

    return 0;
}
