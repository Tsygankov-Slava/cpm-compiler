#ifndef COMPILER_MIXED_H
#define COMPILER_MIXED_H

#include <iostream>
#include <string>
#include<sstream>
#include "Lexer.h"
using namespace std;

enum Type{
    INT, FLOAT, STRING
};
struct Pair{
    Lexeme first;
    Lexeme second;
};
struct Mixed{
    Pair GetType(Lexeme a, Lexeme b, string operation){
        Pair p;
        if ( ((arr_type_lexeme[int(a.type)] == "STRING")&&( (arr_type_lexeme[int(b.type)] == "INT") || (arr_type_lexeme[int(b.type)] == "FLOAT") ))
        ||   ((arr_type_lexeme[int(b.type)] == "STRING")&&( (arr_type_lexeme[int(a.type)] == "INT") || (arr_type_lexeme[int(a.type)] == "FLOAT") ))){
            if (operation == "+"){
                p.first.type = type_lexeme::STRING;
                p.second.type = type_lexeme::STRING;
                p.first.lexeme = a.lexeme;
                p.second.lexeme = b.lexeme;
            }else if (operation == "-"){
                if (arr_type_lexeme[int(a.type)] == "STRING"){
                    if (arr_type_lexeme[int(b.type)] == "INT"){
                        p.first.type = type_lexeme::INT;
                        p.second.type = type_lexeme::INT;
                        p.second.lexeme = b.lexeme;
                        bool flag = 1;
                        for (int i = 1; i < a.lexeme.size()-1; i++)if ((int(a.lexeme[i]) < 48)||(int(a.lexeme[i]) > 57)){ flag = 0; break; }
                        if (flag)p.first.lexeme = a.lexeme.substr(1, a.lexeme.size()-2);
                        else p.first.lexeme = "0";
                    }else if (arr_type_lexeme[int(b.type)] == "FLOAT"){
                        p.first.type = type_lexeme::FLOAT;
                        p.second.type = type_lexeme::FLOAT;
                        p.second.lexeme = b.lexeme;
                        bool flag = 1;
                        bool flagDot = 0;
                        for (int i = 1; i < a.lexeme.size()-1; i++){
                            if (int(a.lexeme[i]) == 46){
                                if (flagDot){flag = 0; break;}
                                else flagDot = 1;
                            }
                            if (((int(a.lexeme[i]) < 48)||(int(a.lexeme[i]) > 57))&&(int(a.lexeme[i]) != 46)){ flag = 0; break; }
                        }
                        if (flag){
                            if (flagDot)p.first.lexeme = a.lexeme.substr(1, a.lexeme.size()-2);
                            else p.first.lexeme = a.lexeme.substr(1, a.lexeme.size()-2) + ".0";
                        }
                        else p.first.lexeme = "0.0";
                    }
                }else if (arr_type_lexeme[int(b.type)] == "STRING"){

                    if (arr_type_lexeme[int(a.type)] == "INT"){
                        p.first.type = type_lexeme::INT;
                        p.second.type = type_lexeme::INT;
                        p.first.lexeme = a.lexeme;
                        bool flag = 1;
                        for (int i = 1; i < b.lexeme.size()-1; i++)if ((int(b.lexeme[i]) < 48)||(int(b.lexeme[i]) > 57)){ flag = 0; break; }
                        if (flag)p.second.lexeme = b.lexeme.substr(1, b.lexeme.size()-2);
                        else p.second.lexeme = "0";
                    }else if (arr_type_lexeme[int(a.type)] == "FLOAT"){
                        p.first.type = type_lexeme::FLOAT;
                        p.second.type = type_lexeme::FLOAT;
                        p.first.lexeme = a.lexeme;
                        bool flag = 1;
                        bool flagDot = 0;
                        for (int i = 1; i < b.lexeme.size()-1; i++){
                            if (int(b.lexeme[i]) == 46){
                                if (flagDot){flag = 0; break;}
                                else flagDot = 1;
                            }
                            if (((int(b.lexeme[i]) < 48)||(int(b.lexeme[i]) > 57))&&(int(b.lexeme[i]) != 46)){ flag = 0; break; }
                        }
                        if (flag){
                            if (flagDot)p.second.lexeme = b.lexeme.substr(1, b.lexeme.size()-2);
                            else p.second.lexeme = b.lexeme.substr(1, b.lexeme.size()-2) + ".0";
                        }
                        else p.second.lexeme = "0.0";
                    }
                }
            }
        }else if ( ((arr_type_lexeme[int(b.type)] == "FLOAT")&&(arr_type_lexeme[int(a.type)] == "INT"))
              ||   ((arr_type_lexeme[int(a.type)] == "FLOAT")&&(arr_type_lexeme[int(b.type)] == "INT")) ){
                p.first.type = type_lexeme::FLOAT;
                p.second.type = type_lexeme::FLOAT;
                if (arr_type_lexeme[int(a.type)] == "INT"){
                    p.first.lexeme = a.lexeme + ".0";
                    p.second.lexeme = b.lexeme;
                }else {
                    p.first.lexeme = a.lexeme;
                    p.second.lexeme = b.lexeme + ".0";
                }
        }else {
            if (arr_type_lexeme[int(a.type)] == "INT"){
                p.first.type = type_lexeme::INT;
                p.second.type = type_lexeme::INT;
                p.first.lexeme = a.lexeme;
                p.second.lexeme = b.lexeme;
            }else if (arr_type_lexeme[int(a.type)] == "FLOAT"){
                p.first.type = type_lexeme::FLOAT;
                p.second.type = type_lexeme::FLOAT;
                p.first.lexeme = a.lexeme;
                p.second.lexeme = b.lexeme;
            }else if (arr_type_lexeme[int(a.type)] == "STRING"){
                p.first.type = type_lexeme::STRING;
                p.second.type = type_lexeme::STRING;
                p.first.lexeme = a.lexeme;
                p.second.lexeme = b.lexeme;
            }
        }
        return p;
    }
};
#endif
