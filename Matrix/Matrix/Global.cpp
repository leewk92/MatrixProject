#include "Global.h"


double add(double a, double b){ return a+b;}
double sub(double a, double b){ return a-b;}
double mult(double a, double b){ return a*b;}
double devi(double a, double b){ return a/b;}

void Tokenize(const string& str, vector<string>& tokens, const string& silcer = " ")
{
    // 맨 첫 글자가 구분자인 경우 무시
    string::size_type lastPos = str.find_first_not_of(silcer, 0);
    // 구분자가 아닌 첫 글자를 찾는다
    string::size_type pos = str.find_first_of(silcer, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // token을 찾았으니 vector에 추가한다
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // 구분자를 뛰어넘는다. 
        lastPos = str.find_first_not_of(silcer, pos);
        // 다음 구분자가 아닌 글자를 찾는다
        pos = str.find_first_of(silcer, lastPos);
    }
}