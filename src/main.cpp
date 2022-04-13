#include <iostream>
#include <string>

#include "AST/AST.h"
#include "Code/Code.h"
#include "File/File.h"
#include "FileCPP/FileCPP.h"
#include "Parser/Parser.h"

int main(int argc, char **argv) {
  if (argc == 1) {
    cout << "Argument \"Path to file\" not found\n";
    cout << "Program launch format: \"./Compiler (path to file)/file.cpm\"";
    return 1;
  } else if (argc > 2) {
    cout << "There are a lot of arguments\n";
    cout << "Program launch format: \"./Compiler (path to file)/file.cpm\"";
    return 2;
  }

  const string path = argv[1];
  File file(path);
  file.openAndReadFile();

  Code code(path, file.getCode());
  vector<Lexeme> tokens = code.getTokens();

  Parser p(tokens);
  if (p.checkAndPrintWrong()) {
    exit(0);
  }

  Node *head = p.getAST();
  Node *root = p.changeCommand(head);

  FileCpp fileCpp(path);
  fileCpp.createFileCPP(root);
  return 0;
}