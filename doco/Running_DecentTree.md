<h1>Running decenttree</h1>
<h2>Command-line options</h2>

| Option      | Argument               | Description |
| ------      | --------               | ----------- |
| -nt         | number (1 or more)     | Specify number of threads of execution (if built with OMP) |
| -no-banner  |                        | Suppress banner |
| -v          |                        | Verbose output |
| -bar        | | Turns on the display of progress bars |
| -q          |                        | Silent |
| -in         | dist input file path   | Supply path of a distance matrix file.        |
| -fasta      | fasta input file path  | Supply path of a fasta format file containing an alignment |
| -phylip     | phylip input file path  | supply path of a phylip alignment file |
| -uncorrected | | with -fasta, do not apply Jukes-Cantor distance correction to calculated distances |
| -max-dist   | number | specify the maximum distance that is to be allowed, when generating a distance matrix file (the default maximum is 10) |
| -not-dna    |                        | with -fasta, indicates input is (not) DNA     |
| -alphabet   | list of characters     | with -fasta, recognized nucleotide characters |
| -unknown    | list of characters     | with -fasta, characters that indicate unknown |
| -strip-name   | list of characters   | Characters to strip from taxon names (case sensitive) |
| -name-replace | list of characters   | Characters to replace the stripped characters with |
| -truncate-name-at | list of characters | Truncate taxon name on one of these characters |
| -num        |                          | Replace all taxon names with numbered names of the form A_i_ (_i_ is taxon number, starting at 1) | 
| -filter     |  | with -fasta, Filter sequences that have zero distances |
| -no-matrix  |  | with -fasta, save memory by *not* constructing the input matrix in memory (only has an effect with -t NONE) |
| -msa-out    | msa output file path             | given -fasta or -phylip, rewrite alignment in msa format |
| -dist       | dist output file path   | Supply path to which to write a distance matrix (makes sense with -in, -fasta or -phylip). Use STDOUT to write to standard output. |
| -dist-out   | distance matrix output file path | Synonym for -dist. |
| -t          | algorithm name                   | Specify the algorithm to use to construct the tree (or none) |
| -out        | newick output file path          | Use STDOUT to write it to standard output  |
| -std-out    |                                  | Equivalent to -out STDOUT                  |
| -no-out     |                                  | Do not generate a newick output file       |
| -gz         |                                  | Write outputs in gzip format               |
| -out-format | square, upper, lower | format for writing distance matrix output |
| -f          | number 1-15     | Digits of precision, to write in the output      |
| -c          | number 0-9      | Compression level to use when writing gzip files |
