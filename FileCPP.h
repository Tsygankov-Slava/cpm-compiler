#ifndef COMPILER_FILECPP_H
#define COMPILER_FILECPP_H
#include <iostream>
#include <string>
#include <fstream>

#include "AST.h"
class FileCpp{
public:
    string path = "";

public:
    FileCpp(string path){
        this->path = path;
    }

    void CreateFileCPP(node* head){ // Создаёт файл .cpp и записывает в него код на С++
        ofstream out;
        if (this->path.find(".txt"))this->path = this->path.substr(0, path.size()-3)+"cpp";
        else this->path += "cpp";
        out.open(this->path);
        if (out.is_open()){
            out << "#include <iostream>\n#include <string>\nusing namespace std;\n";
            out << "int main(){\n";
            node* rootRight = head;
            node* rootLeft = rootRight->left;
            while (rootRight != nullptr){
                out << "\t" << rootRight->token.lexeme << " ";
                while (rootLeft != nullptr){
                    out << rootLeft->token.lexeme << " ";
                    rootLeft = rootLeft->left;
                }
                out << "\n";
                if (rootRight->right != nullptr){
                    rootRight = rootRight->right;
                    rootLeft = rootRight->left;
                }else break;
            }
            out << "}";
        }else cout << "File .cpp didn't created";
    }
};
#endif
