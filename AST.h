#ifndef COMPILER_AST_H
#define COMPILER_AST_H
// Здесь должна идти пустая строка.
#include "Lexer.h"

// Это плохой подход, посмотри паттерн Visitor:
// https://cpppatterns.com/patterns/visitor.html
// И реализацию узлов через базовый абстрактный класс
// и конкретных наследников, например, Literal, FunctionCall, BinOp.
// После того как ты его реализуешь весь код проверки и генерации
// сильно упроситься и станет более понятным.
//
// Имя класса или структуры должно называться с большой буквы!
struct node{
    Lexeme token;
    node* left = nullptr;
    node* right = nullptr;
};

node* MakeHead(Lexeme lex){
    node* head = new node;
    head->token = lex;
    return head;
}

node* Add2Left(node* head, Lexeme lex){
    node* root = head;
    while (root->right != nullptr)root = root->right;
    while (root->left != nullptr)root = root->left;
    root->left = new node;
    root->left->token = lex;
    return head;
}

node* Add2Right(node* head, Lexeme lex){
    node* root = head;
    while (root->right != nullptr)root = root->right;
    root->right = new node;
    root->right->token = lex;
    return head;
}

void PrintAST(node* head){
    node* root = head;
    node* root2 = root->left; // Обходит влево
    while (root){
        cout << root->token.lexeme << " ";
        while (root2){
            cout << root2->token.lexeme << " ";
            root2 = root2->left;
        }
        if (root->right == nullptr)break;
        root = root->right;
        root2 = root->left;
    }
}
// Здесь должна идти пустая строка.
#endif
