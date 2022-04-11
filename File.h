// А почему не использовать просто #pragma once?
// Так будет покороче.
#ifndef COMPILER_FILE_H
#define COMPILER_FILE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Lexer.h"
#include "AST.h"
// Здесь должна идти пустая строка.
using namespace std;

// Если класс содержит в себе только публичные поля,
// то имеет смысл сделать его структурой, считай,
// то же самое, только без необходимости писать явно "public:".
class File{
public:
    ifstream file; // Объект файла
    string path = ""; // Путь к файлу
    string code = ""; // Код файла

    // Еще одним преимуществом CLion являются проверки статического анализа. Например, тут:
    //   Clang-Tidy: The parameter 'path' is copied for each invocation but only used as a const reference; consider making it a const reference
    // Нужно передавать путь по константной ссылке, чтобы не копировать лишний раз строку.
    // То есть что-то типа такого:
    //   File(const string& path)
    // Также в этой строке:
    //   Clang-Tidy: Single-argument constructors must be marked explicit to avoid unintentional implicit conversions
    File(string path){
        // Снова мешанина, очень не хватает пробелов!
        // Также тут у тебя if без фигурных скобок, а в других
        // местах со скобками. Нужно быть более последовательным!
        if(path.find(".txt") != string::npos)this->path = path;
        else this->path = path + ".txt";
    }
    // Здесь нужна пустая строка.
    void OpenAndReadFile(){
        // Вообще использование this необязательно и мне кажется
        // только добавляет шума коду. Его логично использовать, когда
        // есть какая-то неопределенность, например, когда параметр функции
        // имеет такое же имя, как и поле класса, но это не этот случай.
        this->file.open(this->path);
        if (this->file){
            while (!this->file.eof()){
                string str;
                getline(file, str); //Читаем из потока file строку и записываем его в str (читается одна строка, потому что separate[3-ий параметр по умолчанию '\n'])
                code += str;
            }
        // Снова проблемы с пробелами перед/после слова else!
        }else{
            cout << "The file is not open. Probably, your path is wrong.";
        }
    }
};
// Здесь должна идти пустая строка.
#endif
