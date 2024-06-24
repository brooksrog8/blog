# Overview of PE File Structure for Reverse Engineering


Understanding the PE format is crucial for effective reverse engineering. It allows you to quickly identify entrypoints for dissasembled code and locations of key resources within the binary, this is very helpful for:
- analyzing the functiontality of a program's code
- identifying when data is allocated in a dump while manually unpacking
- Recognizing anti-analysis techniques
- Optimizing debugging workflows

And more.



Some  quick definitions
- Relative virtual address (RVA): An address relative to the address of the module
- Base address: The starting memory address where a memory module is loaded in virtual memory
- Virtual address (VA): Memory address used by a proces, providing an abstraction from physical memory addresses for efficient memory management. 

On a 32 bit operating system, each process is guaranteed 4gb of virtual memory, each process will have a memory address range of 0x00000000 to 0xFFFFFFFF.

Here is an example how a file appears on disk


![image-15](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-15.png
)


A VA for the PE file header here would be 0x00400108 in memory, 0x00400200 for .text, and so on. 


![image-18](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-18.png
)

Here is what a PE file looks like in a hex editor.

It starts with the "magic" MZ or 0x5A4D, these are the initials of the PE designer Mark Zbikowski.
This is important to remember because every exe will begin with this sequence, also  the E1fa at 0x40, which is a DWORD offset to a new PE header that includes PE\0\0.
![image-16](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-16.png
)





So for example this is how a .text section would look in IDA, the virtual address for sub_442214 here would be 00042214, and 00442215 would be the virtual address for the `mov edp, esp` line.

And for the Relative virtual address

 (RVA) = VA - Base address

So for sub_442214: 00442214 - 00400000 = 42214. 

A VA acts as a pointer within a specific memory space that doesn't direct association with physical memory addresses. Essentially a way for computers to keep track of where things are without worrying about the actual physical memory layout, this abstraction allows for efficient memory management for the OS performance and security. 

A couple file types that use the PE file format:
- .exe - executable
- .dll - dynamic link library

You'll mainly be analyzing these file types when reverse engineering. 

A quick explanation of the other sections

- .text: Where the executable code or instructions that the processor executes reside.
- .rdata: Holds read-only data, like constant strings and compiler-generated constants.
- .data: Stores initialized global data and static types.
- .rsrc: Contairces like icons, dialog boxes, and version info. 
ns resou
## Import Address Table (IAT)

The IAT is a lookup table used when the application is calling functions in a different module.

So when we reference `MessageBox` symbolically in the C code below below, when compiling and linking they recognize that `MessageBox` is provided by the `USER32.dll` module of the Windows API. Then, during runtime, it dynamically links them together. 

<details>
  <summary>Show C code example</summary>
  <pre><code class="language-c">

#include <stdio.h>
#include <windows.h>

int main() {
    // call MessageBox function from user32.dll to display a message box
    MessageBox(NULL, "IAT example", "IAT Example", MB_OK);

    return 0;
}
  </code></pre>

</details>
<details>
  <summary>Show C++ code example</summary>
  <pre><code class="language-cpp">

#include <windows.h> 

int main() {
    // Call MessageBox function from user32.dll to display a message box
    MessageBox(NULL, "Hello, IAT!", "IAT Example", MB_OK);

    return 0;
}

  </code></pre>
</details>



Now looking at our IAT in PE-Bear:


![image-20](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-20.png
)


As you can see the result is an entry for `user32.dll` being added to the IAT of the exe. 

Now in IDA searching for `MessageBox` in our imports:


![image-23](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-23.png
)

![image-22](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-22.png
)

Then we can find our function here in the `.data` section, where the IAT is typically located.

And same for the `export address table`


<details>
  <summary>Show C code example of a dll export</summary>
  <pre><code class="language-c">

#include <stdio.h>
#include <windows.h>

// This function will be exported and called by the main executable
__declspec(dllexport) void print_two() {
    printf("Two is my number\n"); 
}

// function to print the number 2
__declspec(dllexport) void print_number_two() {
    printf("2\n"); 
}

// Entry point for the DLL, called by the system when the DLL is loaded or unloaded
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    return TRUE;
}

  </code></pre>



</details>



![image-24](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-24.png
)


![image-26](https://raw.githubusercontent.com/brooksrog8/blog/master/pics/image-26.png
)

### Significance of IAT/EAT in Reverse Engineering
In a typical reverse engineering process, it's a good practice to first check the `imports/exports` of the app to see if there's anything notable.

It's a good idea to do this because it helps reverse engineers understand the functionality and behavior of the program, provide insights into a programs external depencdencies, and it's interaction with external libraries. 


While this overview scratches the surface, the intracacies of PE file structure can go deeper from deciphering encrypted payloads to unraveling complex anti-analysis measures, this is all I wanted to write about today. 

We will uncover more PE concepts and other computer security topics later.
