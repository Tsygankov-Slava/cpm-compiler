#include "Mixed.h"

// Не понимаю, почему у тебя сложение двух Mixed дает пару?
pair<Mixed, Mixed> operator+(Mixed &a, Mixed &b) {
  bool flag = false;
  for (int i = 0; i < 2; i++) {
    if (a.lexeme.type == TypeLexeme::STRING && b.lexeme.type == TypeLexeme::INT) {
      b.lexeme.type = TypeLexeme::STRING;
      b.lexeme.lexeme = "\"" + b.lexeme.lexeme + "\"";
      break;
    } else if (a.lexeme.type == TypeLexeme::STRING && b.lexeme.type == TypeLexeme::FLOAT) {
      b.lexeme.type = TypeLexeme::STRING;
      b.lexeme.lexeme = "\"" + b.lexeme.lexeme + "\"";
      break;
    } else if (a.lexeme.type == TypeLexeme::FLOAT && b.lexeme.type == TypeLexeme::INT) {
      b.lexeme.type = TypeLexeme::FLOAT;
      b.lexeme.lexeme += ".0";
      break;
    }
    swap(a, b);
    flag = !flag;
  }
  if (flag) {
    swap(a, b);
  }
  return make_pair(a, b);
}

pair<Mixed, Mixed> operator-(Mixed &a, Mixed &b) {
  Lexeme lex;
  bool flag = false;
  for (int i = 0; i < 2; i++) {
    if (a.lexeme.type == TypeLexeme::FLOAT && b.lexeme.type == TypeLexeme::INT) {
      b.lexeme.type = TypeLexeme::FLOAT;
      b.lexeme.lexeme += ".0";
      break;
    } else if (a.lexeme.type == TypeLexeme::INT && b.lexeme.type == TypeLexeme::STRING) {
      b.lexeme.type = TypeLexeme::INT;
      b.lexeme.lexeme = b.lexeme.lexeme.substr(1, b.lexeme.lexeme.size() - 2);
      if (!lex.isInt(b.lexeme.lexeme)) {
        b.lexeme.lexeme = "0";
      }
      break;
    } else if (a.lexeme.type == TypeLexeme::FLOAT && b.lexeme.type == TypeLexeme::STRING) {
      b.lexeme.type = TypeLexeme::FLOAT;
      b.lexeme.lexeme = b.lexeme.lexeme.substr(1, b.lexeme.lexeme.size() - 2);
      if (lex.isInt(b.lexeme.lexeme)) {
        b.lexeme.lexeme += ".0";
      } else if (!lex.isFloat(b.lexeme.lexeme)) {
        b.lexeme.lexeme = "0.0";
      }
      break;
    }
    swap(a, b);
    flag = !flag;
  }
  if (flag) {
    swap(a, b);
  }
  return make_pair(a, b);
}
