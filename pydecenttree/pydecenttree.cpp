// Python Wrapper for decentTree's distance matrix phylogenetic inference
// implementations.
//
//  Copyright (C) 2021, James Barbetti.
//
//  LICENSE:
//* This program is free software; you can redistribute it and/or modify
//* it under the terms of the GNU General Public License as published by
//* the Free Software Foundation; either version 2 of the License, or
//* (at your option) any later version.
//*
//* This program is distributed in the hope that it will be useful,
//* but WITHOUT ANY WARRANTY; without even the implied warranty of
//* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//* GNU General Public License for more details.
//*
//* You should have received a copy of the GNU General Public License
//* along with this program; if not, write to the
//* Free Software Foundation, Inc.,
//* 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
//
//
//On Windows it might just be <Python.h>.  But on OS it's 
//a framework. The usual way around this is to 
//#include <Python/Python.h> on Mac OS.  But I've hacked 
//the -I parameter in CMakeLists.txt instead.
//-James B. 10-Jul-2022.
//
#define PY3K
#include <Python.h>              //yes, even on Mac OS.
#undef   USE_VECTORCLASS_LIBRARY
#define  USE_VECTORCLASS_LIBRARY 1 //Woo!

#if (USE_NUMPY_HEADERS)
#define PY_ARRAY_UNIQUE_SYMBOL MY_PyArray_API 
#include <numpy/arrayobject.h>   //for numpy helper functions
#endif 

#include <starttree.h>

/**
 * @brief A scoped reference to PyObject pointer, that will have
 *        its reference count decremented, via Py_DECREF().
 */
class ScopedPyObjectPtr {
public:
    PyObject *ptr;
    ScopedPyObjectPtr(): ptr(nullptr) {}
    explicit ScopedPyObjectPtr(PyObject* rhs) : ptr(rhs) {}
    ScopedPyObjectPtr(const ScopedPyObjectPtr& rhs): ptr(ptr) {
        if (ptr!=nullptr) {
            Py_INCREF(ptr);
        }
    }
    ~ScopedPyObjectPtr() {
        if (ptr!=nullptr) {
            Py_DECREF(ptr);
        }
    }
    bool operator==(const ScopedPyObjectPtr& rhs) { return ptr == rhs.ptr; }
    bool operator==(const PyObject* rhs) { return ptr == rhs; }
    operator  PyObject*() const { return ptr; }
    PyObject* getPtr()    const { return ptr; }
    bool      isNull()    const { return ptr==nullptr; }
};

/**
 * @brief  Append a string representation of a python object, to a StrVector.
 * @param  append_me - the python object
 * @param  to_me     - the StrVector (vector of strings based on std::vector)
 * @return true  - if the object had a string represenetation that could
 *                 be converted to UTF-8.
 * @return false - if the object didn't have a string representation,
 *                 or if the conversion to UTF-8 failed.
 * @note   I don't even know what this does if append_me is null.
 *         Please don't pass that! -James B. 
 * @note   The UTF-8 string, returned by PyUnicode_AsUTF8AndSize(),
 *         is automatically cleaned up when str is.
 */
bool appendStrVector(PyObject* append_me, StrVector& to_me) {
    #if (PY_MAJOR_VERSION >= 3)
        ScopedPyObjectPtr str ( PyObject_Str(append_me) );
    #else
        ScopedPyObjectPtr str ( PyObject_Unicode(append_me) );
    #endif

    if (str.isNull()) {
        return false;
    }
    Py_ssize_t  len  = 0;
    char const* utf8 = PyUnicode_AsUTF8AndSize(str, &len);
    if (utf8!=nullptr) {
        to_me.emplace_back(utf8, len);
    }
    return (utf8!=nullptr);
}

