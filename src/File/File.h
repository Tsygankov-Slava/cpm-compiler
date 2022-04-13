#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::ifstream;
using std::string;

class File {
private:
  ifstream file;    // Объект файла
  string path = ""; // Путь к файлу
public:
  // Если у тебя есть геттер getCode, то почему это свойство
  // публично? Если оно публично, то не нужен геттер, если есть
  // геттер, то нужно сделать его приватным.
  string code = ""; // Код файла

public:
  // Если ты используешь CLion, то не игнорируй предупреждения
  // которые он дает. Если у тебя тут их почему-то нет, то
  // погугли как включить в нем Clang Tidy.
  // Я не буду отмечать все ошибки которые он показывает, надеюсь
  // ты сам пройдешься по файлам и поправишь.
  File(const string &path) : path(path){};
  // Мне кажется имеет смысл разделять конструктор и методы пустой строкой.
  void openAndReadFile();
  string getCode();
};
