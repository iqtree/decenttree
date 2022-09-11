<h1>pydecenttree Python Extension</h1>
<h2>Introduction</h2>
pydecenttree is a C++ Python Extension that makes the distance matrix phylogeny inference functions of decenttree available to python users.
<h2>Methods</h2>

| Method name | Comments |
|-------------|---|
| getAlgorithmNames() | Returns a collection, containing the names of the available distance matrix phylogenetic inference algorithms.  Which algorithms are available will depend on whether vectorisation was enabled when pydecenttree was built. |
| constructTree() | Infers a phylogenetic tree. Returns a string, that contains the tree, in Newick format. | 

<h2>Parameters to constructTree()</h2>

| Parameter name | Type | Comments |
|-------------|---|---|
| algorithm | string | the name of the desired algorithm (if it is blank, the default algorithm  will be used) |
| sequences | collection of strings | The names of the sequences (these will be names of the nodes in the newick string that constructTree() returns). The number of sequences, **n**, must be at least 3.
| distances | see comments | May be a flat collection (or 1D numpy matrix) containing n*n numbers, a collection of n rows (each a collection of the n numbers in a row), or an n by n 2D numpy matrix
| number_of_threads | number | The number of threads.  If pydecenttree has been built with [openmp](https://en.wikipedia.org/wiki/OpenMP), this can be used to limit the number of threads of execution that pydecenttree will use. If it is not supplied, as many threads will be used as there are cores available.  If pydecenttree has _not_ been built with [openmp](https://en.wikipedia.org/wiki/OpenMP), this parameter has no effect.
| precision | number | indicates how many digits of precision will be used by pydecenttree, to format the distances between nodes in the Newick tree string, it returns.
| verbosity | number | indicates how much information (if any) should be written to standard output during execution.
