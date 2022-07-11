#undef  USE_PROGRESS_DISPLAY
#undef  USE_VECTORCLASS_LIBRARY
#undef  DECENT_TREE
#undef  USE_GZSTREAM
#define USE_PROGRESS_DISPLAY    1 //Even though there's not much point on an input this small.
#define USE_VECTORCLASS_LIBRARY 1 //For an input this small, vectorisation doesn't matter.
#define DECENT_TREE             1 //Tells shared headers that decenttree, rather than
                                  //iqtree2, is being built. 
#define USE_GZSTREAM            0 //Don't need this, not zipping or unzipping 

#include "example_matrix.h"
#include "fakevector.h"
#include <rapidnj.h>

typedef StartTree::VectorizedBoundingMatrix
        <double, MyFloatVector, MyBoolVector> 
        MyVBM;

int main(int argc, char* argv[]) {

    progress_display::setProgressDisplay(true);
    
    MyVBM r;
	std::istringstream input_file(example_matrix);
	loadDistanceMatrixFromOpenFile(input_file, false, r);
	r.constructTree();

	int precision = 6;
	std::string newickTreeFilePath = "STDOUT";
	r.writeTreeFile(precision, newickTreeFilePath);
}