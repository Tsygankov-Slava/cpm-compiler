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
    f.path = f.EnterPath2File(); // Получаем от пользователя путь к файлу
    f.OpenFile(); // Открываем файл
    f.ReadFile(); // Читаем файл
    ArgumentsLexemes arr;
    arr = f.GetLexemes(f.Code); // Разбиваем код на лексемы и записываем их в массив arr
    p.ArrLexemes = arr.ArrLexemes; // Передаём массив лексем в парсер
    p.lenArrLex = arr.lenArrLexemes;
    //f.PrintLexemes();
    p.GetStackVariable(); // Получаем стек переменных
    //p.PrintStackVariable();
    p.GetStackConstant(); // Получаем стек констант
    //p.PrintStackConstant();
    if (p.Check_CorrectVariable_And_CorrectConstant_And_NoneType_And_Redefinition()){ // Проверка переменных
        node* ast = p.GetAST(); // Получаем AST кода для С+-
        //PrintAST(ast);
        node* astForCPP = p.GetASTForCPP(ast); // Получаем AST кода для C++
        //PrintAST(astForCPP);
        f.CreateFileCPP(f.path, astForCPP); // Создаём файл C++
    }
    f.ClearMemoryAndCloseFile(); // Очищаем памятьоп
    return 0;
}