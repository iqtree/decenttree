<h1>Code examples for decenttree</h1>
<h2>List of files</h2>

|File|Content|
|----|-------|
| headeronlydecenttree.cpp | This example shows how to use decent tree as a header-only library. |
| vectordecenttree.cpp | This example shows how to use one of decenttree's vectorized neighbour-joining algorithms (the vectorisation only works on Intel hardware) |
| examplematrix.h<br>examplematrix.cpp | These two files define the example distance matrix that is used by headeronlydecenttree.cpp and vectordecenttree.cpp
| fakevector.h<br>differentvector.cpp | These files illustrate how you could use a _different_ vector class implementation (on non-Wintel hardware) with decenttree. fakevector.h shows what member functions a class must support, if it is to be used to specialize the vectorized neighbour-joining algorithms in the decenttree library. |
 