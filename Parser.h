#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include "Lexer.h"
#include "ArgumentsLexemes.h"
#include "AST.h"
#include "Mixed.h"
struct PairForTranslate{
    string CommandCPM;
    string CommandCPP;
};
const int COUNTCOMMANDSFORTRANSLATE = 4;
PairForTranslate CommandsForTranslate[COUNTCOMMANDSFORTRANSLATE] = {
                                            {"print", "cout << "},
                                            {"input", "cin >> "},
                                            {"(", "DELETE"},
                                            {")", "DELETE"}
                                         };
class Parser{
public:
    int CountStackVariable = 10;
    string* StackVariable = new string [CountStackVariable];
    int lenStackVariable = 0;
    int CountStackConstant= 10;
    string* StackConstant = new string [CountStackConstant];
    int lenStackConstant = 0;
    int lenArrLex = 0;
    Lexeme* ArrLexemes = new Lexeme;

public:
    string* CheckStackVariableMemory(){
        if (this->CountStackVariable - this->lenStackVariable < 3){
            string* StackVariable2 = new string [this->CountStackVariable*2];
            for (int i = 0; i < this->lenStackVariable; i++)StackVariable2[i] = StackVariable[i];
            this->CountStackVariable *= 2;
            delete [] StackVariable;
            return StackVariable2;
        }else return StackVariable;
    }
    string* CheckStackConstantMemory(){
        if (this->CountStackConstant - this->lenStackConstant < 3){
            string* StackConstant2 = new string [this->CountStackConstant*2];
            for (int i = 0; i < this->lenStackConstant; i++)StackConstant2[i] = StackConstant[i];
            this->CountStackConstant *= 2;
            delete [] StackConstant;
            return StackConstant2;
        }else return StackConstant;
    }
    void GetStackVariable(){
        for (int i = 0; i < lenArrLex; i++){
            if (arr_type_lexeme[int(ArrLexemes[i].type)] == "VAR"){
                StackVariable = CheckStackVariableMemory();
                StackVariable[lenStackVariable] = ArrLexemes[i+1].lexeme;
                lenStackVariable++;
            }
        }
    }
    void PrintStackVariable(){
        cout << "----------------------------------STACK VARIABLE----------------------------------\n";
        for (int i = 0; i < this->lenStackVariable; i++)cout << this->StackVariable[i] << "\n";
    }
    void GetStackConstant(){
        for (int i = 0; i < lenArrLex; i++){
            if (arr_type_lexeme[int(ArrLexemes[i].type)] == "VAL"){
                StackConstant = CheckStackConstantMemory();
                StackConstant[lenStackConstant] = ArrLexemes[i+1].lexeme;
                lenStackConstant++;
            }
        }
    }
    void PrintStackConstant(){
        cout << "----------------------------------STACK CONSTANT----------------------------------\n";
        for (int i = 0; i < this->lenStackConstant; i++)cout << this->StackConstant[i] << "\n";
    }

