#include "Lexer.h"

bool Lexeme::isInt(const string &lexeme) {
  for (auto i : lexeme)
    if (i < '0' || i > '9') {
      return false;
    }
  return true;
}

bool Lexeme::isFloat(const string &lexeme) {
  bool flagDot = false;
  for (auto i : lexeme) {
    if (i == '.') {
      if (!flagDot) {
        flagDot = true;
      } else {
        return false;
      }
    } else if (i < '0' || i > '9') {
      return false;
    }
  }
  return flagDot ? true : false;
}

bool Lexeme::isVariable(const string &lexeme) {
  for (auto i : lexeme) {
    if (!((i >= '0' && i <= '9') || (i >= 'A' && i <= 'Z') || (i >= 'a' && i <= 'z') || i == '_')) {
      return false;
    }
  }
  return true;
}

TypeLexeme Lexeme::typeDefinition(const string &lexeme) {
  if (lexeme == "+") {
    return TypeLexeme::PLUS;
  } else if (lexeme == "-") {
    return TypeLexeme::MINUS;
  } else if (lexeme == "=") {
    return TypeLexeme::EQUALLY;
  } else if (lexeme == "print") {
    return TypeLexeme::PRINT;
  } else if (lexeme == "input") {
    return TypeLexeme::INPUT;
  } else if (lexeme == "var") {
    return TypeLexeme::VAR;
  } else if (lexeme == "val") {
    return TypeLexeme::VAL;
  } else if (lexeme == ";") {
    return TypeLexeme::SEMICOLON;
  } else if (lexeme == "(") {
    return TypeLexeme::L_PARENTHESIS;
  } else if (lexeme == ")") {
    return TypeLexeme::R_PARENTHESIS;
  } else if (isInt(lexeme)) {
    return TypeLexeme::INT;
  } else if (isFloat(lexeme)) {
    return TypeLexeme::FLOAT;
  } else if (isVariable(lexeme)) {
    return TypeLexeme::VARIABLE_NAME;
  } else if (lexeme.front() == '"' && lexeme.back() == '"') {
    return TypeLexeme::STRING;
  } else {
    return TypeLexeme::NONE_TYPE;
  }
}