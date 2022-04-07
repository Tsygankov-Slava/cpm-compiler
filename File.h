#ifndef COMPILER_FILE_H
#define COMPILER_FILE_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Lexer.h"
#include "AST.h"
using namespace std;

class File{
public:
    ifstream file; // Объект файла
    string path = ""; // Путь к файлу
    string code = ""; // Код файла

    File(string path){
        if(path.find(".txt") != string::npos)this->path = path;
        else this->path = path + ".txt";
    }
    void OpenAndReadFile(){
        this->file.open(this->path);
        if (this->file){
            while (!this->file.eof()){
                string str;
                getline(file, str); //Читаем из потока file строку и записываем его в str (читается одна строка, потому что separate[3-ий параметр по умолчанию '\n'])
                code += str;
            }
        }else{
            cout << "The file is not open. Probably, your path is wrong.";
        }
    }
};
#endif
