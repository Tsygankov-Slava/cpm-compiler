#include "File.h"

void File::openAndReadFile() {
  file.open(path);
  if (file) {
    while (!file.eof()) {
      string str;
      getline(file, str); //Читаем из потока file строку и записываем его в str (читается одна строка, потому что separate[3-й параметр по умолчанию '\n'])
      code += str;
    }
  } else {
    cout << "The file is not open. Probably, your path is wrong.";
  }
}

string File::getCode() {
  return code;
}