/**
 * @brief  Indicates whether an object parameter (sequence_arg)
 *         can be treated as a StrVector; and - if it can - loads its
 *         content into a StrVector instance supplied by reference.
 * @param  vector_name  - the formal name of the parameter (this is included in
 *                        error messages appended to (complaint)),
 *                        if any there are.
 * @param  sequence_arg - the python parameter (which will hopefully not be
 *                        nullptr, and will hopefully be a sequence)
 * @param  sequences    - reference to the StrVector to which (utf8) strings
 *                        representing the items in the sequence are to be 
 *                        appended.
 * @param  complaint    - reference to a std::stringstream.  The stream will
 *                        be appended if there is a problem (e.g. parameter
 *                        not supplied, or is not a sequence)
 * @return true  on success
 * @return false on failure
 * @note   different error message are written if the actual parameter
 *         (sequence_arg) is null, or is not a sequence.  If there is an error
 *         accessing an object in the sequence, or a problem determining its
 *         utf8 string representation, an error message will be returned for
 *         the FIRST such object, and the function will return, without 
 *         attempting to add utf8 strings representing the remaining objects
 *         in the sequence.
 */
bool isVectorOfString(const char* vector_name, PyObject*          sequence_arg,
                      StrVector&  sequences,   std::stringstream& complaint) {
    if (sequence_arg==nullptr) {
        complaint << vector_name << " was not supplied.";
        return false;
    }
    ScopedPyObjectPtr seq = PySequence_List(sequence_arg);
    if (seq==nullptr) {
        complaint << vector_name << " is not a sequence.";
        return false;
    }
    int number_of_sequences = PySequence_Fast_GET_SIZE(seq.getPtr());
    for (int i=0; i<number_of_sequences; ++i) {
        PyObject* item = PySequence_Fast_GET_ITEM(seq.getPtr(), i);
        if (item==nullptr) {
            complaint << vector_name << " could not access item " << i << ".";
            return false;
        }
        if (!appendStrVector(item, sequences)) {
            complaint << vector_name << " could not convert item " << i << " to string.";
            return false;
        }
        //Since PySequence_Fast_GET_ITEM returns a borrowed reference,
        //there's no need to decrement the reference count of (item).
    }
    return true;
}

/**
 * @brief  Given a python object (which had better not be null!), append
 *         a double precision value, derived from the object, via 
 *         PyFloat_AsDouble, to a DoubleVector.
 * @param  append_me - the object, that is (or can be converted to) a double
 *                     precision value.
 * @param  to_me     - reference to the DoubleVector to append the double to
 * @return true  - on success
 * @return false - on failure (if one occurred, according to PyErr_Occurred())
 * @note   This function isn't thread-safe, because PyErr_Occurred(),
 *         which it relies upon, indicates whether the most recent Python 
 *         function call errored.  If multiple threads are making Python
 *         function calls, it could report errors when errors did not
 *         occur (or report that errors did not occur when they did).
 */
bool appendDoubleVector(PyObject* append_me, DoubleVector& to_me) {
    double float_val = PyFloat_AsDouble(append_me);
    if (float_val==-1.0 && PyErr_Occurred()) {
        return false;
    }
    to_me.emplace_back(float_val);
    return true;
}

/**
 * @brief  Append double-precision values, supplied via a sequence parameter,
 *         to a DoubleVector (a vector of doubles).
 * @param  row_vector_name - the name of the formal parameter (to be quoted
 *                           in error messages, appended to (complaint), if
 *                           an error is encountered)
 * @param  seq_for_row     - the python object (which we hope will be non-null,
 *                           and hope will be a sequence).
 * @param  doubles         - reference to the DoubleVector to load up
 * @param  row_width_here  - to be used to return the number of items
 *                           in the sequence.  On error, this will be the
 *                           number of items read from the row. It is 
 *                           ADDED to, not SET (so usually, the caller 
 *                           should set it to zero before calling this fn).
 * @param  complaint       - reference to a std::stringstream.  The stream will
 *                           be appended if there is a problem (e.g. parameter
 *                           not supplied, or is not a sequence)
 * @return true  - on success
 * @return false - on failure
 * @note   it is assumed that the caller owns seq_for_row and controls its
 *         reference count (or in Python terms, it is assumed that seq_for_row
 *         is a borrowed reference).
 * @note   it is assumed that row_width_here has already been intialized
 *         (probably to zero).
 * @note   Although in practice, when this function is called, it is always
 *         passed a non-null python object that is a sequence, it does NOT
 *         assume either that seq_for_row is null, OR that it is a sequence.
 */
