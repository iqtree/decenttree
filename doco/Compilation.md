<h1>Compiling decenttree</h1>
<h2>Supported operating systems</h2>
The decenttree command-line application can be built under Windows (using Microsoft Visual Studio or Clang, or GCC, with Microsoft Code), on Intel Macintosh (with Clang, or GCC), or on Linux (using GCC).
As yet, it does not build (M1/M2) Apple Silicon.
 

| Operating System | Hardware | For             | You may need to |
| ---------------- | -------- | --------------- | ---------- |
| Macintosh        | 64-bit   | Parallelization | Link with libmac/libomp.a |
| Unix/Linux       | 64-bit   | Parallelization | Link with lib/libomp.a or lib/libomp.a |
| Unix/Linux.      | 32-bit   | Parallelization | Link with lib32/libomp.a |
| Windows          | 64-bit   | Parallelization | Ensure that lib/libiomp5md.dll is in a folder in the PATH (if building with Microsoft Visual Studio)|
| Windows          | 32-bit   | Parallelization | Ensure that lib32/libiomp5md.dll and lib32/libiomp5md.lib.dll are in the PATH (if building with Microsoft Visual Studio) |

<h2>Compiling on specific operating systems</h2>
Instructions are (or will shortly be) available for compilying pydecenttree on the following operating systems:

 - [Macintosh OS X](Compilation_on_MacOS_X.md)
 - [Linux](Compilation_on_Linux.md)
 - [Windows](Compilation_on_Windows.md)


