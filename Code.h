#ifndef COMPILER_CODE_H
#define COMPILER_CODE_H
// Здесь должна идти пустая строка.
class Code : Lexeme{
public:
    // Поле не используется вне класса, поэтому должно быть сделано приватным!
    string code;
    vector<Lexeme> tokens;

    // Как и у File:
    //   Clang-Tidy: The parameter 'path' is copied for each invocation but only used as a const reference; consider making it a const reference
    // Также такие конструкторы можно записать в следующей форме:
    //   explicit Code(const string& code) : code(code) {}
    //
    // Вот тут вот можно почитать подробнее: https://en.cppreference.com/w/cpp/language/constructor
    Code(string code){
        this->code = code;
    }

    // Странно, что функция с префиксом Get ничего по факту не возвращает!
    // У тебя в main используется поле tokens, но лучше сделать его приватным,
    // а из этой функции возвращать список токенов и уже его использовать далее
    // в main.
    void GetTokens(){
        // Неправильно называть это итератором, это просто индекс.
        int iterator = 0;
        // Далее все те же проблемы с кодстайлом что были описаны ранее, попробуй использовать
        // автоматическое форматирование.
        char ch = this->code[iterator];
        string lex = "";
        bool flagNotString = true; // Переменная предназначена для того, чтобы отслеживать пробелы в типе String
        while (ch != '\0'){
            if ((ch == ';')||(ch == '-')||(ch == '+')||(ch == '=')||(ch == '(')||(ch == ')')||((ch == ' ')&&(flagNotString))||(ch == '\n')){ // Символы разделяющие код на лексемы, они же также являются лексемами
                if (lex != ""){
                    this->tokens.push_back({lex, Lexeme::TypeDefinition(lex)});
                    lex = "";
                }
                if ((ch != ' ')&&(ch != '\n')){ // Добавляем лексемы (разделители), которые упоминаются в условии выше
                    string s(1, ch); // char to string
                    this->tokens.push_back({s, Lexeme::TypeDefinition(s)});
                }
            }else{
                if (ch == '\"'){ // Определяем строку по символу "
                    if (flagNotString)flagNotString = false;
                    else flagNotString = true;
                }
                lex += ch;
            }
            ch = this->code[++iterator];
        }
    }

    void PrintTokens(){
        for (auto i : tokens)
            cout << i.lexeme << "\n";
    }
};
// Здесь должна идти пустая строка.
#endif
