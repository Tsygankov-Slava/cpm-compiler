#ifndef COMPILER_CODE_H
#define COMPILER_CODE_H
class Code : Lexeme{
public:
    string code;
    vector<Lexeme> tokens;

    Code(string code){
        this->code = code;
    }

    void GetTokens(){
        int iterator = 0;
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
#endif
