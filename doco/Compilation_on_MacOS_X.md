<h1>Compiling decenttree on Mac OS X</h1>
(Note: These instructions have only been tested with Intel Macintoshes; they have not been tested with Apple Silicon).

<h2>Installing compile time dependencies</h2>
Decenttree's dependencies are the same, regardless of whether you intend to build it with XCode, the development environment 
provided by Apple, or with Visual Code, the development environment provided by Macintosh.

|Dependency|Comments|
|----------|--------|
| clang    | A C++ compiler that decenttree is built with ([pydecenttree](pydecenttree.md) may be built with gcc, another compiler, depending on how python is configured). Decenttree has been built with version 12 and may build with version 13 (as of yet it compiles, but does not link, with version 15 of the clang compiler). |
| gcc*     | (Alternative for clang). decenttree can be built with version 12.2 of gcc (and it may be possible to build decenttree with earlier versions, as it builds - even for 32-bit targets - with version 9.2 on Windows). |
| cmake    | A system for managing build processes,  independently of your choice of Operating System and compiler. decentree will not build with versions earlier than 3.18. On Mac OS, decenttree has most recently been built with version 3.24.2.  |
| libomp   | A library for supporting the use of [OpenMP](https://en.wikipedia.org/wiki/OpenMP), which decenttree uses for Operating-System-Independent parallel execution and multithreading.  More recent versions of the clang and gcc compilers have their own integrated OMP support. <br> (note: decenttree only makes use of OpenMP 2.0 features).
| python   | An interpreter for the Python programming language. It is only required if you wish to compile the pydecenttree Python extension module. |
| numpy    | A package for scientific computing in python.  It is only required if you wish to compile the pydecenttree Python extension module. |
| zlib | [zlib](https://en.wikipedia.org/wiki/Zlib) provides de-compression and compression, for reading and writing .gzip files.  decenttree includes zlib 1.2.7 (and you may either use the version that comes with decenttree, or the version installed on your operating system). 
| vcl | Agner Fogg's [VCL Vector Class Library](https://www.agner.org/optimize/vcl_manual.pdf) provides classes for vectorizing floating point and integer calculations (but for the Intel architecture only). Vectorized versions of distance matrix algorithms may run up to twice as fast as un-vectorized versions.

decenttree includes MacOS versions of the zlib and vectorclass libraries.

The easiest way to install each of the other components is with 
[homebrew](https://brew.sh). 

| Installation Command | Comment |
|----------------------|------------------|
| brew install cmake   | decenttree compilation has only been tested with cmake 3.20.1 and 3.24.1 |
| brew install libomp  | parallelization in decenttree has only been tested with libomp 14.0.6 |
| brew install python  | [pydecenttree](pydecenttree.md) compliation has only been tested with python 3.10 |
| brew install numpy   | [pydecenttree](pydecenttree.md) compilation has only been tested with numpy 1.23.1.1 |
| brew install gcc     | compilation has only been tested (on Intel Mac OS) with version 12.2 |

If you install more recent versions of the clang compiler (via homebrew)
it may be necessary to add compiler definitions to /Users/[me]/.local/share/CMakeTools/cmake-tools-kits.json 
to ensure that Microsoft Code can find the Clang compiler.
```
{ "name": "Clang 15.0.2",
  "compilers": {
    "C": "/usr/local/opt/llvm/bin/clang",
    "CXX": "/usr/local/opt/llvm/bin/clang++"
  },
  "keep": true
},
```

#                                   ... had to be added to
#                                   /Users/[me]/.local/share/CMakeTools/cmake-tools-kits.json
#                                   ... because Microsoft Code wasn't finding the compiler.

<h2>Compiling dcenttree with XCode</h2>
This section not written yet.
<h2>Compiling decenttree with Visual Code</h2>
