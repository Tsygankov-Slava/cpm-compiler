#include "FileCPP.h"

void FileCpp::createFileCPP(Node *head) { // Создаёт файл .cpp и записывает в него код на С++
  ofstream out;
  path = path.substr(0, path.size() - 3) + "cpp";
  out.open(path);
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
    cout << "File .cpp didn't created";
  }
}
