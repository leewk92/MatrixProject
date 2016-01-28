#include "Global.h"


double add(double a, double b){ return a+b;}
double sub(double a, double b){ return a-b;}
double mult(double a, double b){ return a*b;}
double devi(double a, double b){ return a/b;}

void Tokenize(const string& str, vector<string>& tokens, const string& silcer = " ")
{
    // �� ù ���ڰ� �������� ��� ����
    string::size_type lastPos = str.find_first_not_of(silcer, 0);
    // �����ڰ� �ƴ� ù ���ڸ� ã�´�
    string::size_type pos = str.find_first_of(silcer, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // token�� ã������ vector�� �߰��Ѵ�
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // �����ڸ� �پ�Ѵ´�. 
        lastPos = str.find_first_not_of(silcer, pos);
        // ���� �����ڰ� �ƴ� ���ڸ� ã�´�
        pos = str.find_first_of(silcer, lastPos);
    }
}