cmake_minimum_required(VERSION 3.14)
project(ShamirSecretSharing VERSION 1.0.0 LANGUAGES CXX)

# Enforce C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enforce strict, professional compiler warnings
if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Define the core library target
add_library(shamir_secret_sharing
    src/FiniteField.cpp
    src/Polynomial.cpp
    src/ShamirSecretSharing.cpp
)

# Expose the include/ directory to anyone who links against this library
target_include_directories(shamir_secret_sharing
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
# Enable CTest framework for the entire project
enable_testing()
# Tell CMake to process the tests directory
add_subdirectory(tests)