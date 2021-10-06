cmake_minimum_required(VERSION 3.7)

project(Expr)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# compiler must be 11 or 14
set(CMAKE_CXX_STANDARD 14)

# required if linking to static library
add_definitions(-DANTLR4CPP_STATIC)

# using /MD flag for antlr4_runtime (for Visual C++ compilers only)
set(ANTLR4_WITH_STATIC_CRT OFF)
# add external build for antlrcpp
include(ExternalAntlr4Cpp)
# add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

# set variable pointing to the antlr tool that supports C++
# this is not required if the jar file can be found under PATH environment
set(ANTLR_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/tools/antlr-4.9.2-complete.jar)
# add macros to generate ANTLR Cpp code from grammar
find_package(ANTLR REQUIRED)

# add our project source directories
include_directories(${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/antlr4-runtime/
        )

# Call macro to add lexer and grammar to your build dependencies.
antlr_target(ExprGrammarParser Expr.g4 PARSER OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs/)


# add generated grammar to demo binary target
add_executable(${PROJECT_NAME} ExprMain.cpp
        ${ANTLR_ExprGrammarLexer_CXX_OUTPUTS}
        ${PROJECT_SOURCE_DIR}/antlr4-runtime/ExprBaseListener.cpp
        ${PROJECT_SOURCE_DIR}/antlr4-runtime/ExprBaseListener.h
        ${PROJECT_SOURCE_DIR}/antlr4-runtime/ExprLexer.cpp
        ${PROJECT_SOURCE_DIR}/antlr4-runtime/ExprLexer.h
        ${PROJECT_SOURCE_DIR}/antlr4-runtime/ExprListener.cpp
        ${PROJECT_SOURCE_DIR}/antlr4-runtime/ExprListener.h
        ${PROJECT_SOURCE_DIR}/antlr4-runtime/ExprParser.cpp
        ${PROJECT_SOURCE_DIR}/antlr4-runtime/ExprParser.h
        )
target_link_libraries(${PROJECT_NAME} antlr4_static ${SYSTEM_LIBS})

# copy the input file next to the generated executable
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/input.txt"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/../)