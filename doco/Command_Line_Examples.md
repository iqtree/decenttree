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
<li> example.phy is the same alignment, compressed with gzip </li>
<li> example.dist is a distance matrix (in square phylip distance matrix 
format) </li>
<li> compressed_example.dist.gz is the same distance matrix, compressed with gzip </li>

</ul>

|Command line|Explanation|
|------------|-----------|
|decenttree  |If it is called without arguments, decenttree displays a summary of the command-line arguments that it recognizes.  It will also list the avalailable algorithms (and BENCHMARK, which isn't an algorithm, but is the argument you supply when you want to benchmark the available algorithms).|

<h2>Distance Matrices as inputs</h2>

|Command Line|Explanation|
|------------|-----------|
|decenttree -in ../example/example.dist<br> -std-out | Using the default distance matrix algorithm, infer a phylogenetic tree from the supplied distance matrix, and write the tree, in Newick format, to standard output.|
|decenttree -in ../example/compressed_example.dist.gz<br> -std-out | Using the same (default) distance matrix algorithm, infer a phylogenetic tree from the supplied distance matrix (which is in gz compressed format), and write the tree, in Newick format, to standard output.|
|decenttree -in ../example/example.dist<br> -t NJ-R-V -no-banner<br> -out njrv.newick | Infer a phylogenetic tree, using the *r*apid, *v*ectorized version of the NJ algorithm (NJ-R-V), and write the tree, in Newick format, to the file njrv.newick.  Suppress the decenttree banner text. |
|decenttree -in ../example/example.dist<br> -t NJ-R-V -q <br>-out njrv.newick | Infer a phylogenetic tree, using the *r*apid, *v*ectorized version of the NJ algorithm (NJ-R-V), and write the tree, in Newick format, to the file njrv.newick.  Don't write banner text or timing information to standard output (-q suppresses both). |
|decenttree -in ../example/example.dist<br> -t NJ-R-V -q -f 4<br>-out njrv_low_precision.newick | The same, but reduce the precision, of the inferred distances in the newick tree, to four digits, and write to a different file  |
|decenttree -in ../example/example.dist<br> -t NJ-R-V -q -f 4<br> -out njrv_compressed.newick.gz | The same, but compress the output 
(compression is implied by a .gz suffix). |
|decenttree -in ../example/example.dist<br> -t NJ-R-V -q -f 4<br> -out njrv_compressed.newick.gz | The same, but compress the output 
(compression is implied by a .gz suffix). |
|decenttree -in ../example/example.dist<br> -t NJ-R-V -q -f 4 -nt 1<br> -out njrv_compressed.newick.gz | The same, but use only a single thread. |

<h2>Alignments as inputs</h2>

|Command Line|Explanation|
|------------|-----------|
|decenttree decenttree -phylip ../example/example.phy<br> -std-out -no-banner| Using the default distance matrix algorithm, infer a phylogenetic tree from the supplied phylip alignment file, and write the tree, in Newick format, to standard output.|
|decenttree -phylip ../example/compressed_example.phy.gz<br> -std-out -no-banner| As before, only this time the input is compressed. decenttree inspects the file to determine if it is compressed. The file name doesn't matter.|
|decenttree -phylip ../example/example.phy -uncorrected<br> -std-out -no-banner| Using the default distance matrix algorithm, infer a phylogenetic tree from the supplied phylip alignment file (using uncorrected Hamming distances), and write the tree, in Newick format, to standard output.|
| decenttree -phylip ../example/interleaved_example.phy<<br>> -t NJ-R-V -std-out | Using a vectorized (the V in NJ-R) branch-and-bound (the R in NJ-R-V) version of the Neighbour Joining algorithm, infer a phylogenetic tree from the supplied *interleaved* phylip alignment file, and write the tree, in Newick format, to standard output. |
| decenttree -phylip ../example/3x3.phy<br> -dist-out 3x3_as_dna.dist<br> -q -no-out | Calculate a distance matrix for a dummy 3 taxon, 3 nucleotide input, which has A, C, or T, but not G sites.  By default decenttree assumes that sites can be A, C, G, or T.
| decenttree -phylip ../example/3x3.phy<br> -dist-out 3x3_not_dna.dist<br> -q -no-out -not-dna | Calculate a distance matrix using a 3-character alphabet, implied by input, which has A, C, or T, but not G. |
| decenttree -phylip ../example/3x3.phy<br> -dist-out 3x3_five_chars.dist<br> -q -no-out -alphabet CATGU | Calculate a distance matrix using a 5 character alphabet |
| cat 3x3*.dist | Display the distance matrices output by the previous three examples, showing the affect of alphabet size on corrected distances |



Todo: Provide example command-lines for:
<ul>
<li>[todo: -fasta]</li>
<li>[todo: -alphabet]</li>
</ul>

|Command Line|Explanation|
|------------|-----------|

<h2>Alignments as outputs</h2>
Todo: Provide example command-lines for:
<ul>
<li>[todo: -msa-out]</li>
<li>[todo: -strip-name] + [todo: -name-replace]</li>
<li>[todo: -truncate-name-at] (truncation of long names)</li>
<li>[todo: -num] (replacing names with numbered names, of the form A_i_ where _i_ is a number between 1 and _n_, the number of taxa)</li>
</ul>

|Command Line|Explanation|
|------------|-----------|
| decenttree -phylip ../example/example.phy<br> -aln-out interleaved_example.phy<br> -t NONE -no-out -no-banner | Convert an un-interleaved phylip alignment file into an interleaved one |
| decenttree -phylip ../example/example.phy<br> -aln-out interleaved_example.phy.gz<br> -t NONE  -no-out -no-banner | Convert an un-interleaved phylip alignment file into an interleaved one, and zip the output file as it is generated (zipping is implied by the .gz extension) |


<h2>Distance Matrices as outputs</h2>

Todo:
<ul>
<li>-no-matrix (if a distance matrix file is being generated, and a phylogenetic tree is not being inferred, -t NONE,
    it isn't strictly necessary to create an in-memory distance matrix, and this option tells decenttree to save memory
    by NOT allocating or using one). 
</ul>

|Command Line|Explanation|
|------------|-----------|
|decenttree -phylip ../example/example.phy<br> -no-banner <br> -dist example.dist -out-format upper <br>-t NONE -no-out | Using the default distance matrix algorithm, infer a distance matrix, and write the distance matrix (in upper-triangle Phylip format) to the file, example.dist. -t NONE says *not* to use a phylogenetic inference algorithm.  If no out-format parameter is provided the default is square. |
|decenttree -phylip ../example/example.phy<br> -no-banner -uncorrected<br> -dist uncorrected.dist.gz -out-format upper.gz<br> -t NONE -no-out | The same, only this time uncorrected distances are to be calculated, the distance matrix is to be written to uncorrected.dist.gz, and is to be compressed with gzip|

<h2>Benchmarking</h2>
In these examples, simulated_1k.fa.gz is a fasta file containing a simulated alignment with 1000 taxa, and a sequence length of 10,000,
generated using IQTree2 and gzip, via the (MacOS/Unix) commands:

    iqtree2 -r 1000 tree.nwk 
    iqtree2 --alisim data -af fasta -m JC -t tree.nwk --length 10000
    mv data.fa simulated_1k.fa
    gzip simulated_1k.fa

|Command Line|Explanation|
|------------|-----------|
|decenttree -fasta ../example/simulated_1k.fa.gz<br> -t BENCHMARK -no-out -nt 4 | Benchmark each of the available algorithms, one after another, with 1 through 4 threads of execution (multi-threading is only supported if decenttree is compiled with Open MP, and running on a multi-CPU architecture).|
|decenttree -fasta ../example/simulated_1k.fa.gz<br> -t BENCHMARK -no-out | Benchmark each of the available algorithms, one after another, with 1 through *n* threads (where *n* is the number of available CPUs)  (only if decenttree is compiled with Open MP, and running on a multi-CPU architecture).|
