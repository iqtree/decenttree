#!/bin/sh
#
#Copies over the current versions of files from iqtree2 (dev branch).
#Every source file, apart from:
#   1.  decenttree_config.h.in
#   2.  decentree_config.h
#   3.  decenttree_msvc_config.h
#   4.  headeronlydecenttree.cpp
#   5.  CMakeLists.txt
#   6.  CMakeSettings.json
#.  7.	This file (decenttree_update.sh)
#  
cd ../iqtree2/utils
cp decenttree.cpp flatmatrix.cpp flatmatrix.h starttree.cpp starttree.h ../../decenttree
cp bionj.cpp bionj2.cpp bionj2.h upgma.h nj.h rapidnj.h auctionmatrix.h ../../decenttree
cp clustertree.h distancematrix.h hammingdistance.h stitchup.cpp        ../../decenttree
cp heapsort.h gzstream.cpp gzstream.h progress.cpp progress.h safe_io.h ../../decenttree
cp operatingsystem.cpp operatingsystem.h timeutil.h my_assert.h         ../../decenttree
cp parallel_mergesort.h parallel_sort.h                                 ../../decenttree
cd ..
cp -R zlib-1.2.7      ../decenttree
cp -R lib             ../decenttree
cp -R lib32           ../decenttree
cp -R libmac          ../decenttree
cp -R vectorclass     ../decenttree
cp iqtree_config.h.in ../decenttree
cp LICENSE            ../decenttree
cd ../decentTree
