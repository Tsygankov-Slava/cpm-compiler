cmake_minimum_required(VERSION 3.20)
project(Compiler)

set(CMAKE_CXX_STANDARD 23)

# А откуда здесь взялся ArgumentsLexemes.h, его нет в файлах, из-за
# этого cmake не собирает проект!
add_executable(Compiler main.cpp Lexer.h File.h Parser.h AST.h Mixed.h Code.h FileCPP.h)
