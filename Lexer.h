#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#include <string>
using namespace std;

enum class TypeLexeme{
    PLUS, MINUS, EQUALLY, // + - =
    INT, STRING, FLOAT,
    PRINT, INPUT,
    VAR, VAL, // Variable, Constant
    SEMICOLON, // ;
    LPARENTHESIS, RPARENTHESIS, // ( )
    NAMEVARIABLE,
    NONETYPE
};

class Lexeme{
public:
    string lexeme;
    TypeLexeme type;
public:
    bool isInt(const string lexeme){
        for (auto i : lexeme)
            if (((i < '0')||(i > '9')))return 0;
        return 1;
    }

    bool isFloat(const string lexeme){
        bool flagDot = false;
        for (auto i : lexeme){
            if (i == '.'){
                if (!flagDot)flagDot = true;
                else return 0;
            }else if ((i < '0')||(i > '9'))return 0;
        }
        return flagDot ? 1 : 0;
    }

    bool isVariable(const string lexeme){
        for (auto i : lexeme)
            if (!(((i >= '0')&&(i >= '9'))||((i >= 'A')&&(i <= 'Z'))||((i >= 'a')&&(i <= 'z'))||(i == '_')))return 0;
        return 1;
    }
    TypeLexeme TypeDefinition(const string lexeme) {
        if (lexeme == "+")return TypeLexeme::PLUS;
        else if (lexeme == "-")return TypeLexeme::MINUS;
        else if (lexeme == "=")return TypeLexeme::EQUALLY;
        else if (lexeme == "print")return TypeLexeme::PRINT;
        else if (lexeme == "input") return TypeLexeme::INPUT;
        else if (lexeme == "var") return TypeLexeme::VAR;
        else if (lexeme == "val")return TypeLexeme::VAL;
        else if (lexeme == ";")return TypeLexeme::SEMICOLON;
        else if (lexeme == "(")return TypeLexeme::LPARENTHESIS;
        else if (lexeme == ")")return TypeLexeme::RPARENTHESIS;
        else if ((lexeme.front() == '"') && (lexeme.back() == '"'))return TypeLexeme::STRING;
        else if (isInt(lexeme))return TypeLexeme::INT;
        else if (isFloat(lexeme))return TypeLexeme::FLOAT;
        else if (isVariable(lexeme))return TypeLexeme::NAMEVARIABLE;
        else return TypeLexeme::NONETYPE;
    }
};
#endif
