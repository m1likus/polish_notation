#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <stdio.h>
#include <iostream>
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
	string postfix;
	vector<Lexema> lexems;
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
			pos = next_pos;
			switch (status) {
			case waitSt:
				if (l.type == number) status = numberSt;
				else if (l.type == bin_operator) status = errorSt;
				else if (l.type == function) status = funcSt;
				else if (l.type == leftBracket) status = leftBracketSt;
				else if (l.type == rightBracket) status = errorSt;
				else if (l.type == un_minus) status = unMinSt;
				else if (next_pos == input.size()) break;
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
				throw("Error Status");
				return;
			}
			lexems.push_back(l);
		}
	}
	void toPostfix() {
		//parsing();

	}
	arithmeticExpr(string infx) : infix(infx) {
		priority = { {'+',1},{'-',1}, {'/',2},{'*',2},
			{'sin',2},{'cos',2}, {'tg',2},{'ctg',2},{'(',0}};
		//toPostfix();
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
		return postfix;	
	}
	double calculating(){

	}
};


//void parsing() {
	//	//infix += "?";
	//	set <char> operations = { '+','-','/','*','(', ')' };
	//	set <char> numbers = { '0','1','2','3','4','5','6','7','8','9' };
	//	set <char> func = { 's','i','n','c','o','t','g' };
	//	string sin = "sin", cos = "cos", tg = "tg", ctg = "ctg";
	//	string lexema = "";
	//	for (int i = 0; i < infix.size(); i++) {
	//		char l = infix[i];
	//		if (operations.count(l)) {
	//			//äâà âàðèàíòà ðàçâèòèÿ ñîáûòèé: ñòðîêà ïóñòàÿ è ñòðîêà íå ïóñòàÿ
	//			//åñëè ñòðîêà íå ïóñòàÿ,òî íàäî ñíà÷àëà îïðåäåëèòü, ÷òî â íåé áûëî.
	//			//åñëè ýòî íå ÷èñëî è íå ôóíêöèÿ èç ðàçðåøåííûõ
	//			//òî âîçíèêàþò âîïðîñû êòî ýòî òàêîé, à çíà÷èò âûáðàñûâàåì îøèáî÷êó.
	//			if (!lexema.empty()) {
	//				if (lexema != sin && lexema != cos && lexema != tg && lexema != ctg
	//					&& numbers.count(lexema.back()) == 0)
	//					throw("wrong expression, bye-bye");
	//				//òåïåðü, çíàÿ, ÷òî ìû íè÷åãî ëèøíåãî â ëåêñåìû íå âáðîñèì
	//				//êèäàåì òóäà ñíà÷àëà òî, ÷òî áûëî äî îïåðàòîðà â ëåêñåìå
	//				lexems.push_back(lexema);
	//				lexema = "";
	//			}
	//			lexema += l;
	//			lexems.push_back(lexema);
	//			lexema = "";
	//		}
	//		if (numbers.count(l)) {
	//			//àíàëîãè÷íî, ñòðîêà ì.á. ïóñòîé è íå ïóñòîé.
	//			//åñëè íå ïóñòàÿ, òî òàì ëèáî ÷èñëî, ëèáî ôóíêöèÿ
	//			//ëèáî ÷òî-òî, ÷òî ìû ìîæåì âûáðîñèòü â îøèáêó)
	//			//îïåðàòîðà òàì áûòü íå ìîæåò, â ïðîøëîì if î÷èùàåòñÿ ñðàçó æå
	//			if (!lexema.empty()) {
	//				if (lexema == sin || lexema == cos || lexema == tg
	//					|| lexema == ctg) {
	//					lexems.push_back(lexema);
	//					lexema = "";
	//				}
	//				else if (numbers.count(lexema.back())); //åñëè áûëî ÷èñëî, òî âñå îê, ïðîäîëæàåì
	//				else throw ("wrong expression, bye-bye");
	//			}
	//			lexema += l;
	//		}
	//		if (func.count(l)) {
	//			//åñëè íå ïóñòàÿ ñòðîêà äî,òî ÷òî òàì ìîæåò áûòü?
	//			//åñëè ÷èñëî, î÷èùàåì
	//			//åñëè ôóíêöèÿ = òîãäà îíà òî÷íî íåïîëíàÿ, ïîòîìó ÷òî ñåé÷àñ òîæå
	//			//äîáàâëÿåì áóêâó îò ôóíêöèè
	//			if (!lexema.empty()){
	//				if (numbers.count(lexema.back())){ // êîíåö òî÷íî ÷èñëî
	//					lexems.push_back(lexema);
	//					lexema = "";
	//				}
	//				else if (lexema == "s" || lexema == "si" || lexema == "c"
	//					|| lexema == "co" || lexema == "t" || lexema == "ct") {
	//					lexems.push_back(lexema);
	//					lexema = "";
	//				}
	//				//ïîëíîé ëåêñåìû òàì òî÷íî íå ì.á. ò.ê. òîãäà ýòî íåâåðíîå âûðàæåíèå
	//				else throw ("wrong expression, bye-bye");
	//			}
	//			lexema += l;
	//		}
	//	}
	//}