bool appendDoublesToVector(const std::string& row_vector_name, PyObject* seq_for_row, 
                           DoubleVector& doubles, size_t& row_width_here, 
                           std::stringstream& complaint ) {
    if (sequence_arg==nullptr) {
        complaint << row_vector_name << " was not supplied.";
        return false;
    }
    ScopedPyObjectPtr seq = PySequence_List(sequence_arg);
    if (seq==nullptr) {
        complaint << row_vector_name << " is not a sequence.";
        return false;
    }
    int number_of_items = PySequence_Fast_GET_SIZE(seq_for_row);
    for (int i=0; i<number_of_items; ++i) {
        PyObject* item = PySequence_Fast_GET_ITEM(seq_for_row, i);
        if (item==nullptr) {
            complaint << row_vector_name << " could not access item " << i << ".";
            return false;
        }
        if (PySequence_Check(item)==1) {
            complaint << " item " << i << " of " << row_vector_name 
                      << " was a sequence (not allowed).";
        }
        else if (!appendDoubleVector(item, doubles)) {
            complaint << row_vector_name << ": could not convert item " 
                      << i << " to double.";
            return false;
        }
        ++row_width_here;
    }
    return true;
}

/**
 * @brief  Reads doubles (either as "flat" sequence, or as a sequence of
 *         row sequences, such that each row sequence has the same number
 *         of doubles in it, into a vector).
 * @param  vector_name   - the name of the formal parameter (const char*)
 * @param  vector_arg    - the argument (a python object)
 * @param  doubles       - reference to the DoubleVector to which to append
 *                         the doubles, read from the "flat" or "row/major"
 *                         sequence, passed in via (vector_arg).
 * @param  element_data  - will be set to the start of the data allocated
 *                         for the DoubleVector (only on success), or to 
 *                         nullptr (only on failure).
 * @param  element_count - will be set to the size of the data in DoubleVector
 *                         (only on success), or to 0 (only on failure).
 * @param  complaint     - reference to a std::stringstream.  The stream will
 *                         be appended if there is a problem (e.g. parameter
 *                         not supplied, or is not a sequence)
 * @return true  - on success
 * @return false - on failure
 * @note   if the parameter (vector_arg) is null (not supplied), an error 
 *         saying so will be appended to (complaint) and false will be returned.  
 * @note   if it's not a sequence, an error saying so will be appended to
 *         (complaint) and false will be returned.
 * @note   if it's a "flat" sequence it'll just be read.  if it's a "row-major"
 *         sequence of row sequences, each of the rows will be read.
 *         if any two rows have a different number of items, and error saying
 *         so will be appended to (complaint) and false will be returned.
 *         
 */
