//
//On Windows it might just be <Python.h>.  But on OS it's 
//a framework. The usual way around this is to #include <Python/Python.h>
//on Mac OS.  But I've hacked the -I parameter in CMakeLists.txt instead.
//-James B. 10-Jul-2022.
//
#define PY3K
#include <Python.h>              //yes, even on Mac OS.
#undef   USE_VECTORCLASS_LIBRARY
#define  USE_VECTORCLASS_LIBRARY 1 //Woo!
#define  NO_IMPORT_ARRAY         //Ee-uw. See: https://numpy.org/doc/1.13/reference/c-api.array.html
#include <numpy/arrayobject.h>   //for numpy helper functions
#include <starttree.h>

bool isVectorOfString(const char* vector_name, PyArrayObject* vector,
                      StrVector&  sequences,   std::string&   why_not) {
    return true;
}

bool isMatrixOfDouble(const char*    matrix_name,  PyArrayObject* matrix, 
                      const double*& element_data, intptr_t&      element_count, 
                      std::string& why_not) {
    element_count = 0;
    std::stringstream complaint;
    if (matrix->descr->type_num != NPY_DOUBLE) {
        complaint << matrix_name << " matrix"
                  << " is not a matrix of type Float";
        return false;
    }
    auto dimensions = matrix->nd;
    if (dimensions < 1 || 2<dimensions) {
        complaint << matrix_name << "matrix"
                  << " has " << dimensions << " dimensions"
                  << " (only 1 and 2 dimensional matrices are allowed).";
        why_not = complaint.str();
        return false;                  
    }
    element_count = 1;
    for (int d = 0; d < dimensions; ++d) {
        element_count *= matrix->dimensions[d];
    }
    element_data = reinterpret_cast<double*> PyArray_DATA(matrix);

    return true;
}

static PyObject* pydecenttree_constructTree(PyObject* self, PyObject* args, 
                                            PyObject* keywords)
{
    const char* argument_names[] = {
        "algorithm", "sequences", "distances", "precision", NULL
    };
    char*          algorithm_name   = nullptr;
    PyArrayObject* distance_matrix  = nullptr;
    int            precision        = 6; //should be default precision
    const double*  distance_data    = nullptr;
    intptr_t       distance_entries = 0;
    PyArrayObject* sequence_vector  = nullptr;


    if (!PyArg_ParseTupleAndKeywords(args, keywords, "sAO!i", 
                                        const_cast<char**>(&argument_names[0]),
                                        &algorithm_name,  &sequence_vector,
                                        &distance_matrix, &precision)) 
    {
        return NULL;
    }        
    std::stringstream complaint;
    if (algorithm_name==NULL) {
        complaint << "Error: Algorithm " << algorithm_name << " not found.";
    }
    auto algorithm = StartTree::Factory::getInstance().getTreeBuilderByName(algorithm_name);
    std::string       problem;
    std::string       tree_string;
    StrVector         sequences;
    if (algorithm==nullptr) {
        complaint << "Error: Algorithm " << algorithm_name << " not found.";
    } else {
        if (NULL == distance_matrix) {
            complaint << "Error: No distances were supplied";
        }
        else if (!isVectorOfString("sequencenames", sequence_vector,
                               sequences, problem)) {
            complaint << "Error: " << problem;
        }
        else if (sequences.size()<3) {
            complaint << "Error: sequencenames contains only " << sequences.size()
                      << " sequences (must have at least 3).";
        }
        else if (!isMatrixOfDouble("distance", distance_matrix,
                                   distance_data, distance_entries, problem)) {
            complaint << "Error: " << problem;
        }
        else if (distance_entries != sequences.size() * sequences.size()) {
            complaint << "Error: There are " << sequences.size() << " sequences"
                      << " but the distance matrix"
                      << " contains " << distance_entries << " elements"
                      << " (should be " << (sequences.size() * sequences.size()) << ").";
        }
        else {
            algorithm->beSilent();
            if (!algorithm->constructTreeStringInMemory
                 ( sequences, distance_data, tree_string )) {
                complaint << "Error: Call to constructTreeStringInMemory failed "
                          << " for algorithm " << algorithm_name << ".";
            }
        }
    }
    if (tree_string.empty()) {
        tree_string = complaint.str();
    }
    Py_RETURN_NONE;
}

static PyMethodDef pydecenttree_methods[] = {
    { "constructTree", (PyCFunction) pydecenttree_constructTree,
        METH_VARARGS | METH_KEYWORDS, "Construct tree" },
    { NULL, NULL, 0, NULL }
};

static PyModuleDef pydecenttree = {
    PyModuleDef_HEAD_INIT,
    "pydecenttree",
    "", /* module doco */
    -1, /* no per-instance state */
    pydecenttree_methods
};

extern "C" {
    PyMODINIT_FUNC PyInit_pydecenttree(void) {
        return PyModule_Create(&pydecenttree);
    }
};