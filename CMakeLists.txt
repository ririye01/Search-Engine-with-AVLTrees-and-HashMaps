cmake_minimum_required(VERSION 3.15)
project(Search-Engine-with-AVLTrees-and-HashMaps)

# filesystem.h require C++17
set(CMAKE_CXX_STANDARD 17)

file(COPY sample_data/ DESTINATION sample_data/)

# show compiler output and enable warnings
set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(rapidJSONExample rapidJSONExample.cpp DSAVLTree.h DocumentParser.cpp DocumentParser.h SearchEngine.cpp SearchEngine.h Document.cpp Document.h porter2_stemmer.cpp porter2_stemmer.h Database.cpp Database.h DatabaseHandler.cpp DatabaseHandler.h)

# this makes sure we also link rapidjson
target_include_directories(rapidJSONExample PRIVATE rapidjson/)

set(CMAKE_VERBOSE_MAKEFILE OFF)
