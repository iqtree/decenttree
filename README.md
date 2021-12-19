<h1>decenttree</h1>
<h2>Introduction</h2>
decenttree is a cross-platform library, and stand-alone command-line application, 
for generating phylogenetic trees (in newick format) from distance matrices
(supplied in phylip distance matrix formats), or alignments (supplied in fasta format), 
using well-known algorithms, such as 

  * Neighbour Joining
  * BIONJ
  * UPGMA


The distance matrix tree construction implementations in decenttree were originally
developed as part of the IQTree2 application (formerly IQTree used a single-threaded
implementation of BIONJ to generate initial phylogenetic trees; scaling issues meant 
that was a performance bottleneck for generating phylogenetic trees for Covid-19 alignments,
with more than a few thousand sequences. The classes in decenttree were developed to
remove the bottleneck).

<h2>Key Features</h2>
The decenttree program implements multiple distance matrix tree reconstruction algorithms, in C++:

 * UPGMA (Sokal and Michener, 1958), 
 * Neighbor Joining (or NJ) (Saitou and Nei 1987), 
 * BioNJ (Gascuel, 1997), and 
 * Unweighted NJ (or UNJ) (Gascuel 2002).  

The decenttree folder includes vectorized versions of NJ, BIONJ, and UNJ. It also 
includes optimized versions of UPGMA, NJ and BIONJ, all of which use the 
same branch-and-bound techniques as RapidNJ (Simonsen, et al., 2008). All 
the algorithms are implemented in header files, as template classes, allowing the caller 
to choose between single or double precision, all implement a standard interface, accepting either 
Phylip distance matrix files or in-memory matrices, and all are parallelized using OpenMP.  

