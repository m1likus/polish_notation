#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <stack>
#include <deque>
#include <stdio.h>
#include <iostream>
#include <cmath>
/*
currentStatus 			lexemeType 			nextStatus
waitSt					number				numberSt
waitSt					bin_operator		errorSt
waitSt					function			funcSt
waitSt					leftBracket			leftBracketSt
waitSt					rightBracket		errorSt
waitSt					un_minus			unMinSt
waitSt					end					end

numberSt				number				errorSt
numberSt 				bin_operator		binOperatorSt
numberSt				function			errorSt
numberSt				leftBracket			errorSt
numberSt				rightBracket		rightBracketSt
numberSt				un_minus			errorSt
numberSt				end					end

binOperatorSt			number				numberSt
binOperatorSt			bin_operator		errorSt
binOperatorSt			function			funcSt
binOperatorSt			leftBracket			leftBracketSt
binOperatorSt			rightBracket		errorSt
binOperatorSt			un_minus			errorSt
binOperatorSt			end					errorSt

funcSt					number				numberSt
funcSt					bin_operator		errorSt
funcSt					function			funcSt
funcSt					leftBracket			leftBracketSt
funcSt					rightBracket		errorSt
funcSt					un_minus			unMinSt
funcSt					end					errorSt

leftBracketSt			number				numberSt	
leftBracketSt			bin_operator		errorSt
leftBracketSt			function			funcSt
leftBracketSt			leftBracket			leftBracketSt
leftBracketSt			rightBracket		errorSt
leftBracketSt			un_minus			unMinSt
leftBracketSt			end					errorSt

rightBracketSt			number				errorSt	
rightBracketSt			bin_operator		binOperatorSt
rightBracketSt			function			errorSt
rightBracketSt			leftBracket			errorSt
rightBracketSt			rightBracket		rightBracketSt
rightBracketSt			un_minus			errorSt
rightBracketSt			end					end

unMinSt					number				numberSt
unMinSt					bin_operator		errorSt
unMinSt					function			funcSt
unMinSt					leftBracket			leftBracketSt
unMinSt					rightBracket		errorSt
unMinSt					un_minus			errorSt
unMinSt					end					errorSt

*/


using namespace std;
//проверка на цифру
bool isDigit(char c) {
	return (c >= '0' && c <= '9');
}
//проверка скобок
bool bracketCheck(string str) {
	int lb = 0, rb = 0;
	std::stack <int> s;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '(') {
			lb++;
			s.push(0);
		}
		else if (str[i] == ')') {
			rb++;
			if (!s.empty()) s.pop();
		}
	}
	if (s.empty() && lb == rb) return true;
	else return false;
}

//вычисление функций
double functionCalculating(string function, double operand) {
	if (function == "sin") return sin(operand);
	else if (function == "cos") return cos(operand);
	else if (function == "tg") return tan(operand);
	else if (function == "ctg") return (cos(operand) / sin(operand));
}
//вычисление с помощью операторов
double operatorCalculating(string bin_operator, double rightOperand, double leftOperand) {
	if (bin_operator == "+") return (leftOperand + rightOperand);
	else if (bin_operator=="-") return (leftOperand - rightOperand);
	else if (bin_operator=="*") return (leftOperand * rightOperand);
	else if (bin_operator=="/") return (leftOperand / rightOperand);
}
//унарный минус
double unOperator(double operand) {
	return (0 - operand);
}

//виды лексем
enum TypeLexeme {
	number,
	bin_operator,
	function,
	leftBracket,
	rightBracket,
	un_minus
};

struct Lexema {
	int value = 0;
	TypeLexeme type = TypeLexeme::number;
	string name;
};
//вывод лексемы
ostream& operator <<(ostream& os, const Lexema L) {
	if (L.type == number) return os << L.value;
	else if (L.type == bin_operator || L.type == leftBracket || L.type == rightBracket
		|| L.type == un_minus || L.type == function)
		return os << L.name;
}

enum Status {
	waitSt,
	numberSt,
	binOperatorSt,
	errorSt,
	funcSt,
	leftBracketSt,
	rightBracketSt,
	unMinSt	
};

struct arithmeticExpr {
	string infix;
	string postfixString;
	vector<Lexema> lexems;
	stack<Lexema> postfix;
	map <char, int> priority;
	
