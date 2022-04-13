#include "AST.h"

Node *Node::makeHead(Lexeme lex) {
  Node *head = new Node;
  head->token = lex;
  return head;
}

Node *Node::addToLeft(Node *head, Lexeme lex) {
  Node *root = head;
  while (root->right != nullptr) {
    root = root->right;
  }
  while (root->left != nullptr) {
    root = root->left;
  }
  root->left = new Node;
  root->left->token = lex;
  return head;
}

Node *Node::addToRight(Node *head, Lexeme lex) {
  Node *root = head;
  while (root->right != nullptr) {
    root = root->right;
  }
  root->right = new Node;
  root->right->token = lex;
  return head;
}

Node *Node::addNewNode(Node *head, vector<Lexeme> lexeme) {
  Node *next = head->right;
  head->right = new Node;
  head->right->right = next;
  Node *root = head->right;
  for (auto i : lexeme) {
    root->token = i;
    root->left = new Node;
    root = root->left;
  }
  return head->right;
}

void Node::printAST(Node *head) {
  Node *root = head;
  Node *root2 = root->left; // Обходит влево
  while (root) {
    cout << root->token.lexeme << " ";
    while (root2) {
      cout << root2->token.lexeme << " ";
      root2 = root2->left;
    }
    if (root->right == nullptr) {
      break;
    }
    root = root->right;
    root2 = root->left;
  }
}