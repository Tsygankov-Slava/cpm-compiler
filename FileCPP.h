#ifndef COMPILER_FILECPP_H
#define COMPILER_FILECPP_H
// Здесь должна идти пустая строка.
#include <iostream>
#include <string>
#include <fstream>

#include "AST.h"
// Здесь должна идти пустая строка.
class FileCpp{
public:
    // Это поле используется только в этом классе и должно быть приватным.
    string path = "";

public:
    FileCpp(string path){ // Все те же проблемы, что и в других конструкторах.
        this->path = path;
    }

    void CreateFileCPP(node* head){ // Создаёт файл .cpp и записывает в него код на С++
        ofstream out;
        // А если будет не .txt, а .cpm, например? Лучше сделать алгоритм, который уберет любое расширения.
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
// Здесь должна идти пустая строка.
#endif
