#include "Code.h"

vector<Lexeme> Code::getTokens() {
  int index = 0;
  char ch = code[index];
  string lex = "";
  bool flagNotString = true; // Переменная предназначена для того, чтобы отслеживать пробелы в типе String
  while (ch != '\0') {
    // Чтобы не писать такие длинные и некрасивые условия, лучше было бы написать что-то типа такого:
    // const auto separators = std::set<char>(';', '-', ...);
    // if (separators.contains(ch)) {
    //    ...
    // }
    //
    // separators, конечно вынести за пределы цикла в начало функции.
    // Ситуацию со строкой тоже можно обыграть лучше. Просто вынеси эо в другое условие и если
    // оно верное то делаешь continue и следующий код уже точно не исполнится.
    if (ch == ';' || ch == '-' || ch == '+' || ch == '=' || ch == '(' || ch == ')' || (ch == ' ' && flagNotString) || ch == '\n') { // Символы разделяющие код на лексемы, они же также являются лексемами
      if (lex != "") {
        // Лучше если бы у Lexeme был конструктор и в нем самом бы уже
        // вызывался этот метод, так код стал бы короче и читаемей.
        // Плюсом ты вызываешь метод класса, как константный, не надо так
        // делать, если метод статический, то укажи это явно!
        tokens.push_back({lex, Lexeme::typeDefinition(lex)});
        lex = "";
      }
      if ((ch != ' ') && (ch != '\n')) { // Добавляем лексемы (разделители), которые упоминаются в условии выше
        string s(1, ch); // char to string
        tokens.push_back({s, Lexeme::typeDefinition(s)});
      }
    } else {
      if (ch == '\"') { // Определяем строку по символу "
        if (flagNotString) {
          flagNotString = false;
        } else {
          flagNotString = true;
        }
      }
      lex += ch;
    }
    ch = code[++index];
  }
  return tokens;
}

void Code::printTokens() {
  // У тебя цикл по токенам, но почему-то отдельный токен называется i
  // Нужно давать понятные имена переменным, так как это не цикл по индексам.
  for (auto i : tokens)
    cout << i.lexeme << "\n";
}