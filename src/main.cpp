#include "polish_notation.h"
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <set>
using namespace std;



int main() {
	string str;
	cout << "Enter the expression: ";
	cin >> str;
	int nexPos = 0;
	cout << getLexema(str,0,nexPos).value;

	/*while (!bracketCheck(str)) {
		cout << "Wrong expression, try one more time: ";
		cin >> str;
	}
	arithmeticExpr expr(str);
	cout << expr.getInfix() << endl;
	cout << expr.getPostfix() << endl;*/
 }
