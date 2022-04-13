cmake_minimum_required(VERSION 3.20)
# Название проекта иногда важнее его самого :)
# Это название не отражает его сути, оно неконкретно,
# можно назвать ешо например cpmc (C+- compiler)
# Например компилятор TypeScript имеет имя tsc.
project(Compiler)

set(CMAKE_CXX_STANDARD 23)
# Лучше такие длинные строки не оставлять, лучше перенести все на разные строки с список.
add_executable(Compiler src/main.cpp src/Mixed/Mixed.cpp src/Mixed/Mixed.h src/File/File.cpp src/File/File.h src/Code/Code.cpp src/Code/Code.h src/Parser/Parser.cpp src/Parser/Parser.h src/AST/AST.cpp src/AST/AST.h src/Lexer/Lexer.cpp src/Lexer/Lexer.h src/FileCPP/FileCPP.cpp src/FileCPP/FileCPP.h)