bool isVectorOfDouble(const char*   vector_name,   PyObject* vector_arg,
                      DoubleVector& doubles,       const double*& element_data,
                      size_t&       element_count, std::stringstream& complaint) {
    size_t row_count = 0; //Number of row sequences read
    size_t row_width = 0; //Width of all row sequences seen so far
    element_data  = nullptr;
    element_count = 0;
    if (vector_arg==nullptr) {
        complaint << vector_name << " was not supplied.";
        return false;
    }
    ScopedPyObjectPtr seq = PySequence_List(vector_arg);
    if (seq==nullptr) {
        complaint << vector_name << " is not a sequence.";
        return false;
    }
    int number_of_items = PySequence_Fast_GET_SIZE(seq.getPtr());
    for (int i=0; i<number_of_items; ++i) {
        PyObject* item = PySequence_Fast_GET_ITEM(seq.getPtr(), i);
        if (item==nullptr) {
            complaint << vector_name << " could not access item " << i << ".";
            return false;
        }
        if (PySequence_Check(item)==1) {
            ScopedPyObjectPtr seq_for_row = PySequence_List(item);
            //Nested sequence
            std::stringstream row_seq_name;
            size_t            row_width_here=0;
            row_seq_name << "row [" << i << "] of " << vector_name;
            std::string row_vector_name = row_seq_name.str();
            if (!appendDoublesToVector(row_vector_name, seq_for_row, 
                                       doubles, row_width_here, complaint )) {
                return false;
            }
            if (row_count==0) {
                if (row_width_here<doubles.size()) {
                    complaint << "can't mix scalars and row vectors"
                              << " in " << vector_name << ".";
                    return false;
                }
                row_width = row_width_here;
            }
            ++row_count;
            if (row_width!=row_width_here) {
                complaint << row_vector_name << " has rank "
                    << row_width_here << " that differs with"
                    << " the rank (" << row_width << ") of previous rows"
                    << "\n";
                return false;
            }
        }
        else if (row_count!=0) {
            complaint << "can't mix row vectors and scalars"
                        << " in " << vector_name << ".";
            return false;
        }
        else if (!appendDoubleVector(item, doubles)) {
            complaint << vector_name << " could not convert item " 
                      << i << " to double.";
            return false;
        } 
    }

    element_data  = doubles.data();
    element_count = doubles.size();
    return true;
}

/**
 * @brief  Returns true if a python object is a NumPy matrix.
 * @param  arg - the python object (which may be nullptr)
 * @return true - if the python object is non-null and is a NumPy matrix.
 * @return false - if the python object is null, or is not a NumPy matrix.
 */
bool isMatrix(PyObject* arg) {
    #if (USE_NUMPY_HEADERS)
        return PyArray_API!=nullptr && PyArray_Check(arg)!=0;
    #else
        return false;
    #endif
}

/**
 * @brief  Attempts to read a matrix into a DoubleVector.
 * @param  matrix_name     - the formal name of the matrix argument
 *                           (this is used in error messages if there is
 *                           a problem)
 * @param  possible_matrix - the python parameter (which may be null,
 *                           and need not be a NumPy matrix argument).)
 * @param  element_data    - on success, pointer to the data in the matrix
 * @param  element_count   - on success, count of items in the matrix
 * @param  complaint       - reference to a std::stringstream. To be
 *                           ppended if there is a problem (e.g. parameter
 *                           not supplied, or is not a NumPy array)
 * @return true  - on success
 * @return false - on failure
 * @note   always returns false if USE_NUMPY_HEADERS is not set
 * @note   the data can only be accessed directly, without a conversion,
 *         if the NumPy array has a type of NPY_DOUBLE. If it's any other type,
 *         an error message is appended to (complaint) and false returned.
 */
bool isMatrixOfDouble(const char*        matrix_name,  PyObject* possible_matrix, 
                      const double*&     element_data, size_t&   element_count, 
                      std::stringstream& complaint) {            
    element_count = 0;
    if (!isMatrix(possible_matrix)) {
        complaint << matrix_name << " matrix"
                  << " is not a matrix of type Float";
        return false;
    }

    #if (!USE_NUMPY_HEADERS)
        return false;
    #else
        PyArrayObject* matrix = reinterpret_cast<PyArrayObject*>(possible_matrix);
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
            return false;                  
        }
        element_count = 1;
        for (int d = 0; d < dimensions; ++d) {
            element_count *= matrix->dimensions[d];
        }
        element_data = reinterpret_cast<double*> PyArray_DATA(matrix);
        return true;
    #endif
}

/**
 * @brief  If _OPENMP is support, configure _OPENMP to use the specified
 *         number of threads.
 * @param  number_of_threads - The number of threads to use, or 0, if the
 *                             OpenMP default number of threads (probably 
 *                             the maximum possible number of threads) is
 *                             to be used.
 * @param  complaint         - A reference to a std:stringstream that will
 *                             be appended if an error occurs. Maybe.
 *                             Someday. If I ever decide to treat -ve 
 *                             threadcount as an error condition.  -James B.
 *
 * @return true  - on success (at present, always succeds)
 * @note   Does nothing and returns true if _OPENMP symbol is undefined or zero.
 * @note   Negative thread counts are treated as equivalent to 0 ("all").
 * @note   A thread count of 0 or less DOESN'T result in a call to determine
 *         the OpenMP default.  The number of threads is merely left unchanged.
 */
