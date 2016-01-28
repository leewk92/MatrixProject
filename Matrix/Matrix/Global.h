#ifndef GLOBAL_H
#define GLOBAL_H
#include <vector>
#include <cstring>
using namespace std;

const double SMALLVAL = 0.0000001;

double add(double a, double b);
double sub(double a, double b);
double mult(double a, double b);
double devi(double a, double b);

void Tokenize(const string& str, vector<string>& tokens, const string& silcer);

#endif