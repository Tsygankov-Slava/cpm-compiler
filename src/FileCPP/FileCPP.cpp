#include "FileCPP.h"

// Функция должна возвращать bool.
// См. комментарий для класса File.
void FileCpp::createFileCPP(Node *head) { // Создаёт файл .cpp и записывает в него код на С++
  ofstream out;
  // А если там будет не 3 символа в расширении?
  // Лучше сделать поиск расширения и его замену.
  path = path.substr(0, path.size() - 3) + "cpp";
  out.open(path);
  // Лучше было в случае если файл не открылся выдать ошибку и сделать return,
  // а после уже без else написать код генерации.
  // Такой паттерн называется Early Return:
  // https://softwareengineering.stackexchange.com/questions/18454/should-i-return-from-a-function-early-or-use-an-if-statement
  //
  // То есть:
  // if (!out.is_open()) {
  //   cout << ...;
  //   return;
  // }
  //
  //  out << "#...
  if (out.is_open()) {
    out << "#include <iostream>\n#include <string>\nusing namespace std;\n";
    out << "int main(){\n";
    Node *rootRight = head;
    Node *rootLeft = rootRight->left;
    while (rootRight != nullptr) {
      out << "\t" << rootRight->token.lexeme << " ";
      while (rootLeft != nullptr) {
        out << rootLeft->token.lexeme << " ";
        rootLeft = rootLeft->left;
      }
      out << "\n";
      if (rootRight->right != nullptr) {
        rootRight = rootRight->right;
        rootLeft = rootRight->left;
      } else {
        break;
      }
    }
    out << "}";
  } else {
    // Тоже самое что и для класса File.
    cout << "File .cpp didn't created";
  }
}
