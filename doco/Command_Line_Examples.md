<h1>Command-line Examples for decenttree</h1>
In these examples, **decenttree** is being run in the build
subdirectory (the example folder of the project is a sibling
of the build directory). If the relative path to the example 
folder is different you will have to replace ../example in 
file path parameters.
<p>
The files, in the *example* directory, that these command-line examples make use of, are:
<ul>
<li> example.phy is a small (17-taxon) example alignment (in un-interleaved phylip example format) </li>
<li> example.dist is a distance matrix (in square phylip distance matrix format) </li>
<li> compressed_example.dist.gz is the same distance matrix, compressed with gzip </li>

</ul>

|Command line|Explanation|
|------------|-----------|
|decenttree  |If it is called without arguments, decenttree displays a summary of the command-line arguments that it recognizes.  It will also list the avalailable algorithms (and BENCHMARK, which isn't an algorithm, but is the argument you supply when you want to benchmark the available algorithms).|

<h2>Distance Matrices as inputs</h2>

|Command Line|Explanation|
|------------|-----------|
|decenttree -in ../example/example.dist -std-out | Using the default distance matrix algorithm, infer a phylogenetic tree from the supplied distance matrix, and write the tree, in Newick format, to standard output.|
|decenttree -in ../example/compressed_example.dist.gz -std-out | Using the same (default) distance matrix algorithm, infer a phylogenetic tree from the supplied distance matrix (which is in gz compressed format), and write the tree, in Newick format, to standard output.|
|decenttree -in ../example/example.dist -t NJ-R-V -no-banner -out njrv.newick | Infer a phylogenetic tree, using the *r*apid, *v*ectorized version of the NJ algorithm (NJ-R-V), and write the tree, in Newick format, to the file njrv.newick.  Suppress the decenttree banner text. |
|decenttree -in ../example/example.dist -t NJ-R-V -q-out njrv.newick | Infer a phylogenetic tree, using the *r*apid, *v*ectorized version of the NJ algorithm (NJ-R-V), and write the tree, in Newick format, to the file njrv.newick.  Don't write banner text or timing information to standard output. |

Todo: Provide example command-lines for:
<ul>
<li>[todo: -f]  Turning down the precision</li>
<li>[todo: -c]  Controlling the level of compression to use</li>
<li>[todo: -nt] Running it single-threaded</li>
</ul>

<h2>Alignments as inputs</h2>

|Command Line|Explanation|
|------------|-----------|
|decenttree decenttree -phylip ../example/example.phy -std-out -no-banner| Using the default distance matrix algorithm, infer a phylogenetic tree from the supplied phylip alignment file, and write the tree, in Newick format, to standard output.|
|decenttree -phylip ../example/compressed_example.phy.gz -std-out -no-banner| As before, only this time the input is compressed. decenttree inspects the file to determine if it is compressed. The file name doesn't matter.|
|decenttree -phylip ../example/example.phy -uncorrected -std-out -no-banner| Using the default distance matrix algorithm, infer a phylogenetic tree from the supplied phylip alignment file (using uncorrected Hamming distances), and write the tree, in Newick format, to standard output.|

Todo: Provide example command-lines for:
<ul>
<li>[todo: -fasta]</li>
<li>[todo: interleaved phylip example]</li>
<li>[todo: -alphabet]</li>
</ul>

<h2>Alignments as outputs</h2>
Todo: Provide example command-lines for:
<ul>
<li>[todo: -msa-out]</li>
<li>[todo: -strip-name] + [todo: -name-replace]</li>
</ul>

<h2>Distance Matrices as outputs</h2>

|Command Line|Explanation|
|------------|-----------|
|decenttree -phylip ../example/example.phy -no-banner -dist example.dist -out-format upper -t NONE -no-out | Using the default distance matrix algorithm, infer a distance matrix, and write the distance matrix (in upper-triangle Phylip format) to the file, example.dist. -t NONE says *not* to use a phylogenetic inference algorithm.  If no out-format parameter is provided the default is square. |
|decenttree -phylip ../example/example.phy -no-banner -uncorrected  -dist uncorrected.dist.gz -out-format upper.gz -t NONE -no-out | The same, only this time uncorrected distances are to be calculated, the distance matrix is to be written to uncorrected.dist.gz, and is to be compressed with gzip|

<h2>Benchmarking</h2>

Todo: Provide example command-lines for running benchmarks on a large
example input (need at least 1,000 sequences).
