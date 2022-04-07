#include <iostream>
#include <set>

#include "File.h"
#include "Code.h"
#include "Parser.h"
#include "FileCPP.h"

using namespace std;
int main(int argc, char* argv[]) {
    string path;
    if (argc > 1) {
        path = argv[1];
    }else cin >> path;

    File f(path);
    f.OpenAndReadFile();

    Code code(f.code);
    code.GetTokens();

    Parser p(code.tokens);
    if(p.CheckAndPrintWrong())exit(0);
    node* head = p.GetAST();
    node* root = p.ChangeCommand(head);

    FileCpp fileCpp(path);
    fileCpp.CreateFileCPP(root);

    return 0;
}