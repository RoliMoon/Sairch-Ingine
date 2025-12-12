cmake_minimum_required (VERSION 3.26)

add_executable(${PROJECT_NAME} main.cpp converterjson.cpp invertitindex.cpp sairchserver.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    nlohmann_json::nlohmann_json
)
