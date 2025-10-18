add_executable(Translator main.cpp dictionarmanagement.cpp translator.cpp)

target_include_directories(Translator PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)