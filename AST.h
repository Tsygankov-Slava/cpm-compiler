#ifndef COMPILER_AST_H
#define COMPILER_AST_H
#include "Lexer.h"
struct node{
    Lexeme lex;
    node* left = nullptr;
    node* right = nullptr;
};

node* MakeHead(Lexeme lex){
    node* head = new node;
    head->lex = lex;
    return head;
}

node* Add2Left(node* head, Lexeme lex){
    node* root = head;
    while (root->right != nullptr)root = root->right;
    while (root->left != nullptr)root = root->left;
    root->left = new node;
    root->left->lex = lex;
    return head;
}

node* Add2Right(node* head, Lexeme lex){
    node* root = head;
    while (root->right != nullptr)root = root->right;
    root->right = new node;
    root->right->lex = lex;
    return head;
}

void PrintAST(node* head){
    node* root = head;
    node* root2 = root->left; // Обходит влево
    while (root){
        cout << root->lex.lexeme << " ";
        while (root2){
            cout << root2->lex.lexeme << " ";
            root2 = root2->left;
        }
        cout << "\n";
        if (root->right == nullptr)break;
        root = root->right;
        root2 = root->left;
    }
}
#endif