	Lexema getLexema(string input, int pos, int& nextPos) {
		Lexema lexeme;
		//if the symbols is number we start searching
		if (input[pos] == ' ') {
			pos++;
			nextPos++;
		}
		if (isDigit(input[pos])) {
			int value = input[pos] - '0';
			pos++;
			nextPos++;
			while (isDigit(input[pos])) {
				value *= 10;
				value += input[pos] - '0';
				pos++;
				nextPos++;
			}
			lexeme.value = value;
			lexeme.type = number;
		}
		//checking unary minus
		else if (input[pos] == '-' && pos == 0) {
			lexeme.type = un_minus;
			lexeme.name = input[pos];
			nextPos++;
		}
		else if (pos != 0 && input[pos] == '-' && (input[pos - 1] == '(')) {
				lexeme.type = un_minus;
				lexeme.name = input[pos];
				nextPos++;
		}
		// if the symbol is a binary operator
		else if (input[pos] == '+' || input[pos] == '-' || input[pos] == '*' || input[pos] == '/') {
			lexeme.type = bin_operator;
			lexeme.name = input[pos];
			nextPos++;
		}
		//if there's function
		else if (input[pos] == 's' || input[pos] == 'c') {
			string check = "";
			if (pos + 2 >= input.size()) throw("wrong");
			for (int i = 0; i < 3; i++) {
				check += input[pos + i];
			}
			if (check == "sin" || check == "cos" || check == "ctg") {
				nextPos += 3;
				lexeme.type = function;
				lexeme.name = check;
			}
		}
		else if (input[pos] == 't') {
			string check = "";
			if (pos + 1 >= input.size()) throw("wrong");
			for (int i = 0; i < 2; i++) {
				check += input[pos + i];
			}
			if (check == "tg") {
				nextPos += 2;
				lexeme.type = function;
				lexeme.name = check;
			}
		}
		//if a left bracket
		else if (input[pos] == '(') {
			lexeme.type = leftBracket;
			lexeme.name = input[pos];
			nextPos++;
		}
		//if there's right bracket
		else if (input[pos] == ')') {
			lexeme.type = rightBracket;
			lexeme.name = input[pos];
			nextPos++;
		}
		else throw ("wrong");
		return lexeme;
	}
public:
	void parse(string input) {
		int pos = 0, next_pos = 0;
		Status status = waitSt;
		while (next_pos != input.size()) {
			Lexema l = getLexema(input, pos, next_pos);
			switch (status) {
			case waitSt:
				if (l.type == number) status = numberSt;
				else if (l.type == bin_operator) status = errorSt;
				else if (l.type == function) status = funcSt;
				else if (l.type == leftBracket) status = leftBracketSt;
				else if (l.type == rightBracket) status = errorSt;
				else if (l.type == un_minus && next_pos!=input.size()) status = unMinSt;
				else if (pos == input.size()) break;
				else status = errorSt;
				break;
			case numberSt:
				if (l.type == number) status = errorSt;
				else if (l.type == bin_operator) status = binOperatorSt;
				else if (l.type == function) status = errorSt;
				else if (l.type == leftBracket) status = errorSt;
				else if (l.type == rightBracket) status = rightBracketSt;
				else if (l.type == un_minus) status = errorSt;
				else if (next_pos == input.size()) break;
				break;
			case binOperatorSt:
				if (l.type == number) status = numberSt;
				else if (l.type == bin_operator) status = errorSt;
				else if (l.type == function) status = funcSt;
				else if (l.type == leftBracket) status = leftBracketSt;
				else if (l.type == rightBracket) status = errorSt;
				else if (l.type == un_minus) status = errorSt;
				else if (next_pos == input.size()) status = errorSt;
				break;
			case funcSt:
				if (l.type == number) status = numberSt;
				else if (l.type == bin_operator) status = errorSt;
				else if (l.type == function) status = funcSt;
				else if (l.type == leftBracket) status = leftBracketSt;
				else if (l.type == rightBracket) status = errorSt;
				else if (l.type == un_minus) status = unMinSt;
				else if (next_pos == input.size()) status == errorSt;
				break;
			case leftBracketSt:
				if (l.type == number) status = numberSt;
				else if (l.type == bin_operator) status = errorSt;
				else if (l.type == function) status = funcSt;
				else if (l.type == leftBracket) status = leftBracketSt;
				else if (l.type == rightBracket) status = errorSt;
				else if (l.type == un_minus) status = unMinSt;
				else if (next_pos == input.size()) status == errorSt;
				break;
			case rightBracketSt:
				if (l.type == number) status = errorSt;
				else if (l.type == bin_operator) status = binOperatorSt;
				else if (l.type == function) status = errorSt;
				else if (l.type == leftBracket) status = errorSt;
				else if (l.type == rightBracket) status = rightBracketSt;
				else if (l.type == un_minus) status = errorSt;
				else if (next_pos == input.size()) break;
				break;
			case unMinSt:
				if (l.type == number) status = numberSt;
				else if (l.type == bin_operator) status = errorSt;
				else if (l.type == function) status = funcSt;
				else if (l.type == leftBracket) status = leftBracketSt;
				else if (l.type == rightBracket) status = errorSt;
				else if (l.type == un_minus) status = errorSt;
				else if (next_pos == input.size()) status = errorSt;
				break;
			}
			if (status == errorSt) {
				throw(1);
				return;
			}
			pos = next_pos;
			lexems.push_back(l);
		}
	}
	void toPostfix() {
		parse(infix);
		stack <Lexema> st;
		TypeLexeme checkType;
		Lexema stackItem;
		stack <Lexema> postfixReversed;
		for (int i = 0; i < lexems.size(); i++) {
			checkType = lexems[i].type;
			switch (checkType) {
			case leftBracket:
				st.push(lexems[i]);
				break;
			case rightBracket:
				stackItem = st.top();
				st.pop();
				while (stackItem.name != "(") {
					postfixReversed.push(stackItem);
					stackItem = st.top();
					st.pop();
				}
				break;
			case number:
				postfixReversed.push(lexems[i]);
				break;
			case function:
				st.push(lexems[i]);
				break;
			case un_minus:
				st.push(lexems[i]);
				break;
			case bin_operator:
				while (!st.empty()) {
					stackItem = st.top();
					st.pop();
					if (( priority[lexems[i].name[0]] <= priority[stackItem.name[0]]) ||
						(stackItem.type == function))
						postfixReversed.push(stackItem);
					else {
						st.push(stackItem);
						break;
					}
				}
				st.push(lexems[i]);
				break;
			}
		}
		while (!st.empty()) {
			stackItem = st.top();
			st.pop();
			postfixReversed.push(stackItem);
		}
		vector<Lexema> v;
		while (!postfixReversed.empty()) {
			postfix.push(postfixReversed.top());
			v.push_back(postfixReversed.top());
			postfixReversed.pop();
		}
		postfixString = toString(v);
	}
	//перевод в строку
	string toString(vector<Lexema> v) {
		string str = "";
		while(!v.empty()){
			if (v.back().type == number)
				str += to_string(v.back().value);
			else
				str += v.back().name;
			v.pop_back();
		}
		return str;
	}
	arithmeticExpr(string infx) : infix(infx) {
		priority = { {'+',1},{'-',1}, {'/',2},{'*',2} };
		if (!bracketCheck(infix)) throw(1);
		toPostfix();
	}
	//вывод вектора лексем
	void print() {
		for (int i = 0; i < lexems.size(); i++)
			std::cout << lexems[i] << " ";
	}

	std::string getInfix() {
		return infix;
	}
	std::string getPostfix() {
		return postfixString;
	}
	double calculating(){
		double leftOperand, rightOperand;
		stack <double> st;
		Lexema stackItem;
		while (!postfix.empty()) {
			stackItem = postfix.top();
			postfix.pop();
			switch (stackItem.type) {
			case bin_operator:
				rightOperand = st.top();
				st.pop();
				leftOperand = st.top();
				st.pop();
				st.push(operatorCalculating(stackItem.name, rightOperand, leftOperand));
				break;
			case function:
				rightOperand = st.top();
				st.pop();
				st.push(functionCalculating(stackItem.name, rightOperand));
				break;
			case un_minus:
				rightOperand = st.top();
				st.pop();
				st.push(unOperator(rightOperand));
				break;
			case number:
				st.push(stackItem.value);
				break;
			}
		}
		return st.top();
	}
};
