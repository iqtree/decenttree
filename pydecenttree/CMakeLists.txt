# was: find_package(PythonInterp 3.5 REQUIRED)
# was: find_package(PythonLibs   3.5 REQUIRED)
find_package(Python3 COMPONENTS Interpreter NumPy)
message("Python Include directory: ${PYTHON_INCLUDE_DIR}")
include_directories(${PYTHON_INCLUDE_DIR})
#message("Python Libraries:         ${PYTHON_LIBRARIES}")

exec_program(${PYTHON_EXECUTABLE}
             ARGS "-c \"import numpy; print(numpy.get_include())\""
             OUTPUT_VARIABLE NUMPY_INCLUDE_DIR
             RETURN_VALUE NUMPY_NOT_FOUND
            )
if(NUMPY_NOT_FOUND)
    message(FATAL_ERROR "NumPy headers not found")
endif()

message("Numpy Include directory:  ${NUMPY_INCLUDE_DIR}")
include_directories(${NUMPY_INCLUDE_DIR})
#message("Numpy Linker flags:       ${NUMPY_EXE_LINKER_FLAGS}")
#set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} ${NUMPY_EXE_LINKER_FLAGS}")

add_library(pydecenttree SHARED
    pydecenttree.cpp 
    ../starttree.cpp  ../starttree.h ../bionj.cpp ../bionj2.cpp
    ../flatmatrix.cpp ../flatmatrix.h
    ../utils/vectortypes.cpp ../utils/vectortypes.h
    ../utils/stringfunctions.cpp ../utils/stringfunctions.h
    ../utils/gzstream.cpp ../utils/gzstream.h
    ../utils/progress.cpp ../utils/progress.h
    ../utils/operatingsystem.cpp ../utils/operatingsystem.h
    )
# ../flatmatrix.cpp for flat matrix functions for writing to files
# Stuff in ../utils :
#   vectortypes.cpp for contains()
#   stringfunctions.cpp for StrVector::contains()
#   gzstream.cpp for zip and unzip support, pigzstream class.
#   progress.cpp for progress bar stuff, progress_display class.
#   operatingsystem.cpp for isStandardOutputATerminal()

target_link_libraries(pydecenttree ${PYTHON_LIBRARIES} Python3::NumPy)
if(ZLIB_FOUND)
  target_link_libraries(decenttree ${ZLIB_LIBRARIES})
else(ZLIB_FOUND)
  target_link_libraries(decenttree zlibstatic)
endif(ZLIB_FOUND)

if (APPLE OR WIN32 )            
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Xpreprocessor -fopenmp -pthread")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp -pthread")
endif()
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lz")
#message("Open MP Linker flags:     ${OpenMP_EXE_LINKER_FLAGS}")
#set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

#set_target_properties(pydecenttree PROPERTIES PREFIX "" OUTPUT_NAME "pydecenttree" LINKER_LANGUAGE C)
target_link_libraries(pydecenttree omp)

if(ZLIB_FOUND)
  message("Zlib libraries:           ${ZLIB_LIBRARIES}")
  target_link_libraries(pydecenttree "-static ${ZLIB_LIBRARIES}")
else(ZLIB_FOUND)
  message("Zlib libraries:           zlibstatic")
  target_link_libraries(pydecenttree zlibstatic)
endif(ZLIB_FOUND)
