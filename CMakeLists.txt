# ------------------------------- WARNING --------------------------------------------------
# This is just a debug build and does not generate valid make files for the project.
# File naming conventions suck...
# ------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.14)

project(arduino3dengine_debug C CXX)

# executable target
add_executable(arduino3dengine_debug
    "src/debug.cpp"
    "src/fixp_math.cpp"
    "src/linalg.cpp"
    "src/triangle.cpp"
    "src/util.cpp"
)

# add include directory for this project
target_include_directories(arduino3dengine_debug
    PRIVATE
        "include"
)

# enable C++17
target_compile_features(arduino3dengine_debug
    PRIVATE
        "cxx_std_17"
)