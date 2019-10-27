cmake_minimum_required(VERSION 3.14)
project(linx_search_challenge)

set(CMAKE_CXX_STANDARD 17)

set(Headers
        headers/Index.hpp
        headers/Utils.hpp
)

set(Sources
        src/Index.cpp
        src/Utils.cpp
        main.cpp
        )

add_executable(processador ${Headers} ${Sources} )