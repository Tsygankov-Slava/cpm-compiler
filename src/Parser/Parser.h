#pragma once

#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <vector>

#include "../AST/AST.h"
#include "../Mixed/Mixed.h"

using std::cin;
using std::cout;
using std::map;
using std::pair;
using std::set;
using std::stringstream;
using std::vector;

class Parser : Node {
private:
  map<string, bool> stackVariables;
  map<string, bool> stackWrongConstants;
  vector<Lexeme> tokens;

public:
  // О, а вот тут ты уже использовал инициализацию в таком виде.
  // Советую придерживаться единому стилю везде.
  explicit Parser(vector<Lexeme> &tokens) : tokens(tokens){};
  set<string> // Странный тут перенос.
  findWrongVariables(); // Ищет переменные(в том числе константы), которые объявлены дважды или неинициализированы вообще
  set<string> findWrongConstants(); // Ищет константы, которые перезаписываются
  void printSet(set<string> a);
  set<string> findNoneType(); // Ищет нераспознанные лексемы
  bool checkAndPrintWrong();
  Node *getAST(); //Создаёт дерево
  string goToLeftAndGetType(Node *root); // Обходит левую ветвь и определяет по ней тип переменной (вызывается в ChangeCommand)
  Node *processingOpInput(Node *root); // Обрабатывает ввод данных
  Node *changeCommand(Node *head); // Заменяет ключевой синтаксис C+- на синтаксис C++
};
