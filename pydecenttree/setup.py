#from   sysconfig import get_paths
import numpy
from   distutils.core import setup, Extension

numpy_include = numpy.get_include()

#python_include = get_paths() 
#(but this doesn't seem necessary, so I've commented it out)

module1 = Extension("pydecenttree",
                    define_macros = [('DECENT_TREE',              '1'),
                                     ('USE_VECTORCLASS_LIBRARY',  '1'),
                                     ('USE_BIONJ_2009',           '0')],
                    sources = ["pydecenttree.cpp",  "../starttree.cpp",
                               "../bionj2.cpp",     "../flatmatrix.cpp",
                               "../utils/vectortypes.cpp",
                               "../utils/stringfunctions.cpp"],
                    include_dirs = [numpy_include, "..", "../build"],
                    extra_compile_args=['-std=c++11'],
                    language = "c++")

#Todo: Consider adding additional macros:
#USE_PROGRESS_DISPLAY=1
#USE_GZSTREAM=1
#
#Todo: want extra_compile_args "-fopenmp=libomp"
#But the compiler Python is defaulting to doesn't allow it.

#Might eventually need these...
#Old BIONJ (but I don't plan to support this!)
#    ../bionj.cpp
#Compression:
#    ../utils/gzstream.cpp ../utils/gzstream.h
#Progress bars:
#    ../utils/progress.cpp ../utils/progress.h
#    ../utils/operatingsystem.cpp ../utils/operatingsystem.h

def main():
    setup(name="pydecenttree",
          version="1.0.0",
          description="Python interface for the decenttree library function",
          author="James Barbetti (2022)",
          author_email="james_barbetti@yahoo.com",
          ext_modules=[module1],
          setup_requires = ["numpy"],
          install_requires = ["numpy"])

if __name__ == "__main__":
    main()
