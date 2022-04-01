#include <iostream>
#include "File.h"
#include "Parser.h"
#include "ArgumentsLexemes.h"

int main() {
    File f;
    Parser p;
    f.path="/Users/tv/Desktop/file.txt";
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
        cout << "OK";
    }
    f.ClearMemoryAndCloseFile();
    return 0;
}