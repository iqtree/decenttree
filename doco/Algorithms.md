<h1>Algorithm Implementation Details</h1>
<h2>Memory Requirements</h2>
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
