DecentTree
==========

Introduction
------------

DecentTree is a cross-platform command-line program and also a C++ library for 
inferring phylogenetic trees (in newick format) from distance matrices (supplied in 
phylip distance matrix formats), or alignments (supplied in fasta format), 
using well-known algorithms, such as Neighbour Joining, BIONJ and UPGMA.

If you use DecentTree in a publication, please cite:

> W. Wang, J. Barbetti, T.K.F Wong, B. Thornlow, R. Corbett-Detig, Y. Turakhia, 
  R. Lanfear, B.Q. Minh (2023) DecentTree: scalable Neighbour-Joining for the genomic era.
  _Bioinformatics_, 39, btad536.
  <https://doi.org/10.1093/bioinformatics/btad536>

The distance-based tree reconstruction in DecentTree was originally derived 
from IQ-TREE2 and and then optimized and parallelized for large datasets with 
more than 10,000 sequences.

Key Features
------------

DecentTree implements several distance-based phylogenetic algorithms:

 * UPGMA (Sokal and Michener, 1958), 
 * Neighbor Joining (or NJ) (Saitou and Nei 1987), 
 * BioNJ (Gascuel, 1997), and 
 * Unweighted NJ (or UNJ) (Gascuel 2002).  

It includes vectorized versions of NJ, BIONJ, and UNJ. It also 
includes optimized versions of UPGMA, NJ and BIONJ, all of which use the 
same techniques as RapidNJ (Simonsen, et al., 2008). All 
the algorithms are implemented in header files, as template classes, allowing the caller 
to choose between single or double precision, all implement a standard interface, accepting either 
Phylip distance matrix files or in-memory matrices, and all are parallelized using OpenMP.  

The vectorized versions make use of the [VectorClass library](https://github.com/vectorclass/version2). 
The command-line application allows users to select the algorithm and thread count. 
DecentTree also makes use of custom vectorized sequence comparison functions (which also available 
via headers), that are called in parallel, to calculate distance matrices.

The (header only) template classes can be used in other projects.
(For full functionality it will be necessary to link with OpenMP - for parallelization - and 
compile with Agner Fog's VectorClass library - for vectorization).

More Detailed Information
-------------------------

For additional documentation, see:

- [Installation](doco/Installation.md)
- [Compilation](doco/Compilation.md)
- [Algorithms](doco/Algorithms.md)
- [API References](doco/Algorithms.md)
- [Code Examples](doco/Code_Examples.md)
- [Running DecentTree](doco/Running_DecentTree.md)

Acknowledgements and references
-------------------------------

### Distance Matrix Algorithms

- UPGMA_Matrix, used for Unweighted Neighbor Joining is an implementation 
  of the UPGMA algorithm of "Evaluating Systematic Relationships",
  by Rober R. Sokal, and Charles D. Michener (1958), 
  (in the University of Kansas Science Bulletin).
- NJMatrix, used for Neighbor Joining (NJ), is an implementation based on
  the Neighbor Joining (NJ) algorithm outlined in 
  "The neighbor-joining method: a new method for reconstructing phylogenetic trees",
  by Naurya Saitou and Masatoshi Nei (1987).
- UNJMatrix, is an implementation based on the Unweighted NJ (or UNJ)
  algorithm, described in "Concerning the NJ algorithm and its unweighted version, UNJ",
  by Olivier Gascuel (1997).
- BIONJMatrix, is an implementation based on the BIONJ algorithm
  described in "BIONJ: An Improved Version of the NJ Algorithm
  Based on a Simple Model of Sequence Data", by Olivier Gascuel (2009),
  in Molecular Biology and Evolution. 1997 14:685-695.
  See: http://www.lirmm.fr/~w3ifa/MAAS/BIONJ/BIONJ.html
- BIONJ2009, is based on a program, written by Olivier Gascuel
  and Hoa Sien Cuong, that was obtained from 
  http://www.lirmm.fr/~w3ifa/MAAS/BIONJ/BIONJ.html
- BoundingMatrix, used for BIONJ-R and NJ-R is based on
  "Inference of Large Phylogenies using Neighbour-Joining",
  by Martin Simonsen, Thomas Mailund, Christian N. S. Pedersen.
  From: Communications in Computer and Information Science
        (Biomedical Engineering Systems and Technologies:
        3rd International Joint Conference, BIOSTEC 2010,2
        Revised Selected Papers), volume 127, pages 334-344,
        Springer Verlag, 2011.
  See: https://birc.au.dk/software/rapidnj/.

### Other components

- LLVM's OpenMP library is used for parallelization
  (if DecentTree is built with a compiler than has Open MP support).
  (The omp.h header, based on that of LLVM, is included to deal with 
   compilation issues that sometims arise when building on Macintosh)
- Agner Fog's vectorclass library is used for vectorization 
  (in the NJ-V, BIONJ-V, UPGMA-V algorithms, implemented by
   VectorNJ, VectorBIONJ and VectorizedUPGMA_Matrix template classes).
   See: https://github.com/vectorclass.
- zlib (https://zlib.net) is a free library of compression algorithms.
  (DecentTree is built with version 1.2.7).
- gzstream, C++ iostream classes wrapping the zlib compression library.
  Copyright (C) 2001  Deepak Bandyopadhyay, Lutz Kettner
- The heapsort algorithm implemented in parallel_heapsort.h, is loosely 
  based on Floyd's TreeSort3 (Algorithm 245, Communications of the ACM,
  Volume 7, Number 12, December 1964) which in turn was based on 
  J.W.J.William's Heapsort (Algorithm 232, Communications of the aCM,
  Volume 7, Number 6, June 1964).
- The mergesort algorithm implemented in parallel_mergesort.h, is loosely 
  based on Algorithm S (Straight Mergesort), from volume 3 of
  "The Art of Computer Programming", by Donald E. Knuth
  (only the rational arithmetic used to split partitions evenly
   is original).
- The timing functions in timeutil.h were originally developed for IQ-TREE2.
  See: https://github.com/iqtree/iqtree2.
- The progress bar functionality in progress.h and progess.cpp was
  originally developed for IQ-TREE. See: https://github.com/iqtree/iqtree2.
  
