//If you want to use Open MP, on Windows, you will need to ensure that
//the (64-bit) version of libiomp5md.dll can be found in the library path
//when your executable runs.

#define USE_GZSTREAM            0 //If you linked in gzstream.cpp, this could be set to 1.
                                  //(not that this example needs gz formatting)
#define USE_PROGRESS_DISPLAY    1 //If you linked in progress.cpp, this could be set to 1.
                                  //to get progress bars (not much point on small inputs!)
                                  //Progress reporting depends on functions in the progress.cpp 
                                  //in the main decenttree folder.
#define USE_VECTORCLASS_LIBRARY 1 //For an input this small, vectorisation doesn't matter.
#define DECENT_TREE             1 //Tells shared headers that decenttree, rather than
                                  //iqtree2, is being built. 

#include <distancematrix.h>	//for loadDistanceMatrixFromOpenFile
#include <rapidnj.h>		//for RapidNJ
#include <sstream>          //for std::istringstream
#include "example_matrix.h" //for example_matrix string

template <class T> void testMatrix
    (const std::string &infile_name, bool silent, T& r) {
    loadDistanceMatrixInto(infile_name, silent, r);
	r.constructTree();
}

void example_2() {
	const std::string input_file("./example.dist");

    std::ofstream dist;
    dist.open(input_file.c_str(), std::ios_base::out);
    dist << example_matrix;
    dist.close();

	StartTree::NJMatrix<NJFloat> r1;
	StartTree::VectorNJ          r2;
    StartTree::RapidNJ           r3;

    testMatrix(input_file, true, r1);
    testMatrix(input_file, true, r2);
    testMatrix(input_file, true, r3);
    
    StartTree::RapidNJ           r4;
    r4.beSilent();

    testMatrix(input_file, false, r4);
}

int main(int argc, char* argv[]) {
    printf("Try a conventional NJ and a vectorized NJ implementation\n");
	example_2();
	return 0;
}