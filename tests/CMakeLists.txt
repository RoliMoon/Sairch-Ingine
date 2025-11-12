set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(Search_Engine_Tests
    test1.cpp
    testinvindex.cpp
    testsairch.cpp
    ${SRC_DIR}/sairchserver.cpp
    ${SRC_DIR}/invertitindex.cpp
    ${SRC_DIR}/converterjson.cpp
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

target_include_directories(Search_Engine_Tests PUBLIC
    ${TEST_DIR}
    ${SRC_DIR}
    ${GTEST_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
)

#include_directories(
#    ${gtest_SOURCE_DIR}/include 
#    ${gtest_SOURCE_DIR}
#    ${CMAKE_SOURCE_DIR}/include
#)

target_link_libraries(Search_Engine_Tests PRIVATE 
    nlohmann_json::nlohmann_json
    gtest_main
    gtest
)
enable_testing()

include(GoogleTest)
gtest_discover_tests(Search_Engine_Tests)

add_subdirectory(tests)
