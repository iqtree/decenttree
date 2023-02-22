<h1>pydecenttree Python Extension</h1>
<h2>Introduction</h2>
pydecenttree is a C++ Python Extension that makes the distance matrix phylogeny inference functions of decenttree available to python users.

<h2>Methods</h2>

| Method name | Comments |
|-------------|---|
| getAlgorithmNames() | Returns a collection, containing the names of the available distance matrix phylogenetic inference algorithms.  Which algorithms are available will depend on whether vectorisation was enabled when pydecenttree was built. |
| constructTree() | Infers a phylogenetic tree. Returns a string, that contains the tree, in Newick format. | 

<h2>Parameters to constructTree()</h2>

| Parameter name | Type | Comments |
|-------------|---|---|
| algorithm | string | the name of the desired algorithm (if it is blank, the default algorithm  will be used) |
| sequences | collection of strings | The names of the sequences (these will be names of the nodes in the newick string that constructTree() returns). The number of sequences, **n**, must be at least 3.
| distances | see comments | May be a flat collection (or 1D numpy matrix) containing n*n numbers, a collection of n rows (each a collection of the n numbers in a row), or an n by n 2D numpy matrix
| number_of_threads | number | The number of threads.  If pydecenttree has been built with [openmp](https://en.wikipedia.org/wiki/OpenMP), this can be used to limit the number of threads of execution that pydecenttree will use. If it is not supplied, or is -1, as many threads will be used as there are cores available.  If pydecenttree has _not_ been built with [openmp](https://en.wikipedia.org/wiki/OpenMP), this parameter has no effect.
| precision | number | indicates how many digits of precision will be used by pydecenttree, to format the distances between nodes in the Newick tree string, it returns.
| verbosity | number | indicates how much information (if any) should be written to standard output during execution.

<h2>Building and installing the pydecenttree Python package</h2>
<h3>With Python 3.10 or earlier, on Mac OS</h3>
These instructions are for Python 3.10 (pydecenttree has not been built with Python 2), but the process should be similar with earlier versions of Python 3. Python 3.11 does not appear to allow the use of setup.py

On Macintosh.  From the decenttree folder (*after* you have built the C++ executables), to build,
install and test the pydecenttree run the following (replace python3.10 with the name of your python interpreter):

```
cd pydecenttree
export CFLAGS="-Xpreprocessor -fopenmp $CFLAGS"
export CXXFLAGS="-Xpreprocessor -fopenmp $CXXFLAGS"
rm -r build
rm -r dist
python3.10 setup.py build 
python3.10 setup.py install
python3.10 test_pydecenttree.py
```

<h3>With Python 3.11 or later, on Mac OS</h3>

On Macintosh.  From the decenttree folder (*after* you have built the C++ executables), to build,
install and test the pydecenttree package, run the following (replace python3.11 with the name of your python interpreter):

```
python3.11 -m ensurepip --upgrade
python3.11 -m pip install --upgrade pip
cd pydecenttree
export CFLAGS="-Xpreprocessor -fopenmp $CFLAGS"
export CXXFLAGS="-Xpreprocessor -fopenmp $CXXFLAGS"
rm -r build
rm -r dist
pip install -e . 
python3.11 test_pydecenttree.py
```

<h3>With Python 3.11, on Windows 10 (or 11)</h3>
<i>These instructions are probably not the best (and are as yet incomplete).
I've got as far as installing python and numpy, but I haven't figured out how
to get pip to build (let alone install) the pydecenttree module itself</i> -James.

Download Python via the Windows download page

[https://www.python.org/downloads/windows](https://www.python.org/downloads/windows).

Run the Python 3.11 app, and execute the commands
```
import ensurepip
ensurepip.bootstrap()
```

Open the command prompt and navigate to the folder where you installed python (for me this was c:\Users\james\AppData\Local\Programs\Python\Python311). Execute the command (alernatively you could add your Python install directory to your %PATH% and then you could execute the following command from any folder - I didn't):

```
python -m pip install numpy
```

Navigate to the pydecenttree folder (for me this was c:\Users\james\Source\repos\decenttree\pydecenttree).
Run a command <i>like</i> this (replace C:\Users\james\AppData\Local\Programs\Python\Python311 with the directory 
to which you installed Python):

```
C:\Users\james\AppData\Local\Programs\Python\Python311\Scripts\pip install -e .
```

(if you get an error message about it not being able to find zconf.h, you may need
to run CMake in the build subfolder of the decenttree project folder, either 
directly, or via VS Code or Microsoft VIsual Studio, to create a
build\zconf.h header file)

(this is building for me but I am getting a disturbing number of warnings)



