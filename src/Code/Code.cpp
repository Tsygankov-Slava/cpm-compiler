#include "Code.h"

vector<Lexeme> Code::getTokens() {
  int index = 0;
  char ch = code[index];
  string lex = "";
  bool flagNotString = true; // Переменная предназначена для того, чтобы отслеживать пробелы в типе String
  while (ch != '\0') {
    if (ch == ';' || ch == '-' || ch == '+' || ch == '=' || ch == '(' || ch == ')' || (ch == ' ' && flagNotString) || ch == '\n') { // Символы разделяющие код на лексемы, они же также являются лексемами
      if (lex != "") {
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
  for (auto i : tokens)
    cout << i.lexeme << "\n";
}