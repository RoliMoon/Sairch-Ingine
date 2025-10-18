add_executable(Sairch_Ingine main.cpp converterjson.cpp invertitindex.cpp sairchserver.cpp)

target_include_directories(Sairch_Ingine PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    nlohmann_json::nlohmann_json
)