    ArgumentsLexemes CheckVariables(){
        Lexeme* arr = new Lexeme [lenStackVariable+lenStackConstant];
        int lenArr = 0;
        Lexeme* arr2 = new Lexeme [lenStackVariable+lenStackConstant];
        int lenArr2 = 0;
        for (int i = 0; i < lenArrLex; i++){
            if ((arr_type_lexeme[int(ArrLexemes[i].type)] == "VAR")||(arr_type_lexeme[int(ArrLexemes[i].type)] == "VAL")){
                arr[lenArr] = ArrLexemes[i+1];
                lenArr++;
            }
            if (arr_type_lexeme[int(ArrLexemes[i].type)] == "NAMEVARIABLE"){
                bool flag = 1;
                for (int j = 0; j < lenArr; j++)
                    if (ArrLexemes[i].lexeme == arr[j].lexeme)flag = 0;
                for (int j = 0; j < lenArr2; j++)
                    if(ArrLexemes[i].lexeme == arr2[j].lexeme)flag=0;
                if (flag){
                    arr2[lenArr2] = ArrLexemes[i];
                    lenArr2++;
                }
            }
        }
        return {arr2, lenArr2};
    }
    ArgumentsLexemes CheckConstants(){
        Lexeme* arr = new Lexeme [lenStackVariable+lenStackConstant];
        int lenArr = 0;
        for (int i = 0; i < lenArrLex; i++){
            if (arr_type_lexeme[int(ArrLexemes[i].type)] == "VAL"){
                arr[lenArr] = ArrLexemes[i+1];
                lenArr++;
            }
        }
        Lexeme* arr2 = new Lexeme [lenStackVariable+lenStackConstant];
        int lenArr2 = 0;
        for (int i = 0; i < lenArrLex; i++){
            for (int j = 0; j < lenArr; j++){
                if (ArrLexemes[i].lexeme == arr[j].lexeme){
                    if ((arr_type_lexeme[int(ArrLexemes[i+1].type)] == "EQUALLY")&&(arr_type_lexeme[int(ArrLexemes[i-1].type)] != "VAL")){
                        arr2[lenArr2] = ArrLexemes[i];
                        lenArr2++;
                    }
                }
            }
        }
        return {arr2, lenArr2};
    }
    ArgumentsLexemes CheckNoneType(){
        Lexeme* arr = new Lexeme [lenArrLex];
        int lenArr = 0;
        for (int i = 0; i < lenArrLex; i++){
            if (arr_type_lexeme[int(ArrLexemes[i].type)] == "NONETYPE"){
                bool flag = 1;
                for (int j = 0; j < lenArr; j++)if (arr[j].lexeme == ArrLexemes[i].lexeme)flag = 0;
                if (flag) {
                    arr[lenArr] = ArrLexemes[i];
                    lenArr++;
                }
            }
        }
        return {arr, lenArr};
    }
    ArgumentsLexemes CheckRedefinitionVariablesOrConstants(){
        Lexeme* arr = new Lexeme [lenStackVariable+lenStackConstant];
        int lenArr = 0;
        for (int i = 0; i < lenArrLex; i++){
            if ((arr_type_lexeme[int(ArrLexemes[i].type)] == "VAR")||(arr_type_lexeme[int(ArrLexemes[i].type)] == "VAL")){
                arr[lenArr] = ArrLexemes[i+1];
                lenArr++;
            }
        }
        Lexeme* arr2 = new Lexeme [lenStackVariable+lenStackConstant];
        int lenArr2 = 0;
        for (int i = 0; i < lenArr-1; i++){
            for (int j = i+1; j < lenArr; j++){
                if (arr[i].lexeme == arr[j].lexeme){
                    arr2[lenArr2] = arr[i];
                    lenArr2++;
                }
            }
        }
        return {arr2, lenArr2};
    }
    void PrintLexemes(ArgumentsLexemes arg){
        for (int i = 0; i < arg.lenArrLexemes; i++){
            cout << "\n" << arg.ArrLexemes[i].lexeme;
        }
        cout << "\n";
    }
    bool Check_CorrectVariable_And_CorrectConstant_And_NoneType_And_Redefinition(){
        bool result = 1;

        ArgumentsLexemes unidentifiable;
        unidentifiable = CheckVariables();
        if (unidentifiable.lenArrLexemes) {
            cout << "ERROR!\n";
            cout << unidentifiable.lenArrLexemes;
            if (unidentifiable.lenArrLexemes == 1) cout <<  " variable which undefined:";
            else cout <<  " variables which undefined:";
            PrintLexemes(unidentifiable);
            result = 0;
        }

        ArgumentsLexemes changingConstants;
        changingConstants = CheckConstants();
        if (changingConstants.lenArrLexemes) {
            cout << "ERROR!\n";
            cout << changingConstants.lenArrLexemes;
            if (changingConstants.lenArrLexemes == 1) cout <<  " constant which changing:";
            else cout <<  " constants which changing:";
            PrintLexemes(changingConstants);
            result = 0;
        }
        ArgumentsLexemes TypeNoneType;
        TypeNoneType = CheckNoneType();
        if (TypeNoneType.lenArrLexemes){
            cout << "ERROR!\n";
            cout << TypeNoneType.lenArrLexemes;
            if (TypeNoneType.lenArrLexemes == 1) cout <<  " type - NoneType:";
            else cout <<  " types - NoneType:";
            PrintLexemes(TypeNoneType);
            result = 0;
        }
        ArgumentsLexemes RedefinitionVariables;
        RedefinitionVariables = CheckRedefinitionVariablesOrConstants();
        if (RedefinitionVariables.lenArrLexemes){
            cout << "ERROR!\n";
            cout << RedefinitionVariables.lenArrLexemes;
            if (RedefinitionVariables.lenArrLexemes == 1) cout <<  " redefinition variable or constant:";
            else cout <<  " redefinition variables or constants:";
            PrintLexemes(RedefinitionVariables);
            result = 0;
        }
        return result;
    }

    node* GetAST() {
        if (lenArrLex) {
            node *head = MakeHead(ArrLexemes[0]);
            bool flagAddLeft = 1;
            for (int i = 1; i < lenArrLex; i++) {
                if (flagAddLeft)head = Add2Left(head, ArrLexemes[i]);
                else{
                    head = Add2Right(head, ArrLexemes[i]);
                    flagAddLeft = 1;
                }
                if (arr_type_lexeme[int(ArrLexemes[i].type)] == "SEMICOLON")flagAddLeft = 0;
            }
            return head;
        }
        return 0;
    }

    node* ChangeVariableInABS(node* head, int number, Lexeme lex){
        int flag = -1;
        node* root = head;
        while (flag != number){
            root = root->left;
            flag++;
        }
        root->lex.lexeme = lex.lexeme;
        root->lex.type = lex.type;
        return head;
    }

