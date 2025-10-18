set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

add_executable(Sairch_Ingine_Tests
    test1.cpp
    testinvindex.cpp
    testsairch.cpp
    ${SRC_DIR}/sairchserver.cpp
    ${SRC_DIR}/invertitindex.cpp
    ${SRC_DIR}/converterjson.cpp
)

target_include_directories(Sairch_Ingine_Tests PUBLIC
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

target_link_libraries(Sairch_Ingine_Tests PRIVATE 
    nlohmann_json::nlohmann_json
    gtest_main
    gtest
)

include(GoogleTest)
gtest_discover_tests(Sairch_Ingine_Tests)