bool obeyThreadCount(int number_of_threads, std::stringstream& complaint) {
    #ifdef _OPENMP
        std::cout <<"OpenMP is defined\n";
        if (0<number_of_threads) {
            int maxThreadCount = omp_get_max_threads();
            if (maxThreadCount < number_of_threads ) {
                //For now, don't care.  Don't even warn about it.
                //Some day, maybe write to complaint and return false
            } else {
                omp_set_num_threads(number_of_threads);
            }
        }
        //If number of threads < 1 use the OMP default.
    #else
        //Ignore it.  Some day, maybe complain.
    #endif
    return true;
}

/**
 * @brief  Convert a std::string into a string that can be returned to
 *         Python.
 * @param  convert_me - the string to convert
 * @return PyObject* a new unicode reference to a Unicode object that
 *         contains the (unicode) conversion of (convert_me).
 */
PyObject* StringToPythonString(const std::string& convert_me) {
    #if PY_MAJOR_VERSION >= 3
        return PyUnicode_FromString(convert_me.c_str());
    #else
        return PyString_FromString(convert_me.c_str());
    #endif
}

/**
 * @brief  Impleemnts PyDecentTree.constructTree
 * @param  self     - the pydcenttree instance (a Python object)
 * @param  args     - arguments (a Python object)
 * @param  keywords - keywords (a Python object)
 * @return PyObject* - on success, a python string representing the 
 *                     newick-format representation of the phylogenetic tree, 
 *                     inferred by the requested distance matrix algorithm,
 *                     for the supplied sequence names and distance matrix.
 *                   - on failure, nullptr (PyErr_SetString is called to
 *                     report back to Python what the problem was).
 */
static PyObject* pydecenttree_constructTree(PyObject* self, PyObject* args, 
                                            PyObject* keywords)
{
    const char* argument_names[] = {
        "algorithm", "sequences", "distances", 
        "number_of_threads", "precision", 
        "verbosity", nullptr
    };
    char*          algorithm_name    = nullptr;
    PyObject*      distance_arg      = nullptr;
    int            number_of_threads = 0;
    int            precision         = 6; //should be default precision
    int            verbosity         = 0; //>0 to say what's happening
    const double*  distance_data     = nullptr;
    size_t         distance_entries  = 0;
    PyObject*      sequence_arg      = nullptr;

    if (!PyArg_ParseTupleAndKeywords(args, keywords, "sOO|iii", 
                                        const_cast<char**>(&argument_names[0]),
                                        &algorithm_name,  &sequence_arg,
                                        &distance_arg, &number_of_threads,
                                        &precision, &verbosity)) 
    {
        //Parsing failure
        return nullptr;
    }        
    std::stringstream complaint;
    complaint << "Error: ";
    StartTree::BuilderInterface* algorithm = nullptr;
    if (algorithm_name==nullptr) {
        complaint << "Algorithm name not specified";
    } else {
        algorithm = StartTree::Registry::getInstance().getTreeBuilderByName(algorithm_name);
    }
    std::string  problem;
    std::string  tree_string;
    StrVector    sequences;
    DoubleVector local_distance_vector; //Not needed if distance_matrix is NumPy array
    if (algorithm==nullptr) {
        if (algorithm_name!=nullptr) {
            complaint << "Algorithm " << algorithm_name << " not found.";
        }
    } else {
        if (distance_arg==nullptr) {
            complaint << "No distances were supplied";
        }
        else if (!isVectorOfString("sequencenames", sequence_arg,
                                   sequences, complaint)) {
        }
        else if (sequences.size()<3) {
            complaint << "sequencenames contains only " << sequences.size()
                      << " sequences (must have at least 3).";
        }
        else if (isMatrix(distance_arg) && !isMatrixOfDouble("distance", distance_arg,
                                                 distance_data, distance_entries, complaint)) {
            //Will have set complaint
            //Problem. What if lower precision type is wanted?
        }
        else if (!isVectorOfDouble("distance", distance_arg, local_distance_vector,
                                   distance_data, distance_entries, complaint )) {
            //Will have set complaint
            //To think about later.  Might caller want to request
            //single precision?  Because that uses about half as much
            //memory and is ~ 20% *faster* (if a bit less accurate).
        }
        else if (distance_entries != sequences.size() * sequences.size()) {
            complaint << "There are " << sequences.size() << " sequences"
                      << " but the distance matrix"
                      << " contains " << distance_entries << " elements"
                      << " (should be " << (sequences.size() * sequences.size()) << ").";
        }
        else if (!obeyThreadCount(number_of_threads, complaint)) {
            //Will have set complaint
        }
        else if (precision<1)
            complaint << "Cannot have precision (" << precision << ")"
                      << " less than 1";
        else {
            if (verbosity==0) {
                algorithm->beSilent();
            }
            if (1<verbosity) {
                std::cout << "Sequences: " << sequences.join(",") << "\n";
                std::cout << "First two distances: " 
                          << distance_data[0] << " and "
                          << distance_data[1] << ".\n";
            }
            if (!algorithm->constructTreeStringInMemory
                 ( sequences, distance_data, tree_string )) {
                complaint << "Call to constructTreeStringInMemory failed "
                          << " for algorithm " << algorithm_name << ".";
                tree_string.clear();
            }
        }
    }
    if (tree_string.empty()) {
        PyErr_SetString(PyExc_TypeError, complaint.str().c_str());
        return nullptr;
    } else {
        PyObject* tree_result = StringToPythonString(tree_string);
        return tree_result;
    }
}