    node* ChangeCommand(node* head){
        node* root = head;
        if ((arr_type_lexeme[int(root->lex.type)] == "VAR")||(arr_type_lexeme[int(root->lex.type)] == "VAL")){
            bool flagVal = 0;
            if (arr_type_lexeme[int(root->lex.type)] == "VAL")flagVal = 1;
            root = root->left;
            int countLexeme = 100;
            Lexeme* arrLexemeVariable = new Lexeme [countLexeme];
            int lenLexemeVariable = 0;
            int* arrNumberVariableInExp = new int [countLexeme];
            int lenArrNumberVariableInExp = 0;
            Lexeme* arrLexemeOperation = new Lexeme [countLexeme];
            int lenLexemeOperation = 0;
            while (root->lex.lexeme != ";"){
                if ((arr_type_lexeme[int(root->lex.type)] == "INT")||(arr_type_lexeme[int(root->lex.type)] == "FLOAT")||(arr_type_lexeme[int(root->lex.type)] == "STRING")||(arr_type_lexeme[int(root->lex.type)] == "NAMEVARIABLE")){
                    arrLexemeVariable[lenLexemeVariable] = root->lex;
                    arrNumberVariableInExp[lenLexemeVariable] = lenArrNumberVariableInExp;
                    lenLexemeVariable++;
                }
                if ((arr_type_lexeme[int(root->lex.type)] == "PLUS")||(arr_type_lexeme[int(root->lex.type)] == "MINUS")){
                    arrLexemeOperation[lenLexemeOperation] = root->lex;
                    lenLexemeOperation++;
                }
                root = root->left;
                lenArrNumberVariableInExp++;
            }
            if (lenLexemeVariable == 2){
                if (arr_type_lexeme[int(arrLexemeVariable[1].type)] == "INT")head->lex.lexeme = "int";
                else if (arr_type_lexeme[int(arrLexemeVariable[1].type)] == "FLOAT")head->lex.lexeme = "float";
                else if (arr_type_lexeme[int(arrLexemeVariable[1].type)] == "STRING")head->lex.lexeme = "string";
            }else{
                Mixed M;
                Pair p;
                for (int i = 1; i < lenLexemeVariable-1; i++) {
                    p = M.GetType(arrLexemeVariable[i], arrLexemeVariable[i+1], arrLexemeOperation[i-1].lexeme);
                    arrLexemeVariable[i].type = p.first.type;
                    arrLexemeVariable[i].lexeme = p.first.lexeme;
                    arrLexemeVariable[i+1].type = p.second.type;
                    arrLexemeVariable[i+1].lexeme = p.second.lexeme;
                    head = ChangeVariableInABS(head, arrNumberVariableInExp[i], arrLexemeVariable[i]);
                    head = ChangeVariableInABS(head, arrNumberVariableInExp[i+1], arrLexemeVariable[i+1]);
                }
                for (int i = lenLexemeVariable-1; i > 1; i--){
                    p = M.GetType(arrLexemeVariable[i], arrLexemeVariable[i-1], arrLexemeOperation[i-2].lexeme);
                    stringstream s1;
                    arrLexemeVariable[i].lexeme = p.first.lexeme;
                    arrLexemeVariable[i-1].type = p.second.type;
                    arrLexemeVariable[i-1].lexeme = p.second.lexeme;
                    head = ChangeVariableInABS(head, arrNumberVariableInExp[i], arrLexemeVariable[i]);
                    head = ChangeVariableInABS(head, arrNumberVariableInExp[i-1], arrLexemeVariable[i-1]);
                }
                if (arr_type_lexeme[int(arrLexemeVariable[1].type)] == "INT")head->lex.lexeme = "int";
                else if (arr_type_lexeme[int(arrLexemeVariable[1].type)] == "FLOAT")head->lex.lexeme = "float";
                else if (arr_type_lexeme[int(arrLexemeVariable[1].type)] == "STRING")head->lex.lexeme = "string";
            }
            if (flagVal)head->lex.lexeme = "const " + head->lex.lexeme;
            return head;
        }else if (arr_type_lexeme[int(root->lex.type)] == "PRINT"){
            node* root = head;
            node* last = head;
            head->lex.lexeme = "cout <<";
            while (root->lex.lexeme != ";"){
                if (root->lex.lexeme == "(")last->left = root->left;
                if (root->lex.lexeme == ")") root->lex.lexeme = " << \"\\n\"";
                last = root;
                root = root->left;
            }
            return head;
        }else if (arr_type_lexeme[int(root->lex.type)] == "INPUT"){
        }
        return head;
    }
    node* GetASTForCPP(node* head) {
        node* root = head;
        node* root2 = root->left; // Обходит влево
        node* last = root;
        while (root){
            root = ChangeCommand(root);
            if (root->right == nullptr)break;
            root = root->right;
        }
    }

    void ClearMemory(){
        delete [] StackVariable;
        delete [] StackConstant;
        delete [] ArrLexemes;
    }
};
#endif

