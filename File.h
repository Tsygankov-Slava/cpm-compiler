#ifndef COMPILER_FILE_H
#define COMPILER_FILE_H

#include <fstream>
#include <iostream>
#include <string>
#include "Lexer.h"
#include "ArgumentsLexemes.h"
#include "AST.h"
using namespace std;

class File{
public:
    ifstream file;
    string path = "";
    bool FlagOpenFile = 0;
    string Code = "";
    int CountLexemes = 10;
    Lexeme* ArrLexemes = new Lexeme [CountLexemes];
    int lenArrLexemes = 0;
public:
    string EnterPath2File(){
        cout << "Enter the path to the code -> ";
        string path = "";
        cin >> path;
        return path;
    }
    void OpenFile(){
        if (this->path == "")cout << "You wrong initialized class File. Path is empty.";
        else {
            file.open(path);
            if (file.is_open()){
                this->FlagOpenFile = 1;
            }else cout << "The file is not open. Probably, your path is wrong.";
        }
    }
    void ReadFile(){
        if (FlagOpenFile) {
            while (!file.eof()) {
                string s;
                getline(file, s);
                Code += s;
            }
        }else {cout << "File is not open. Call function \"OpenFile\"";}
    }
    Lexeme* CheckMemory(){
        if (this->CountLexemes - this->lenArrLexemes < 3){
            Lexeme* ArrLexemes2 = new Lexeme[this->CountLexemes*2];
            for (int i = 0; i < this->CountLexemes; i++)
                ArrLexemes2[i] = ArrLexemes[i];
            delete [] ArrLexemes;
            this->CountLexemes *= 2;
            return ArrLexemes2;
        }else return ArrLexemes;
    }
    ArgumentsLexemes GetLexemes(string code){
        int iterator = 0;
        char ch = code[iterator];
        string lex = "";
        bool flagNotString = 1; // Переменная предназначена для того, чтобы отслеживать пробелы в типе String
        while (ch != '\0'){
            ArrLexemes = CheckMemory();
            if ((ch == ';')||(ch == '-')||(ch == '+')||(ch == '=')||(ch == '(')||(ch == ')')||((ch == ' ')&&(flagNotString))||(ch == '\n')){
                if (lex != "") {
                    this->ArrLexemes[this->lenArrLexemes].lexeme = lex;
                    this->ArrLexemes[this->lenArrLexemes].type = this->ArrLexemes[this->lenArrLexemes].TypeDefinition(lex);
                    this->lenArrLexemes++;
                    lex = "";
                }
                if ((ch != ' ')&&(ch != '\n')){
                    string s = "";
                    s = ch;
                    this->ArrLexemes[this->lenArrLexemes].lexeme = ch;
                    this->ArrLexemes[this->lenArrLexemes].type = this->ArrLexemes[this->lenArrLexemes].TypeDefinition(s);
                    this->lenArrLexemes++;
                }
            }else {
                if (ch == '\"'){
                    if (flagNotString)flagNotString = 0;
                    else flagNotString = 1;
                }
                lex += ch;
            }
            iterator++;
            ch = code[iterator];
        }
        ArgumentsLexemes arr = {ArrLexemes, lenArrLexemes};
        return arr;
    }
    void PrintLexemes(){
        for (int i = 0; i < this->lenArrLexemes; i++)
            cout << this->ArrLexemes[i].lexeme << " -> " << arr_type_lexeme[int(this->ArrLexemes[i].type)] << "\n";
    }
    void CreateFileCPP(string path, node* head){
        ofstream out;
        path = path.substr(0, path.size()-3)+"cpp";
        out.open(path);
        if (out.is_open()){
            out << "#include <iostream>\n#include <string>\nusing namespace std;\n";
            out << "int main(){\n";
            node* root_right = head;
            node* root_left = root_right->left;
            while (root_right != nullptr){
                out << "    " << root_right->lex.lexeme << " ";
                while (root_left != nullptr){
                    out << root_left->lex.lexeme;
                    root_left = root_left->left;
                }
                out << "\n";
                if (root_right->right != nullptr){
                    root_right = root_right->right;
                    root_left = root_right->left;
                }else break;
            }
            out << "}";
        }else cout << "File .cpp didn't created";
    }
    void ClearMemoryAndCloseFile(){
        delete [] ArrLexemes;
        this->file.close();
    }
};
#endif
