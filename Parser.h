#ifndef COMPILER_PARSER_H
#define COMPILER_PARSER_H

#include "Lexer.h"
#include "ArgumentsLexemes.h"
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
                for (int j = 0; j < lenArr; j++)if (ArrLexemes[i].lexeme == arr[j].lexeme)flag = 0;
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
                arr[lenArr] = ArrLexemes[i];
                lenArr++;
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
    void ClearMemory(){
        delete [] StackVariable;
        delete [] StackConstant;
        delete [] ArrLexemes;
    }
};
#endif

