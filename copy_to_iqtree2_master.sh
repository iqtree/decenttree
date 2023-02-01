#!/bin/sh
#Copies the current versions of files to iqtree2 (dev branch).
#Opposite of decenttree_update.sh
#  
export DMT=../iqtree_master/distancematrixtree
cp decenttree.cpp flatmatrix.cpp flatmatrix.h starttree.cpp starttree.h ${DMT}
cp bionj.cpp bionj2.cpp bionj2.h upgma.h nj.h rapidnj.h auctionmatrix.h ${DMT}
cp clustertree.h distancematrix.h stitchup.cpp sequence.cpp sequence.h  ${DMT}
cp hashrow.h fancyrapidnj.h ${DMT}
cd utils
export UTILS=../../iqtree_master/utils
cp argument.cpp argument.h               ${UTILS}
cp gzstream.cpp gzstream.h heapsort.h    ${UTILS}
cp progress.cpp progress.h               ${UTILS}
cp operatingsystem.cpp operatingsystem.h ${UTILS}
cp timeutil.h my_assert.h safe_io.h      ${UTILS}
cp parallel_mergesort.h parallel_sort.h  ${UTILS}
cp vectortypes.cpp vectortypes.h         ${UTILS}
cp hammingdistance.h                     ${UTILS}
cp stringfunctions.h stringfunctions.cpp ${UTILS}
cd ..
