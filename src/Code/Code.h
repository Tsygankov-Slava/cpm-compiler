#pragma once

#include <vector>

#include "../File/File.h"
#include "../Lexer/Lexer.h"

using std::cout;
using std::vector;

// Не очень понимаю почему у тебя класс наследуется от Lexeme (для
// использования Lexeme::typeDefinition внутри класса это не нужно) и от File.
// Выглядит крайне странно. Также этот класс лексического анализа, называть
// его Code, неправильно, лучше просто Lexer, на подобии с Parser.
class Code : public File, Lexeme {
private:
  string code;
  vector<Lexeme> tokens;

public:
  // Кстати члены класса также можно инициализировать, как при наследовании:
  // Code(const string &path, const string &code) : code(code)
  // Это короче и в таком виде не страшны одинаковые названия параметра
  // и поля.
  // Также файл тебе здесь не нужен и его можно удалить.
  Code(const string &path, const string &code) : File(path), code(code) {
    this->code = code;
  };
  vector<Lexeme> getTokens();
  void printTokens();
};
