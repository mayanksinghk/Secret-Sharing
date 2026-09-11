# tests/CMakeLists.txt

include(FetchContent)

# Automatically download and configure Google Test
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Define the test executable
add_executable(shamir_tests
    FiniteFieldTest.cpp
    PolynomialTest.cpp
    ShamirSecretSharingTest.cpp
)

# Link your core library and Google Test to the test executable
target_link_libraries(shamir_tests
    PRIVATE
        shamir_secret_sharing
        gtest_main
)

# Register the test with CMake's testing framework
include(GoogleTest)
gtest_discover_tests(shamir_tests)