#ifndef COMPILER_MIXED_H
#define COMPILER_MIXED_H

#include <iostream>
#include <string>

#include "Lexer.h"
using namespace std;

class Mixed{
public:
    pair<Lexeme, Lexeme> ChangeTypeStr2IntOrFloat(pair<Lexeme, Lexeme> arr, pair<Lexeme*, Lexeme*> pairPointerVariables){
        if (arr.second.type == TypeLexeme::INT){
            arr.first.type = TypeLexeme::INT;
            bool flag = true;
            for (int i = 1; i < arr.first.lexeme.size()-1; i++)
                if(arr.first.lexeme[i] < '0' || arr.first.lexeme[i] > '9'){ flag = false; break; }
            if (flag){
                arr.first.lexeme = arr.first.lexeme.substr(1, arr.first.lexeme.size()-2);
                pairPointerVariables.first->lexeme = arr.first.lexeme;
            }
            else {
                arr.first.lexeme = "0";
                pairPointerVariables.first->lexeme = arr.first.lexeme;
            }
        }else if (arr.second.type == TypeLexeme::FLOAT){
            arr.first.type = TypeLexeme::FLOAT;
            bool flag = true;
            bool flagDot = false;
            for (int i = 1; i < arr.first.lexeme.size()-1; i++){
                if (arr.first.lexeme[i] == '.'){
                    if (flagDot){flag = false; break;}
                    else flagDot = true;
                }
                if (((arr.first.lexeme[i] < '0')||(arr.first.lexeme[i] > '9'))&&(arr.first.lexeme[i] != '.')){ flag = 0; break; }
            }
            if (flag){
                if (flagDot){
                    arr.first.lexeme = arr.first.lexeme.substr(1, arr.first.lexeme.size()-2);
                    pairPointerVariables.first->lexeme = arr.first.lexeme;
                }
                else {
                    arr.first.lexeme = arr.first.lexeme.substr(1, arr.first.lexeme.size()-2) + ".0";
                    pairPointerVariables.first->lexeme = arr.first.lexeme;
                }
            }
            else {
                arr.first.lexeme = "0.0";
                pairPointerVariables.first->lexeme = arr.first.lexeme;
            }
        }
        return arr;
    }

    pair<Lexeme, Lexeme> GetType(pair<pair<Lexeme, Lexeme>, string> pairTypes, pair<Lexeme*, Lexeme*> pairPointerVariables){
        if (((pairTypes.first.first.type == TypeLexeme::STRING)&&((pairTypes.first.second.type == TypeLexeme::INT)||(pairTypes.first.second.type == TypeLexeme::FLOAT)))
        ||  ((pairTypes.first.second.type == TypeLexeme::STRING)&&((pairTypes.first.first.type == TypeLexeme::INT)||(pairTypes.first.first.type  == TypeLexeme::FLOAT)))){
            if (pairTypes.second == "+"){ // Если STRING + INT/FLOAT -> (STRING, STRING)
                if ((pairTypes.first.first.type == TypeLexeme::INT)||(pairTypes.first.first.type == TypeLexeme::FLOAT)){
                    pairPointerVariables.first->lexeme = "\"" + pairTypes.first.first.lexeme + "\"";
                }
                if ((pairTypes.first.second.type == TypeLexeme::INT)||(pairTypes.first.second.type == TypeLexeme::FLOAT)){
                    pairPointerVariables.second->lexeme = "\"" + pairTypes.first.second.lexeme + "\"";
                }
                pairTypes.first.first.type = TypeLexeme::STRING;
                pairTypes.first.second.type = TypeLexeme::STRING;
            }else if (pairTypes.second == "-"){ // Если STRING - INT/FLOAT -> (INT/FLOAT, INT/FLOAT)
                if (pairTypes.first.first.type == TypeLexeme::STRING){
                    pairTypes.first = this->ChangeTypeStr2IntOrFloat(pairTypes.first, pairPointerVariables);
                }else if (pairTypes.first.second.type == TypeLexeme::STRING){
                    swap(pairTypes.first.first, pairTypes.first.second);
                    swap(pairPointerVariables.first, pairPointerVariables.second);
                    pairTypes.first = this->ChangeTypeStr2IntOrFloat(pairTypes.first, pairPointerVariables);
                    swap(pairTypes.first.first, pairTypes.first.second);
                    swap(pairPointerVariables.first, pairPointerVariables.second);
                }
            }
        }else if (((pairTypes.first.first.type == TypeLexeme::INT)&&(pairTypes.first.second.type == TypeLexeme::FLOAT)) // Если INT/FLOAT +/- INT/FLOAT -> (FLOAT, FLOAT)
              ||  ((pairTypes.first.second.type == TypeLexeme::INT)&&(pairTypes.first.first.type == TypeLexeme::FLOAT))){
                if (pairTypes.first.first.type == TypeLexeme::INT) {
                    pairTypes.first.first.lexeme += ".0";
                    pairPointerVariables.first->lexeme  = pairTypes.first.first.lexeme;
                }
                else {
                    pairTypes.first.second.lexeme += ".0";
                    pairPointerVariables.second->lexeme  = pairTypes.first.second.lexeme;
                }
            pairTypes.first.first.type = TypeLexeme::FLOAT;
            pairTypes.first.second.type = TypeLexeme::FLOAT;
        }
        return make_pair(pairTypes.first.first, pairTypes.first.second);
    }
};
#endif