The vectorized versions make use of Agner Fog’s VectorClass library (https://www.agner.org/optimize/vectorclass.pdf). The command-line application allows the caller to select the algorithm and thread count.  The decenttree application also makes use of custom vectorized sequence comparison functions (which also available via headers), that are called in parallel, to calculate distance matrices.

The (header only) template classes can be used in other projects.
(For full functionality it will be necessary to link with OpenMP - for parallelization - and 
compile with Agner Fog's VectorClass library - for vectorization).

<h2>Running decenttree</h2>

<h2>Command-line options</h2>

| Option      | Argument               | Description |
| ------      | --------               | ----------- |
| -nt         | number (1 or more)     | Specify number of threads of execution (if built with OMP) |
| -no-banner  |                        | Suppress banner |
| -v          |                        | Verbose output |
| -bar        | | Turns on the display of progress bars |
| -q          |                        | Silent |
| -fasta      | fasta input file path  | Supply path of a fasta format file containing an alignment |
| -in         | dist input file path   | Supply path of a distance matrix file.        |
| -dist       | dist input file path   | Supply path of a distance matrix file         |
| -not-dna    |                        | with -fasta, indicates input is (not) DNA     |
| -alphabet   | list of characters     | with -fasta, recognized nucleotide characters |
| -unknown    | list of characters     | with -fasta, characters that indicate unknown |
| -strip-name   | list of characters | Characters to strip from taxon names (case sensitive) |
| -name-replace | list of characters | Characters to replace the stripped characters with |
| -truncate-name-at | list of characters | Truncate taxon name on one of these characters |
| -uncorrected | | with -fasta, do not apply Jukes-Cantor distance correction to calculated distances |
| -filter     | | with -fasta, Filter sequences that have zero distance |
| -no-matrix  |  | with -fasta, save memory by *not* constructing the input matrix in memory  |
| -msa-out    | msa output file path             | with -fasta, write alignment in msa format |
| -dist-out   | distance matrix output file path | Use STDOUT to write it to standard output  |
| -t          | algorithm name                   | Specify the algorithm to use to construct the tree (or none) |
| -out        | newick output file path          | Use STDOUT to write it to standard output  |
| -std-out    |                                  | Equivalent to -out STDOUT                  |
| -no-out     |                                  | Do not generate a newick output file       |
| -gz         |                                  | Write outputs in gzip format               |
| -out-format | square, upper, lower | format for writing distance matrix output |
| -f          | number 1-15     | Digits of precision, to write in the output      |
| -c          | number 0-9      | Compression level to use when writing gzip files |

<h2>Algorithms</h2>
Each of the working matrices require the same amount of memory (approximately 4 * n * n bytes,
where n is the number of taxa), except for the double precision versions (where the D, V, and S
matrices are twice as large).  The D matrix tracks distances between taxa (or clusters). The V 
matrix tracks estimated variance associated with each taxon (or cluster) (only in BIONJ 
implementations).  The S matrix is like the D matrix, but with each row sorted by increasing 
distance (and each row of the I matrix contains the indices of the clusters that correspond to
those distances).  Only branch-and-bound algorithms use S and I matrices.

The ONJ-R and ONJ-R-V implementations use a single _triangular_ S+I matrix, containing 
entries that are (distance, cluster number) pairs (and removing entries for clusters 
that are no longer under consideration).  They're rather more complicated (and for now, 
appear to be slightly slower) than the NJ-R and NJ-R-V implementations.

| Name     | Matrices    | Description | Notes |
| ----     | --------    | ----------- | ----- |
| UPGMA    | D           | UPGMA (assumes tree is ultrametric)      | Not recommended |
| UPGMA-V  | D           | Vectorized version of UPGMA.             | Not recommended |
| NJ.      | D           | Neighbor Joining                         | |
| NJ-V     | D           | Vectorized version of Neighbor Joining   | |
| NJ-R     | D, S, I     | NJ with branch and bound optimization    | Recommended |
| NJ-R-D   | D, S, I.    | Double precision version of NJ-R.        | |
| ONJ-R    | D, S+I      | An alternative version of NJ-R           | Slower than NJ-R|
| ONJ-R-V  | D, S+I      | An alternative version of NJ-R           | Slower than NJ-R-V|
| UNJ      | D           | Unweighted Neighbor Joining              | |
| BIONJ    | D, V        | BIONJ                                    | |
| BIONJ-V  | D, V        | Vectorized version of BIONJ              | |
| BIONJ-R  | D, V, S, I  | BIONJ with branch-and-bound optimization | Recommended. But slower than NJ-R |
| AUCTION  | D, S, I     | Reverse auction cluster joining          | Experimental. Not recommended |

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

<h2>Code examples</h2>

<h2>Installation</h2>

<h2>API reference</h2>

<h3>Distance Matrices and Distance Matrix Algorithms</h3>

All of these classes are in the StartTree namespace.

| File    | Class.                 | Dependencies | Function |
| -----   | ----------             | ------------ | -------- |
| distancematrix.h | Matrix        | none         | 2-dimensional matrices  |
| distancematrix.h | SquareMatrix. | Matrix.      | Square matrices (and reading from phylip distance matrix files) |
| upgma.h   | UPGMA_Matrix.        | SquareMatrix | Implementation of UPGMA |
| upgma.h | VectorizedUPGMA_Matrix | UPGMA_Matrix, vectorclass library | Vectorized implementation of UPGMA_Matrix |
| nj.h.     | NJMatrix             | UPGMA_Matrix | Implementation of NJ |
| nj.h.     | UNJMatrix            | NJMatrix     | Implementation of UNJ |
| nj.h.     | BIONJMatrix          | NJMatrix     | Implementation of BIONJ (adds V matrix, for calculating branch lengths) |
| nj.h.     | VectorizedMatrix     | NJMatrix *or* BIONJMatrix, vectorclass library | Vectorizes either NJMatrix of BIONJMatrix |
| rapidnj.h | BoundingMatrix       | NJMatrix *or* BIONJMatrix, MirrorMergeSorter | Adds S and I matrices, for branch and bound, for NJ-R or BIONJ-R |
| auctionmatrix.h | AuctionMatrix. | BoundingMatrix, NJMatrix | Implementation of a reverse-auction distance matrix algorithm |
| starttree.h | BuilderInterface.  | std::string   | Interface that additional distance matrix algorithms must implement.  This is only a proof of concept. |
| starttree.h, starttree.cpp  | Factory | BuilderInteface | Registry of distance matrix algorithms |
| starttree.h, starttree.cpp  | Builder | BuilderInterface | Used to make an individual algorithm accessible via Factory::getBuilder |
| starttree.h, starttree.cpp  | BenchmarkingTreeBuilder | BuilderInterface, Factory | Used for calling *all* for the algorithms registered via Factory::addBuilder |

<h3>Alignments</h3>

| File                     | Class.         | Dependencies | Function |
| -----                    | ----------     | ------------ | -------- |
| sequence.h, sequence.cpp | Sequence       | none         | Recording sequence name and sites|
| sequence.h, sequence.cpp | Sequences.     | Sequence     | Loading sequence alignments from fast or phylip files.|
| sequence.h, sequence.cpp | SequenceLoader | Sequences.   | Loading sequence alignments, calculating hamming (or Jukes-Cantor) distances, loading distance matrices and writing distance matrices in Phylip format.|

<h3>Sorting</h3>

| File            | Class.                   | Dependencies    | Function |
| -----           | ----------               | ------------    | -------- |
| parallel_sort.h | ParallelSorter           | none            | Interface |
| parallel_sort.h | ParallelMirrorSorter     | ParallelSorter  | Interface, for sorting one array (row of S) and mirroring the permutation in another (row of I) |
| parallel_sort.h | ValueAndSattelite        | none            | Sorting (key,value) pairs by key (and not value) |
| parallel_sort.h | ParallelMirrorSorterBase | ParallelMirrorSorter, ValueAndSattelite | Converts a ParallelSorter into a ParallelMirrorSorter (copying data from S and I rows into an auxiliary matrix of ValueAndSattelite, sorting that, and copying the result back. |
| parallel_mergesort.h | MergeSorter         | ParallelSorter  | Mergesort |
| parallel_mergesort.h | MirrorMergeSorter   | MergeSorter, ParallelMirrorSorterBase | Sorting rows of S and I using Mergesort |

<h3>Other</h3>

| File                        | Class            | Dependencies                   | Function |
| -----                       | -----            | ------------                   | -------- |
| utils/argument.h and argument.cpp | Argument, IntArgument, StringArgument, SwitchArgument | (none) | Parsing command-line arguments |
| utils/progress.h and progress.cpp | progress_display | std::string, std::fstream      | Displaying progress bars on the console |
| utils/gzstream.h and gzstream.cpp | igzstream        | zlib headers                   | Reading files in gzip format |
| utils/gzstream.h and gzstream.cpp | pigzstream       | zlib headers, display_progress | Displaying progress while reading files in gzip format |
| utils/gzstream.h and gzstream.cpp | ogzstream        | zlib headers                   | Writing files in gzip format |
| utils/hammingdistance.h           | (none)           | none                           | Free functions for calculating hamming distances |
| utils/hammingdistance.h           | (none)           | vectorclass libraries          | Free functions for calculating hamming distances |
  
<h2>Acknowledgements and references</h2>

<h3>Distance Matrix Algorithms</h3>

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

<h3>Other components</h3>

- LLVM's OpenMP library is used for parallelization
  (if decenttree is built with a compiler than has Open MP support).
  (The omp.h header, based on that of LLVM, is included to deal with 
   compilation issues that sometims arise when building on Macintosh)
- Agner Fog's vectorclass library is used for vectorization 
  (in the NJ-V, BIONJ-V, UPGMA-V algorithms, implemented by
   VectorNJ, VectorBIONJ and VectorizedUPGMA_Matrix template classes).
   See: https://github.com/vectorclass.
- zlib [Todo]
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
- The timing functions in timeutil.h were originally developed for IQTree2.
  See: https://github.com/iqtree/iqtree2.
- The progress bar functionality in progress.h and progess.cpp was
  originally developed for IQTree2 See: https://github.com/iqtree/iqtree2.
  
