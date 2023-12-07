#include "polish_notation.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <stack>
using namespace std;



int main() {
	string str;
	std::cout << "Enter the expression: ";
	getline(cin, str);
	while (!bracketCheck(str)) {
		cout << "Wrong expression, try one more time: ";
		cin >> str;
	}
	arithmeticExpr expr(str);
	try{expr.parse(expr.getInfix()); }
	catch (...) {
		cout << "something went wrong";
		return 0;
	};
	expr.print();
	/*
	arithmeticExpr expr(str);
	cout << expr.getInfix() << endl;
	cout << expr.getPostfix() << endl;*/
 }
