#ifndef COMPILER_MIXED_H
#define COMPILER_MIXED_H

#include <iostream>
#include <string>
#include<sstream>
using namespace std;

enum Type{
    INT, FLOAT, STRING
};
struct Pair{
    Type type;
    int first_int;
    int second_int;

    float first_float;
    float second_float;

    string first_string = "";
    string second_string = "";

};
struct Mixed{
    template<typename Type1, typename Type2>
    Pair F(Type1 a, Type2 b, string operation){
        Pair p;
        if ( (typeid(Type1) == typeid(string)&&((typeid(Type2) == typeid(int))||(typeid(Type2) == typeid(float))))
        ||   (typeid(Type2) == typeid(string)&&((typeid(Type1) == typeid(int))||(typeid(Type1) == typeid(float)))) ){
            if (operation == "+") {
                p.type = Type::STRING;
                stringstream stream;
                if (typeid(Type1) == typeid(string)) {
                    p.first_string = a;
                    stream << b;
                    stream >> p.second_string;
                } else if (typeid(Type2) == typeid(string)) {
                    stream << a;
                    stream >> p.first_string;
                    p.second_string = b;
                }
            }else if (operation == "-"){
                if ((typeid(Type1) == typeid(int))||(typeid(Type2) == typeid(int))){
                    bool flag = 1;
                    string str = "";
                    int pos_str;
                    if (typeid(Type1) == typeid(string)){str = a; pos_str = 1;}
                    else { str = b; pos_str = 2;}
                    for (int i = 0; i < str.size(); i++)if ((int(str[i]) < 48)||(int(str[i]) > 57)){flag = 0; break;}
                    p.type = Type::INT;
                    if (flag){
                        stringstream s1;
                        s1 << a;
                        s1 >> p.first_int;
                        stringstream s2;
                        s2 << b;
                        s2 >> p.second_int;
                    }else{
                        if (pos_str == 1){
                            p.first_int = 0;
                            stringstream s2;
                            s2 << b;
                            s2 >> p.second_int;
                        }else{
                            stringstream s1;
                            s1 << a;
                            s1 >> p.first_int;
                            p.second_int = 0;
                        }
                    }
                }else if ((typeid(Type1) == typeid(float))||(typeid(Type2) == typeid(float))){
                    bool flag = 1;
                    string str = "";
                    int pos_str;
                    if (typeid(Type1) == typeid(string)){str = a; pos_str = 1;}
                    else { str = b; pos_str = 2;}
                    for (int i = 0; i < str.size(); i++)if (((int(str[i]) < 48)||(int(str[i]) > 57))&&(int(str[i]) != 46)){flag = 0; break;}
                    p.type = Type::FLOAT;
                    if (flag){
                        stringstream s1;
                        s1 << a;
                        s1 >> p.first_float;
                        stringstream s2;
                        s2 << b;
                        s2 >> p.second_float;
                    }else{
                        if (pos_str == 1){
                            p.first_float = 0;
                            stringstream s2;
                            s2 << b;
                            s2 >> p.second_float;
                        }else{
                            stringstream s1;
                            s1 << a;
                            s1 >> p.first_float;
                            p.second_float = 0;
                        }
                    }
                }
            }
        }else if ((typeid(Type1) == typeid(float)&&(typeid(Type2) == typeid(int)))
              || (typeid(Type2) == typeid(float)&&(typeid(Type1) == typeid(int)))){
            p.type = Type::FLOAT;
            stringstream s1;
            s1 << a;
            s1 >> p.first_float;
            stringstream s2;
            s2 << b;
            s2 >> p.second_float;
        }else {
            if (typeid(Type1) == typeid(int)){
                p.type = Type::INT;
                stringstream s1;
                s1 << a;
                s1 >> p.first_int;
                stringstream s2;
                s2 << b;
                s2 >> p.second_int;
            }else if (typeid(Type1) == typeid(float)){
                p.type = Type::FLOAT;
                stringstream s1;
                s1 << a;
                s1 >> p.first_float;
                stringstream s2;
                s2 << b;
                s2 >> p.second_float;
            }else if (typeid(Type1) == typeid(string)){
                p.type = Type::STRING;
                stringstream s1;
                s1 << a;
                s1 >> p.first_string;
                stringstream s2;
                s2 << b;
                s2 >> p.second_string;
            }
        }
        return p;
    }
    void PrintPair(Pair p){
        if (p.type == Type::STRING)cout << p.first_string << " " << typeid(p.first_string).name() << " " << p.second_string << " " << typeid(p.second_string).name();
        else if (p.type == Type::INT)cout << p.first_int << " " << typeid(p.first_int).name() << " " << p.second_int << " " << typeid(p.second_int).name();
        else if (p.type == Type::FLOAT)cout << p.first_float << " " << typeid(p.first_float).name() << " " << p.second_float << " " << typeid(p.second_float).name();
    }
};
#endif
