################################################################################
#                                                                              #
#   OpenNN: Open Neural Networks Library                                       #
#   www.intelnics.com/opennn                                                   #
#                                                                              #
#   O P E N N N   P R O J E C T                                                #
#                                                                              #
#   Roberto Lopez                                                              #
#   Intelnics - The artificial intelligence company                            #
#   robertolopez@intelnics.com                                                 #
#                                                                              #
################################################################################

cmake_minimum_required(VERSION 2.8)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

project(OpenNN)
set(MAJOR_VERSION 1)
set(MINOR_VERSION 0)
set(PATCH_VERSION 0)
set(VERSION ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/source")
