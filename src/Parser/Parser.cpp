#include "Parser.h"

set<string> Parser::findWrongVariables() { // Ищет переменные(в том числе константы), которые объявлены дважды или неинициализированы вообще
  set<string> arrWrongVariables;
  for (int i = 0; i < tokens.size(); i++) {
    if (tokens[i].type == TypeLexeme::VARIABLE_NAME && !stackVariables[tokens[i].lexeme]) {
      arrWrongVariables.insert(tokens[i].lexeme);
    }
    if (tokens[i].lexeme == "var" || tokens[i].lexeme == "val") {
      if (!stackVariables[tokens[i + 1].lexeme]) {
        stackVariables[tokens[i + 1].lexeme] = true;
      } else {
        arrWrongVariables.insert(tokens[i + 1].lexeme);
      }
    }
  }
  return arrWrongVariables;
}

set<string> Parser::findWrongConstants() { // Ищет константы, которые перезаписываются
  set<string> arrWrongConstants;
  for (int i = 0; i < tokens.size(); i++) {
    if (tokens[i].lexeme == "val") {
      if (stackWrongConstants[tokens[i + 2].lexeme]) {
        arrWrongConstants.insert(tokens[i].lexeme);
      }
      stackWrongConstants[tokens[i].lexeme] = true;
    }
  }
  return arrWrongConstants;
}

void Parser::printSet(set<string> a) {
  set<string>::iterator it;
  for (it = a.begin(); it != a.end(); it++) {
    cout << *it << "\n";
  }
}

set<string> Parser::findNoneType() { // Ищет нераспознанные лексемы
  set<string> arrNoneType;
  for (int i = 0; i < tokens.size(); i++) {
    if (tokens[i].type == TypeLexeme::NONE_TYPE) {
      arrNoneType.insert(tokens[i].lexeme);
    }
  }
  return arrNoneType;
}

bool Parser::checkAndPrintWrong() {
  bool wrong = false;
  set<string> a;
  a = findWrongVariables();
  if (!a.empty()) {
    cout << "ERROR\nProbably this variables/constants is not initialized or announced twice: \n";
    printSet(a);
    wrong = true;
  }
  a = findWrongConstants();
  if (!a.empty()) {
    cout << "ERROR\nThis constants changing: \n";
    printSet(a);
    wrong = true;
  }
  a = findNoneType();
  if (!a.empty()) {
    cout << "ERROR\nNoneType: \n";
    printSet(a);
    wrong = true;
  }
  return wrong;
}

Node *Parser::getAST() { //Создаёт дерево
  if (!tokens.empty()) {
    Node *head = makeHead(tokens[0]);
    bool flagAddLeft = true;
    for (int i = 1; i < tokens.size(); i++) {
      if (flagAddLeft) {
        head = addToLeft(head, tokens[i]);
      } else {
        head = addToRight(head, tokens[i]);
        flagAddLeft = true;
      }
      if (tokens[i].lexeme == ";") {
        flagAddLeft = false;
      }
    }
    return head;
  }
  return 0;
}

string Parser::goToLeftAndGetType(Node *root) { // Обходит левую ветвь и определяет по ней тип переменной (вызывается в ChangeCommand)
  vector<Lexeme *> stackPointerVariables;
  vector<string> stackOperations;
  while (root->token.lexeme != ";") {
    if (root->token.type == TypeLexeme::INPUT) {
      root = processingOpInput(root);
      goToLeftAndGetType(root);
    }
    if (root->token.type == TypeLexeme::INT || root->token.type == TypeLexeme::FLOAT || root->token.type == TypeLexeme::STRING) {
      stackPointerVariables.push_back(&root->token);
    }
    if (root->token.lexeme == "+" || root->token.lexeme == "-") {
      stackOperations.push_back(root->token.lexeme);
    }
    root = root->left;
  }
  for (int i = 0; i < stackPointerVariables.size() - 1; i++) {
    Mixed m1(*stackPointerVariables[i]);
    Mixed m2(*stackPointerVariables[i + 1]);
    pair<Mixed, Mixed> p;
    if (stackOperations[i] == "+") {
      p = m1 + m2;
    } else {
      p = m1 - m2;
    }
    *stackPointerVariables[i] = p.first.lexeme;
    *stackPointerVariables[i + 1] = p.second.lexeme;
  }
  for (int i = stackPointerVariables.size() - 1; i > 0; i--) { // Цикл идёт в обратную сторону, чтобы изменить первые типы относительно последних
    Mixed m1(*stackPointerVariables[i]);
    Mixed m2(*stackPointerVariables[i - 1]);
    pair<Mixed, Mixed> p;
    if (stackOperations[i - 1] == "+") {
      p = m1 + m2;
    } else {
      p = m1 - m2;
    }
    *stackPointerVariables[i] = p.first.lexeme;
    *stackPointerVariables[i - 1] = p.second.lexeme;
  }
  map<TypeLexeme, string> a = {{TypeLexeme::INT, "int"},
                               {TypeLexeme::FLOAT, "float"},
                               {TypeLexeme::STRING, "string"}};
  return a[(*stackPointerVariables[0]).type];
}

Node *Parser::processingOpInput(Node *root) {
  Node *pointToInput = root;
  string strOut = pointToInput->left->left->token.lexeme.substr(1, pointToInput->left->left->token.lexeme.size() - 2); // строка, которую выводим
  cout << strOut;
  string strIn; // строка, которую читаем
  cin >> strIn;
  Lexeme l;
  pointToInput->token.lexeme = strIn;
  if (l.isInt(strIn)) {
    pointToInput->token.type = TypeLexeme::INT;
  } else if (l.isFloat(strIn)) {
    pointToInput->token.type = TypeLexeme::FLOAT;
  } else {
    pointToInput->token.type = TypeLexeme::STRING;
    pointToInput->token.lexeme = "\"" + strIn;
    pointToInput->token.lexeme += "\"";
  }
  pointToInput->left->token.lexeme = ";";
  pointToInput->left->token.type = TypeLexeme::SEMICOLON;
  pointToInput->left->left = nullptr;
  pointToInput->left->right = nullptr;
  return root;
}

Node *Parser::changeCommand(Node *head) { // Заменяет ключевой синтаксис C+- на синтаксис C++
  Node *root = head;
  while (root) {
    if (root->token.lexeme == "print") {
      root->token.lexeme = "cout <<";
    }
    if (root->token.lexeme == "val") {
      root->token.lexeme = "const " + goToLeftAndGetType(root);
    }
    if (root->token.lexeme == "var") {
      root->token.lexeme = goToLeftAndGetType(root);
    }
    root = root->right;
  }
  return head;
}