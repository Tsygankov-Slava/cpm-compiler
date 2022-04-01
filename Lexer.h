#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#include <string>
using namespace std;

enum class type_lexeme{
    PLUS, MINUS, EQUALLY, // + - =
    INT, STRING, FLOAT,
    PRINT, INPUT,
    VAR, VAL, // Variable, Constant
    SEMICOLON, // ;
    LPARENTHESIS, RPARENTHESIS, // ( )
    NAMEVARIABLE,
    NONETYPE
};

const int LEN_TYPE_LEXEME = 15;
string arr_type_lexeme[LEN_TYPE_LEXEME] = {"PLUS", "MINUS", "EQUALLY", "INT", "STRING", "FLOAT", "PRINT", "INPUT", "VAR", "VAL", "SEMICOLON","LPARENTHESIS", "RPARENTHESIS","NAMEVARIABLE", "NONETYPE"};

class Lexeme{
public:
    string lexeme;
    type_lexeme type;
public:
    bool isInt(const string lexeme){
        for (auto i : lexeme){
            if (((int(i) < 48)||(int(i) > 57)))return 0;
        }
        return 1;
    }

    bool isFloat(const string lexeme){
        bool flagDot = 0;
        for (auto i : lexeme){
            if (i == '.'){
                if (flagDot == 0)flagDot = 1;
                else return 0;
            }else if ((int(i) < 48)||(int(i) > 57))return 0;
        }
        if (flagDot)return 1;
        else return 0;
    }

    bool isVariable(const string lexeme){
        for (auto i : lexeme){
            if (!(((i >= 48)&&(i <= 57))||((i >= 65)&&(i <= 90))||((i >= 97)&&(i <= 122))||(i == 95)))return 0;
        }
        return 1;
    }
    type_lexeme TypeDefinition(const string lexeme) {
        if (lexeme == "+")return type_lexeme::PLUS;
        else if (lexeme == "-")return type_lexeme::MINUS;
        else if (lexeme == "=")return type_lexeme::EQUALLY;
        else if (lexeme == "print")return type_lexeme::PRINT;
        else if (lexeme == "input") return type_lexeme::INPUT;
        else if (lexeme == "var") return type_lexeme::VAR;
        else if (lexeme == "val")return type_lexeme::VAL;
        else if (lexeme == ";")return type_lexeme::SEMICOLON;
        else if (lexeme == "(")return type_lexeme::LPARENTHESIS;
        else if (lexeme == ")")return type_lexeme::RPARENTHESIS;
        else if ((lexeme.front() == '"') && (lexeme.back() == '"'))return type_lexeme::STRING;
        else if (isInt(lexeme))return type_lexeme::INT;
        else if (isFloat(lexeme))return type_lexeme::FLOAT;
        else if (isVariable(lexeme))return type_lexeme::NAMEVARIABLE;
        else return type_lexeme::NONETYPE;
    }
};
#endif
