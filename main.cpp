#include <iostream>
#include <set>

#include "File.h"
#include "Code.h"
#include "Parser.h"
#include "FileCPP.h"

// Лучше так не делать, на крайний случай импортировать конкретные
// символы, например:
//   using std::string;
//
// https://stackoverflow.com/questions/1452721/why-is-using-namespace-std-considered-bad-practice
using namespace std;
// По кодстайлу здесь должна быть пустая строка!
int main(int argc, char* argv[]) {
    string path;

    // Насчет стиля кода, вот тут у тебя блок if обернут
    // в фигурные скобки, но блок else, нет, это плохо.
    // Также отсутствие перед else пробела это плохо.
    // В кодстайле обычно в таких местах присутствует пробел.
    if (argc > 1) {
        path = argv[1];
     // Не уверен в необходимости здесь этого ввода, лучше здесь показать ошибку в которой
     // описать как правильно передавать файл.
     // Например:
     //   No input file.
     //   Usage:
     //     spm FILE.cpm
     //
     // Также советую это сделать с помощью early return pattern:
     // https://softwareengineering.stackexchange.com/questions/18454/should-i-return-from-a-function-early-or-use-an-if-statement
     // То есть вместо:
     //   if (argc > 1) {
     //      path = argv[1];
     //   } else {
     //      std::cout << "No input file. ...";
     //   }
     //
     // Написать вот так:
     //   // Обрабатываем ошибочный случай первым и делаем сразу return.
     //   if (argc == 1) {
     //      std::cout << "No input file. ...";
     //      // Обрати внимание, что мы возвращаем код не 0, а 1, это
     //      // это признак, что что-то пошло не так. Если что-то пошло не так
     //      // то твоя программа не должна завершаться с кодом завершения 0!
     //      return 1;
     //   }
     //
     //   // А после уже спокойно напрямую присваиваем путь к файлу переменной.
     //   const string path = argv[1];
    }else cin >> path;

    File f(path);
    // Обычно имена методов пишутся в lowerCamelCase или в snake_case.
    // Насколько я знаю, такое наименование в C#, но в С++ лучше использовать
    // одно из двух выше.
    // Вот, например, что говорит Google C++ Code style:
    // https://gist.github.com/derofim/df604f2bf65a506223464e3ffd96a78a#function-names
    f.OpenAndReadFile();

    // Если у тебя есть некая абстракция над файлом, то имеет смысл
    // использовать ее дальше, то есть класс Code должен в себе
    // содержать объект класса File.
    Code code(f.code);
    code.GetTokens();

    Parser p(code.tokens);

    // Нечитаемая конструкция, все слиплось в одну строку!
    // Тут после if нет пробела, выше пробел есть, стиль кода
    // не выдержан!
    // Советую пользоваться форматированием кода в IDE,
    // если ты все еще не используешь CLion, то очень советую
    // для плюсов очень крутая штука, там так же есть
    // автоматическое форматирование.
    if(p.CheckAndPrintWrong())exit(0);
    node* head = p.GetAST();
    node* root = p.ChangeCommand(head);

    FileCpp fileCpp(path);
    fileCpp.CreateFileCPP(root);

    return 0;
}