/**
 * @brief  Convert a StrVector into a Python List of strings
 * @param  string_vector - the string vector whose strings are to be
 *                         included in the Python List.
 * @return PyObject* - a new reference to a Python List ojbect
 */
PyObject* StringVectorToPythonList(const StrVector& string_vector) {
    PyObject* list = PyList_New(string_vector.size());
    for (size_t i=0; i < string_vector.size() ; ++i ) {
        const std::string& name = string_vector[i];
        PyObject* item = StringToPythonString(name);
        if (item==nullptr) {
            continue;
        }
        if (PyList_SetItem(list,i,item) != 0) {
            Py_DECREF(item);
            Py_DECREF(list);
            return nullptr;
        }
    }
    return list;
}

/**
 * @brief  Return a Python list containing the names of the available
 *         algorithms.
 * @param  self      - the pydcenttree instance (a Python object)
 * @param  args      - arguments (a Python object)
 * @param  keywords  - keywords (a Python object)
 * @return PyObject* - a new Python list object (containing the names).
 */
static PyObject* pydecenttree_getAlgorithmNames
    ( PyObject* self, PyObject* args, PyObject* keywords ) {
    const char* argument_names[] = {
        "descriptions", nullptr
    };
    int descriptions = 0;
    if (!PyArg_ParseTupleAndKeywords(args, keywords, "|i", 
                                     const_cast<char**>(&argument_names[0]), 
                                     &descriptions)) {
        return nullptr;
    }
    bool withDescriptions = (descriptions!=0);
    StartTree::Registry& registry = StartTree::Registry::getInstance();
    auto names   = registry.getVectorOfTreeBuilderNames(withDescriptions);
    return StringVectorToPythonList(names);
}

static PyMethodDef pydecenttree_methods[3] = {
    { "constructTree", (PyCFunction) pydecenttree_constructTree,
      METH_VARARGS | METH_KEYWORDS, "Construct tree" },
    { "getAlgorithmNames", (PyCFunction) pydecenttree_getAlgorithmNames,
      METH_VARARGS | METH_KEYWORDS, 
      "Return a list of available algorithms" },
    { NULL, NULL, 0, NULL },
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
        #if (USE_NUMPY_HEADERS)
            import_array();
        #endif
        return PyModule_Create(&pydecenttree);
    }
};