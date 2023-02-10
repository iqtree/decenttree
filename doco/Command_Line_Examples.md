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
| cat 3x3*.dist | Display the distance matrices output by the previous three examples, showing the affect of alphabet size on corrected distances. |

<h2>Alignments as outputs</h2>

|Command Line|Explanation|
|------------|-----------|
| decenttree -phylip ../example/example.phy<br> -msa-out example.msa<br> -t NONE -no-out -no-banner | Given Phylip-format alignment file, output a file in an msa format, for the same alignment |
| decenttree -phylip ../example/example.phy<br> -msa-out example.msa<br> -t NONE -no-out -no-banner<br>-strip-name fish | The same, but replace the characters 'f', 'i', 's' and 'h' with underscores, in taxon names (some phylogenetic inference programs treat commas, slashes, hyphens, colons, single quotes as special characters, that may not appear in taxon names) |
| decenttree -phylip ../example/example.phy<br> -msa-out example.msa<br> -t NONE -no-out -no-banner<br>-truncat-name-at e | The same, but truncate every taxon name at the first occurrence of the character 'e' (this is a bit artificial.  But often taxon names are identifier, a marker character, and supplementary information, and truncating at the marker character may be necessary if you are providing input to a program that has a taxon name length limit) |
| decenttree -phylip ../example/example.phy<br> -msa-out example.msa<br> -t NONE -no-out -no-banner<br>-num | The same, but replace taxon names with numbered names "A1", "A2", and so on. |
| decenttree -phylip ../example/example.phy<br> -aln-out interleaved_example.phy<br> -t NONE -no-out -no-banner | Convert an un-interleaved phylip alignment file into an interleaved one |
| decenttree -phylip ../example/example.phy<br> -aln-out interleaved_example.phy.gz<br> -t NONE  -no-out -no-banner | Convert an un-interleaved phylip alignment file into an interleaved one, and zip the output file as it is generated (zipping is implied by the .gz extension) |

<h2>Distance Matrices as outputs</h2>

Decenttree can be used to generate distance matrices (it has this functionality because it made it easier to generate test inputs for other programs that require distance matrices, and impose additional requirements - such as no two sequences being identical).

<ul>
<li>The -strip-name, -truncate-name-at and -num parameters also affect the taxon names that are quoted in distance matrix outputs. If the file-name ends with ".gz" results in
</li>
<li>The -no-matrix option may save memory. If a distance matrix file is being generated,    
    and a phylogenetic tree is not being inferred (because, for
    example, -t NONE was supplied as an option on the command-line)
    it isn't strictly necessary to create an in-memory distance matrix, and this option tells decenttree to save memory
    by NOT allocating or using one.
    </li>
<li>The -filter instructs decenttree to identify groups (pairs, or larger sets) of taxa, for which the sequences have no characters that are definitely different, and to remove all but one of the taxa, in each such group, from consideration (this option, for removing such such "problematic" sequences, exists because some distance matrix phylogenetic inference implementations, that take alignment files as inputs, will refuse to accept inputs containing sets of taxa with zero differences).
</ul>

|Command Line|Explanation|
|------------|-----------|
|decenttree -phylip ../example/example.phy<br> -no-banner <br> -dist example.dist -out-format upper <br>-t NONE -no-out | Using the default distance matrix algorithm, infer a distance matrix, and write the distance matrix (in upper-triangle Phylip format) to the file, example.dist. -t NONE says *not* to use a phylogenetic inference algorithm.  If no out-format parameter is provided the default is square. |
|decenttree -phylip ../example/example.phy<br> -no-banner -uncorrected<br> -dist uncorrected.dist.gz -out-format upper.gz<br> -t NONE -no-out | The same, only this time uncorrected distances are to be calculated, the distance matrix is to be written to uncorrected.dist.gz, and is to be compressed with gzip|
|./decenttree -in ../example/example.dist -dist example_copy.dist -out-format upper -f 4 -t NONE -no-out |  Given a distance matrix (!) file as an input, generate another distance matrix file (in upper triangle format, with four digits of precision). |

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
