#from   sysconfig import get_paths
import numpy
from   distutils.core import setup, Extension

numpy_include = numpy.get_include()

#python_include = get_paths() 
#(but this doesn't seem necessary, so I've commented it out)

dirs   = [numpy_include, "..", "../build"]
flags  = ['-std=c++11']
link_flags = []

#
#This is how I hacked OpenMP support on OS X 12.4
#Outside setup.py.. run these:
#
#>  export CFLAGS="-Xpreprocessor -fopenmp $CFLAGS"
#>  export CXXFLAGS="-Xpreprocessor -fopenmp $CXXFLAGS"
#b
#(you need to set both CFLAGS and CXXFLAGS!  Don't know why)
#...but I get lots of repeated warnings out of signal.h when I build.
#
import os
if ('CXXFLAGS' in os.environ):
    if (os.environ['CXXFLAGS'].find('-Xpreprocessor')!=-1):
        link_flags.append('-lomp')
        dirs.append('/Library/Developer/CommandLineTools/SDKs/MacOSX10.15.sdk/usr/include')

module1 = Extension("pydecenttree",
                    define_macros = [('DECENT_TREE',              '1'),
                                     ('USE_VECTORCLASS_LIBRARY',  '1'),
                                     ('USE_PROGRESS_DISPLAY',     '1'),
                                     ('USE_BIONJ_2009',           '0')],
                    sources = ["pydecenttree.cpp",  "../starttree.cpp",
                               "../bionj2.cpp",     "../flatmatrix.cpp",
                               "../utils/vectortypes.cpp",
                               "../utils/stringfunctions.cpp",
                               "../utils/progress.cpp",
                               "../utils/operatingsystem.cpp" ],
                    include_dirs = dirs,
                    extra_compile_args = flags,
                    extra_link_args= link_flags,
                    language = "c++")

#If USE_PROGRESS_DISPLAY is set, ../utils/progress.cpp
#and ../utils/operatingsystem.cpp are needed.

#Todo: Consider adding additional macros:
#USE_GZSTREAM=1
#
#Todo: want extra_compile_args "-fopenmp=libomp"
#But the compiler Python is defaulting to doesn't allow it.

#Might eventually need these...
#Old BIONJ (but I don't plan to support this!)
#    ../bionj.cpp
#Compression:
#    ../utils/gzstream.cpp ../utils/gzstream.h
#

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
