add_executable(hod_tree
    headeronlydecenttree.cpp example_matrix.cpp
    ../utils/progress.cpp         ../utils/progress.h 
    ../utils/operatingsystem.cpp  ../utils/operatingsystem.h)

add_executable(vectordecenttree
    vectordecenttree.cpp example_matrix.cpp ../utils/progress.cpp
    ../utils/progress.cpp         ../utils/progress.h 
    ../utils/operatingsystem.cpp  ../utils/operatingsystem.h)

add_executable(differentvector
    differentvector.cpp           example_matrix.cpp 
    ../utils/progress.cpp         ../utils/progress.h 
    ../utils/operatingsystem.cpp  ../utils/operatingsystem.h)
