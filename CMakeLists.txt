Project(Testgmsh)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(testgmsh bin/main.cpp)
add_executable(quadMeshing bin/quadMeshing.cpp)
add_executable(simplexMeshing bin/simplexMeshing.cpp)

if(NOT GMSH_LIB)
    set(GMSH_LIB /home/fprotais/gmsh-git-Linux64-sdk/lib/libgmsh.so)
endif()
if(NOT GMSH_INCLUDE_DIR)
    set(GMSH_INCLUDE_DIR /home/fprotais/gmsh-git-Linux64-sdk/include/)
endif()

target_link_libraries(testgmsh PUBLIC ${GMSH_LIB})
target_include_directories(testgmsh PUBLIC ${GMSH_INCLUDE_DIR})
target_link_libraries(quadMeshing PUBLIC ${GMSH_LIB})
target_include_directories(quadMeshing PUBLIC ${GMSH_INCLUDE_DIR})
target_link_libraries(simplexMeshing PUBLIC ${GMSH_LIB})
target_include_directories(simplexMeshing PUBLIC ${GMSH_INCLUDE_DIR})