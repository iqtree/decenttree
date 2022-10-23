<h1>Compiling decenttree on Windows</h1>
The easiest way to build decenttree is with Microsoft Visual Studio 2022 (Community Edition). It should be possible to build 32-bit or 64-bit versions (but 64-bit builds are recommended).

<h2>Compiling using Visual Studio</h2>
decenttree has been built with Visual Studio 2017, 2019, and 2022. If you have Visual Studio (Community Edition) installed, this is the easiest way to build decenttree on Windows. [todo: explain how - it boils down to "point VS at the github repository and build!" but more detail would be good.]
<h3>Compiling using Visual Studio and Clang</h3>
<br>

<h2>Compiling using Microsoft Code</h2>

You may need to download Ninja to get Clang and GCC builds to work, by downloading a recent version from the official Ninja website, and put that somewhere in your path (one of the folders listed by the PATH environment variable).

<h3>Compiling with Microsoft Code and Clang</h3>
[todo: this bit not written yet.  There are two different ways to do this, one where you build with a version of Clang that mimics the Microsoft C++ Compiler (badly), using the Microsoft include folders, and another where you build with a MingW version of Clang running in a pretend Linux environment, with its own include folders and Open MP libraries.  I can't 
recommend either option! I had serious problems getting the Open MP libraries to link, and worse problems getting the vectorization to work!]
<br><br>

<h3>Compiling with Microsoft Code and GCC</h3>
<h4>Compiling with Microsoft Code and GCC 9.2</h4>
Building decenttree on Windows with GCC 9.2 is not recommended.
The compiler may not be installed with the OpenMP libraries that are needed (the problematic files are libgomp.a, libgomp.dll.a, libgomp.spec), which may may linking difficult.
<br><br>
<h4>Compiling with Microsoft Code and GCC 12.2</h4>
At present (October 2022), the version of CMake that MS Code uses (3.23 or 3.24) doesn't automatically recognize the compiler.
Builds may fail outright (with no error messages), due to missing DLLs (libisl-23.dll, for example) (the version number might vary). If you are installing GCC using MSYS2 and pacman you may find it necessary to copy files from c:\msys64\user\bin (where pacman puts them!) into c:\msys64\mingw64\bin (which is where pacman probably should put them, but might not).
<br><br>
<h4>Compiling with Microsoft Code and the Visual Studio Compiler</h4>
[todo: this bit not written yet]

