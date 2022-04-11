#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H
#include <vector>
#include <map>
#include <set>

#include "AST.h"
#include "Mixed.h"

class Parser{
public:
    // Вот эти поля должны быть приватными, так как не используются вне класса!
    // Лишние пробелы между "map" и "<" здесь и далее.
    map <string, bool> stackVariables;
    map <string, bool> stackConstants;
    vector <Lexeme> tokens;

public:
    Parser(vector <Lexeme> tokens){ // Вот здесь нужно передавать аргумент по ссылке, чтобы не копировать вектор 2 раза!
        this->tokens = tokens;
    }

    set<string> FindWrongVariables(){ // Ищет переменные(в том числе константы), которые объявлены дважды или неинициализированы вообще
        set <string> arrWrongVariables;
        for (int i = 0; i < this->tokens.size(); i++) {
            if ((this->tokens[i].type == TypeLexeme::NAMEVARIABLE) && (!this->stackVariables[this->tokens[i].lexeme]))
                arrWrongVariables.insert(this->tokens[i].lexeme);
            if ((this->tokens[i].lexeme == "var") || ((this->tokens[i].lexeme == "val"))) {
                if (!stackVariables[this->tokens[i + 1].lexeme])
                    stackVariables[this->tokens[i + 1].lexeme] = true;
                else arrWrongVariables.insert(this->tokens[i + 1].lexeme);
            }
        }
        return arrWrongVariables;
    }

    void GetConstants(){ // Получаем массив с константами
        for (int i = 0; i < this->tokens.size(); i++)
            if (this->tokens[i].lexeme == "val")
                stackConstants[this->tokens[i + 1].lexeme] = true;
    }

    set<string> FindWrongConstants(){ // Ищет константы, которые перезаписываются
        set <string> arrWrongConstants;
        this->GetConstants();
        for (int i = 0; i < this->tokens.size(); i++)
           // Не нужно писать явно "== true"&
           if ((stackConstants[this->tokens[i].lexeme] == true)&&(((i >= 1) ? this->tokens[i-1].lexeme : " ") != "val"))
               arrWrongConstants.insert(this->tokens[i].lexeme);
        return arrWrongConstants;
    }

    void PrintSet(set<string> a){
        set <string> :: iterator it;
        for (it = a.begin(); it != a.end(); it++)
            cout << *it << "\n";
    }
    // Здесь должна идти пустая строка.
    set<string> FindNoneType(){ // Ищет нераспознанные лексемы
        set <string> arrNoneType;
        for (int i = 0; i < this->tokens.size(); i++)
            if (this->tokens[i].type == TypeLexeme::NONETYPE)
                arrNoneType.insert(this->tokens[i].lexeme);
        return arrNoneType;
    }
    // Здесь должна идти пустая строка.
    bool CheckAndPrintWrong(){
        bool wrong = false;
        set<string> a ;
        a = this->FindWrongVariables();
        if (!a.empty()){
            cout << "ERROR\nProbably this variables/constants is not initialized or announced twice: \n";
            this->PrintSet(a);
            wrong = true;
        }
        a = this->FindWrongConstants();
        if (!a.empty()){
            cout << "ERROR\nThis constants changing: \n";
            this->PrintSet(a);
            wrong = true;
        }
        a = this->FindNoneType();
        if (!a.empty()){
            cout << "ERROR\nNoneType: \n";
            this->PrintSet(a);
            wrong = true;
        }
        return wrong;
    }

    // Лишняя пустая строка.
    node* GetAST(){ //Создаёт дерево
        if (!this->tokens.empty()){
            node* head = MakeHead(this->tokens[0]);
            bool flagAddLeft = true;
            for (int i = 1; i < this->tokens.size(); i++){
                if (flagAddLeft)head = Add2Left(head, this->tokens[i]);
                else {head = Add2Right(head, this->tokens[i]); flagAddLeft = true;}
                if (this->tokens[i].lexeme == ";")flagAddLeft = false;
            }
            return head;
        }
        return 0;
    }
    // Здесь должна идти пустая строка.
    // Лучше не использовать замены "to" и "2", это не улучшает читаемость кода.
    string Go2LeftAndGetType(node* root){  // Обходит левую ветвь и определяет по ней тип переменной (вызывается в ChangeCommand)
        vector <Lexeme> stackVariablesLexeme;
        vector <Lexeme*> stackPointerVariables;
        vector <string> stackOperations;
        while (root->token.lexeme != ";"){
            if ((root->token.type == TypeLexeme::INT)||(root->token.type == TypeLexeme::FLOAT)||(root->token.type == TypeLexeme::STRING)) {
                stackVariablesLexeme.push_back(root->token);
                stackPointerVariables.push_back(&root->token);
            }
            if ((root->token.lexeme == "+")||(root->token.lexeme == "-"))
                stackOperations.push_back(root->token.lexeme);
            root = root->left;
        }
        Mixed Mixed;
        for (int i = 0; i < stackVariablesLexeme.size()-1; i++){
            pair<Lexeme, Lexeme> p;
            p = Mixed.GetType(make_pair(make_pair(stackVariablesLexeme[i], stackVariablesLexeme[i+1]), stackOperations[i]),
                              make_pair(stackPointerVariables[i], stackPointerVariables[i+1]));
            stackVariablesLexeme[i] = p.first;
            stackVariablesLexeme[i+1] = p.second;
        }
        map <TypeLexeme, string> a = {{TypeLexeme::INT, "int"}, {TypeLexeme::FLOAT, "float"}, {TypeLexeme::STRING, "string"}};
        for (int i = stackVariablesLexeme.size()-1; i > 0; i--){ // Цикл идёт в обратную сторону, чтобы изменить первые типы, относительно последних
            pair<Lexeme, Lexeme> p;
            p = Mixed.GetType(make_pair(make_pair(stackVariablesLexeme[i], stackVariablesLexeme[i-1]), stackOperations[i-1]),
                              make_pair(stackPointerVariables[i], stackPointerVariables[i-1]));
            stackVariablesLexeme[i] = p.first;
            stackVariablesLexeme[i-1] = p.second;
        }
        return a[stackVariablesLexeme[0].type];
    }
    // Здесь должна идти пустая строка.
    node* ChangeCommand(node* head){ // Заменяет ключевой синтаксис C+- на синтаксис C++
        node* root  = head;
        while (root){
            if (root->token.lexeme == "print")root->token.lexeme = "cout <<";
            if (root->token.lexeme == "val")root->token.lexeme = "const " + Go2LeftAndGetType(root);
            if (root->token.lexeme == "var")root->token.lexeme = Go2LeftAndGetType(root);
            root = root->right;
        }
        return head;
    }
};

#endif

