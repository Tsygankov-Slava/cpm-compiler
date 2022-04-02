#include <iostream>
#include "File.h"
#include "Parser.h"
#include "ArgumentsLexemes.h"
#include "AST.h"
#include "Mixed.h"
using namespace std;
int main() {
    File f;
    Parser p;
    f.path="/Users/tv/Desktop/file.txt";
    //f.path = f.EnterPath2File();
    f.OpenFile();
    f.ReadFile();
    ArgumentsLexemes arr;
    arr = f.GetLexemes(f.Code);
    p.ArrLexemes = arr.ArrLexemes;
    p.lenArrLex = arr.lenArrLexemes;
    //f.PrintLexemes();
    p.GetStackVariable();
    //p.PrintStackVariable();
    p.GetStackConstant();
    //p.PrintStackConstant();
    if (p.Check_CorrectVariable_And_CorrectConstant_And_NoneType_And_Redefinition()){
//        node* ast = p.GetAST();
//        PrintAST(ast);
        Mixed M;
        string a = "hello";
        string b = "world";
        M.PrintPair(M.F(a,b,"+"));
    }
    f.ClearMemoryAndCloseFile();
    return 0;
}