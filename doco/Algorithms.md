<h1>decenttree Algorithm Implementation Details</h1>
All neighbour-joining algorithms rely on matrices of distances between clusters (of one taxon or multiple taxa). Most calculate adjusted distances, taking into account how far individual clusters are, on average, from other clusters, and some use auxiliary matrices (such as the estimated variance matrix of BIONJ), but all use matrices of distances.<p>

The decenttree algorithms (except for the ONJ algorithms, which use triangular matrices), make use of square matrices (using triangular matrices would reduce memory consumption by a factor of 2, but would considerably increase the cost of accessing entries in the matrix, and matrix access would also have been much more difficult to vectorize efficiently).

The bulk of the memory required by the decenttree distance matrix tree inference algorithms, is that used to track the ( n * n entry) distance matrices themselves.  There are also some vectors, the track clusters to be considered, or the structure of the subtrees for the clsuters yet to be joined, but these are much smaller (of size proportional to n, rather than n * n).

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
| NJ       | D           | Neighbor Joining                         | |
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

<h2>Other common features</h2>
All of the distance-based algorithms implemented in decentTree make use of distance matrices.
Distance-*matrix* algorithms take, as their principle input (apart from a list of names of the N Taxa),
an N row, N column matrix of distances; the distance between taxa *a* and *b* can be read by 
looking at the *b*th entry in the *a*th row (or the *a*th entry in the *b*th row, 
if distances are symmetric).  In practice, distances *are* symmetric and
the distance from a and b is the same as the distance from b and a.  
The distance between any sequence and itelf is assumed to be zero.<br><br>
Uncorrected distances are typically calculated by counting the number of characters that must differ,
between two sequences in a sequence alignment, and dividing the count by the total number 
of sites in both sequences. Corrected distances are calculated by adjusting the uncorrected distance using a Jukes-Cantor (or similar) correction.<br><br>

Distance matrix algorithms can use either uncorrected or corrected distances between taxa.  In practice, using uncorrected distances seems to give better results (indeed, the formulae that are used to determine the
calculated or estimated distances between imputed ancestors, were designed assuming that all distances are 
uncorrected, and using them on corrected distances does not really make mathematical sense).

decentTree can be supplied a sequence alignment (rather than a distance matrix). It will 
calculate corrected (or uncorrected) distances between the taxa in the alginment.

Neighbour-joining algorithms (except for AUCTION and STICHUP algorithms, which use raw distances) tend to
look for neighbours by searching for pairs of clusters (or indivdidual taxa) with a minimal adjusted 
difference. (the literature tends to talk about a Q matrix, where Qij is the adjusted difference between 
the *i*th and *j*th cluster). The details vary from algorithm to algorithm, but typically the adjusted 
distances are calculated by subtracting "compensatory" terms to adjust for how distant each of the two clusters is, on average, from all other clusters.  In the literature entries in the Q matrix are calculated as

(N-2)*D(x,y) - sum(D row for x) - sum(D row for Y)

(or something like it). In practice, decentTree tends to divide by N-2, so:

D(x,y) - (1/(n-2)) * sum(D row for x) - (1/(n-2)) *sum(D row for Y)

(or something like it). This is because multiplying by (N/2), frequently (in the case of the simpler algorithms, once for every non-diagonal entry in an (N*N) matrix!), is a lot more expensive than multiplying N row totals by (1/(N-2)), once.

The initial N*N distance matrix is laid out in memory, in row major order:
with all the distances in the first row, then all the distances in the second row, and so on.  Whenever two clusters, one in row
(and column) A, one in row (and column) B, A less than B, are joined, 
and replaced by a new cluster (the one that joins them), by
<ul>
<li>writing distances to the new cluster in row (and column) A</li>
<li>overwriting column B with the distances from the last row (and column)</li>
<li>reducing the number of rows (and columns) by one</li>
</ul>

Pointers to the start of each of the rows are maintained (the starts of rows stay in the same place, what is changing is: which row is mapped to which cluster). 

Each time the algorithm identifies the pair (a,b) of clusters to me merged next,
the two clusters, a, and b, are removed, and replaced with the cluster, u, that is their union.
Assume, that a is the cluster with the row that appears first in the matrix.
 - Row a is overwritten with row u (likewise column a)
 - Row b is overwritten with the contents of the last row (likewise, column b)
 - Whatever cluster was mapped to the last row (and column) is "remapped" to row (and column) b
 - The rank of the matrix is reduced by one.

Another approach that is often used in distance matrix algorithms is virtual 
deletion; the "marking" the merged clusters (a and b) as "no longer in use". 
But doing this, the memory for the (working distance matrix) D entries that 
refer to the "retired" clusters remains in use.  The issue isn't that it isn't
deallocated, but that it needs to be read. Moving the entries in (what was) the
last column into the vacancies left by the removal of cluster b, and writing 
the entries for cluster u into (what was) the column for cluster a, reduces the
amount of memory in use (though, not the amount of memory allocated!).

Since the sum of the first N squares is N(N+1)(2N+1)/6 (approximately one third of the cube of N), the reduction in the expected number of cache fetches (or cache misses) resulting from access to the distance matrix, over the course of an execution is, for large enough N, about two thirds.  <i>If all of the distances in the distance matrix are actually examined, one every iteration, as they are in the NJ and BIONJ algorithms, but <b>not</b> in the NJ-R, BIONJ-R, and the other "-R" algorithms.</i>

Maintaining the entire matrix (and not just the upper or lower triangle) makes it
possible to do the memory accesses almost entirely sequentially (except for the
column rewriting and moving when clusters are moved.

In algorithms that have Variance Estimate matrices, operations (row and column overwrites, row and column deletes) are "mirrored" on the Variance Estimate matrices. 

Row (but not column!) operations are mirrored on the "sorted distance" (S) and "index" I matrices.  

Columns cannot easily be deleted out of existing rows of the S and I matrices (if the algorithm has them), because in each row of those arrays, then entries are sorted by ascending distance (so to find out which entry 
is for a column that is to be removed, a search would be necessary, and to
write an entry for the column for a newly joined cluster, an insert into 
a sorted array would be necessary). The I and S matrices contain entries
for clusters which have a cluster number less than that of the cluster 
mapped to the row they are in. As neighbour joining continues, some of these will be for clusters that are no longer under consideration, because
they have already been joined into another, newer, cluster. Distances to
these clusters are "skipped" over.

<h2>Working matrix reallocation</h2>
During the course of the execution of a distance matrix algorithm, as the number of rows and columns in use falls, less and less of the memory allocated to the matrix remains in use.  Periodically, the items still in use in the matrix are moved, so that a smaller block of sequential memory contains all the distances in the matrix (in row major order), with no "unused" memory between rows.


<h2>Treatment of duplicates</h2>
All of the decentTree distance-matrix algorithms have special treatment for sequences that
can be treated as identical (or; for taxa whose rows in initial distance matrix are identical).

<h2>Tie-breaking</h2>

<h2>Treatment of Rounding Error</h2>
Rounding error is ignored.

<h2>Comments</h2>
Removing columns from the *right* (and rows from the *bottom*) was probably a mistake. 
Columns should have been removed from the left (and matrix row pointers incremented).
There would have been a cache utilisation advantage, since the entries being moved 
would have been near at least some of the entries to be read at the start of the 
next search of a pair of clusters to merge.  Similarly, rows should have been removed
from the *top* of the matrix.
