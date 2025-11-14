add_executable(Search_Engine main.cpp converterjson.cpp invertitindex.cpp sairchserver.cpp)

target_include_directories(Search_Engine PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(Search_Engine PRIVATE 
    nlohmann_json::nlohmann_json
)
