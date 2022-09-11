<h2>Compiling decenttree</h2>
The decenttree command-line application can be built under Windows (using Microsoft Visual Studio),
on Macintosh, or on Linux (using GCC).  It hasn't been tested with other compilers.

| Operating System | Hardware | For             |            |
| ---------------- | -------- | --------------- | ---------- |
| Macintosh        | 64-bit   | Parallelization | Link with libmac/libomp.a |
| Unix/Linux       | 64-bit   | Parallelization | Link with lib/libomp.a or lib/libomp.a |
| Unix/Linux.      | 32-bit   | Parallelization | Link with lib32/libomp.a |
| Windows          | 64-bit   | Parallelization | Ensure that lib/libiomp5md.dll is in a folder in the PATH |
| Windows          | 32-bit   | Parallelization | Ensure that lib32/libiomp5md.dll and lib32/libiomp5md.lib.dll are in the PATH |

