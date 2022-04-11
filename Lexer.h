#ifndef COMPILER_LEXER_H
#define COMPILER_LEXER_H

#include <string>
// Здесь должна идти пустая строка.
using namespace std;

enum class TypeLexeme{
    PLUS, MINUS, EQUALLY, // + - =
    INT, STRING, FLOAT,
    PRINT, INPUT,
    VAR, VAL, // Variable, Constant
    SEMICOLON, // ;
    LPARENTHESIS, RPARENTHESIS, // ( )
    NAMEVARIABLE, // Все сливается, лучше VARIABLE_NAME&
    NONETYPE
};

class Lexeme{
public:
    string lexeme;
    TypeLexeme type;
public:
    bool isInt(const string lexeme){ // Clang-Tidy: The const qualified parameter 'lexeme' is copied for each invocation; consider making it a reference
       for (auto i : lexeme)
            // В выражениях с || или && необязательно оборачивать левую и правую части в скобки.
            // То есть ((i < '0')||(i > '9')) эквивалентно (i < '0' || i > '9') и в 100 раз читаемей!
            // Это касается не только здесь, но и все таких мест в коде.
            if (((i < '0')||(i > '9')))return 0;
        // Все еще возвращаешь числа вместо true/false!
        return 1;
    }

    bool isFloat(const string lexeme){ // Clang-Tidy: The const qualified parameter 'lexeme' is copied for each invocation; consider making it a reference
        bool flagDot = false;
        for (auto i : lexeme){
            if (i == '.'){
                if (!flagDot)flagDot = true;
                else return 0;
            }else if ((i < '0')||(i > '9'))return 0;
        }
        // Все еще возвращаешь числа вместо true/false!
        return flagDot ? 1 : 0;
    }

    bool isVariable(const string lexeme){ // Clang-Tidy: The const qualified parameter 'lexeme' is copied for each invocation; consider making it a reference
        for (auto i : lexeme)
            // Из-за обилия скобок и отсутствия пробелов это нечитаемо абсолютно!
            if (!(((i >= '0')&&(i >= '9'))||((i >= 'A')&&(i <= 'Z'))||((i >= 'a')&&(i <= 'z'))||(i == '_')))return 0;
        // Все еще возвращаешь числа вместо true/false!
        return 1;
    }
    // Здесь должна идти пустая строка.
    TypeLexeme TypeDefinition(const string lexeme) { // Clang-Tidy: The const qualified parameter 'lexeme' is copied for each invocation; consider making it a reference
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
// Здесь должна идти пустая строка.
#endif
