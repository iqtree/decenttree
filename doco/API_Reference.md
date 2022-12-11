<h1>decenttree API reference</h1>
<h2>Distance Matrices and Distance Matrix Algorithms</h2>

All of these classes are in the StartTree namespace.

| File    | Class.                 | Dependencies | Function |
| -----   | ----------             | ------------ | -------- |
| distancematrix.h | Matrix        | none         | 2-dimensional matrices  |
| distancematrix.h | SquareMatrix. | Matrix.      | Square matrices (and reading from phylip distance matrix files) |
| upgma.h   | UPGMA_Matrix.        | SquareMatrix | Implementation of UPGMA algorithm. |
| upgma.h | VectorizedUPGMA_Matrix | UPGMA_Matrix, vectorclass library | Vectorized implementation of UPGMA_Matrix |
| nj.h     | NJMatrix             | UPGMA_Matrix | Implementation of NJ algorithm |
| nj.h     | UNJMatrix            | NJMatrix     | Implementation of UNJ algorithm|
| nj.h     | BIONJMatrix          | NJMatrix     | Implementation or BIONJ (adds V matrix, for calculating branch lengths) |
| nj.h     | VectorizedMatrix     | NJMatrix *or* BIONJMatrix, vectorclass library | Vectorizes either NJMatrix of BIONJMatrix |
| rapidnj.h | BoundingMatrix       | NJMatrix *or* BIONJMatrix, MirrorMergeSorter | Adds S and I matrices, for branch and bound, for NJ-R or BIONJ-R |
| auctionmatrix.h | AuctionMatrix | BoundingMatrix, NJMatrix | Implementation of a reverse-auction distance matrix algorithm |
| starttree.h | BuilderInterface  | std::string   | Interface that additional distance matrix algorithms must implement.  |
| starttree.h, starttree.cpp  | Registry | BuilderInteface | Registry of distance matrix algorithms |
| starttree.h, starttree.cpp  | Builder | BuilderInterface | Used to make an individual algorithm accessible via Registry::getBuilder |
| starttree.h, starttree.cpp  | BenchmarkingTreeBuilder | BuilderInterface, Registry | Used for calling *all* for the algorithms registered via Registry::addBuilder |

<h2>Alignments</h2>

| File                     | Class.         | Dependencies | Function |
| -----                    | ----------     | ------------ | -------- |
| sequence.h, sequence.cpp | Sequence       | none         | Recording sequence name and sites|
| sequence.h, sequence.cpp | Sequences.     | Sequence     | Loading sequence alignments from fast or phylip files.|
| sequence.h, sequence.cpp | SequenceLoader | Sequences.   | Loading sequence alignments, calculating hamming (or Jukes-Cantor) distances, loading distance matrices and writing distance matrices in Phylip format.|

<h2>Sorting</h2>

| File            | Class.                   | Dependencies    | Function |
| -----           | ----------               | ------------    | -------- |
| parallel_sort.h | ParallelSorter           | none            | Interface |
| parallel_sort.h | ParallelMirrorSorter     | ParallelSorter  | Interface, for sorting one array (row of S) and mirroring the permutation in another (row of I) |
| parallel_sort.h | ValueAndSattelite        | none            | Sorting (key,value) pairs by key (and not value) |
| parallel_sort.h | ParallelMirrorSorterBase | ParallelMirrorSorter, ValueAndSattelite | Converts a ParallelSorter into a ParallelMirrorSorter (copying data from S and I rows into an auxiliary matrix of ValueAndSattelite, sorting that, and copying the result back. |
| parallel_mergesort.h | MergeSorter         | ParallelSorter  | Mergesort |
| parallel_mergesort.h | MirrorMergeSorter   | MergeSorter, ParallelMirrorSorterBase | Sorting rows of the S and I auxiliar matrices using Mergesort |

<h2>Other</h2>

| File                        | Class            | Dependencies                   | Function |
| -----                       | -----            | ------------                   | -------- |
| utils/argument.h and argument.cpp | Argument, IntArgument, StringArgument, SwitchArgument | (none) | Parsing command-line arguments |
| utils/progress.h and progress.cpp | progress_display | std::string, std::fstream      | Displaying progress bars on the console |
| utils/gzstream.h and gzstream.cpp | igzstream        | zlib headers                   | Reading files in gzip format |
| utils/gzstream.h and gzstream.cpp | pigzstream       | zlib headers, display_progress | Displaying progress while reading files in gzip format |
| utils/gzstream.h and gzstream.cpp | ogzstream        | zlib headers                   | Writing files in gzip format |
| utils/hammingdistance.h           | (none)           | none                           | Free functions for calculating hamming distances |
| utils/hammingdistance.h           | (none)           | vectorclass libraries          | Free functions for calculating hamming distances |
  