#pragma once

#include <iostream>
#include <vector>

#include "../Lexer/Lexer.h"

using std::cout;
using std::vector;

class Node {
public:
  Lexeme token;
  Node *left = nullptr;
  Node *right = nullptr;

public:
  Node *makeHead(Lexeme lex);
  Node *addToLeft(Node *head, Lexeme lex);
  Node *addToRight(Node *head, Lexeme lex);
  Node *addNewNode(Node *head, vector<Lexeme>);
  void printAST(Node *head);
};
