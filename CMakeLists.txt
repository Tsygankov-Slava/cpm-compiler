cmake_minimum_required(VERSION 3.20)
project(Compiler)

set(CMAKE_CXX_STANDARD 23)

add_executable(Compiler main.cpp Lexer.h File.h Parser.h ArgumentsLexemes.h AST.h Mixed.h Code.h FileCPP.h)
