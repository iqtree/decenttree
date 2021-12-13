//If you want to use Open MP, on Windows, you will need to ensure that
//the (64-bit) version of libiomp5md.dll can be found in the library path
//when your executable runs.

#define USE_GZSTREAM            0 //If you linked in gzstream.cpp, this could be set to 1.
                                  //(not that this example needs gz formatting)
#define USE_PROGRESS_DISPLAY    0 //If you linked in progress.cpp, this could be set to 1.
                                  //to get progress bars (not much point on small inputs!)
#define USE_VECTORCLASS_LIBRARY 0 //For an input this small, vectorisation doesn't matter.
#define DECENT_TREE             1 //Tells shared headers that decenttree, rather than
                                  //iqtree2, is being built. 

#include <distancematrix.h>	//for loadDistanceMatrixFromOpenFile
#include <rapidnj.h>		//for RapidNJ
#include <sstream>          //for std::istringstream
#include "example_matrix.h" //for example_matrix string

void example_1() {
	StartTree::RapidNJ r;

	std::istringstream input_file(example_matrix);
	loadDistanceMatrixFromOpenFile(input_file, false, r);
	r.constructTree();

	int precision = 6;
	std::string newickTreeFilePath = "STDOUT";
	r.writeTreeFile(precision, newickTreeFilePath);
}

int main(int argc, char* argv[]) {
	example_1();
	return 0;
}