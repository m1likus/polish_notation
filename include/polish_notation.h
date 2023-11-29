#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;
bool isDigit(char c) {
	return (c >= '0' && c <= '9');
}

enum TypeLexeme {
	number,
	bin_operator
};

struct Lexema {
	int value = 0;
	TypeLexeme type = TypeLexeme::number;
	string s;
};

enum Status {
	waitSt,
	numberSt,
	binOperatorSt
};

vector<Lexema> lexemas;

Lexema getLexema(string input, int pos, int& nextPos) {
	Lexema lexeme;
	if (isDigit) {
		int value = input[pos] - '0';
		pos++;
		nextPos++;
		while (input[pos]) {
			value *= 10;
			value += input[pos] - '0';
			pos++;
			nextPos++;
		}
		lexeme.value = value;
		lexeme.type = number;
	}
	
	return lexeme;
}

vector<Lexema> parse(string input) {
	Status status = waitSt;
	int pos = 0, next_pos = 0;
	vector<Lexema> v;
	while (next_pos != input.size()) {
		Lexema l = getLexema(input, pos, next_pos);
		if (status == waitSt) {

		}
		else if (status == numberSt) {

		}
		else if (status == binOperatorSt) {

		}
	}
	return v;
}

class arithmeticExpr {
	string infix;
	string postfix;
	vector<string> lexems;
	map <char, int> priority;
	//map <char, double> operands;

	
	void toPostfix() {
		//parsing();
	
	}
public:
	arithmeticExpr(string infx) : infix(infx) {
		priority = { {'+',1},{'-',1}, {'/',2},{'*',2},
			{'sin',2},{'cos',2}, {'tg',2},{'ctg',2},{'(',0}};
		toPostfix();
	}


	std::string getInfix() {
		return infix;
	}
	std::string getPostfix() {
		return postfix;	
	}

	//double calculating(const map<char, double>& values) {
	double calculating(){

	}
};

bool bracketCheck(string str) {
	int lb = 0, rb = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '(') lb++;
		else if (str[i] == ')') rb++;
	}
	if (lb == rb) return true;
	return false;
}


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
	//			//два варианта развития событий: строка пустая и строка не пустая
	//			//если строка не пустая,то надо сначала определить, что в ней было.
	//			//если это не число и не функция из разрешенных
	//			//то возникают вопросы кто это такой, а значит выбрасываем ошибочку.
	//			if (!lexema.empty()) {
	//				if (lexema != sin && lexema != cos && lexema != tg && lexema != ctg
	//					&& numbers.count(lexema.back()) == 0)
	//					throw("wrong expression, bye-bye");
	//				//теперь, зная, что мы ничего лишнего в лексемы не вбросим
	//				//кидаем туда сначала то, что было до оператора в лексеме
	//				lexems.push_back(lexema);
	//				lexema = "";
	//			}
	//			//а теперь можем и с нынешней лексемой разобраться, ура
	//			lexema += l;
	//			lexems.push_back(lexema);
	//			lexema = "";
	//		}
	//		if (numbers.count(l)) {
	//			//аналогично, строка м.б. пустой и не пустой.
	//			//если не пустая, то там либо число, либо функция
	//			//либо что-то, что мы можем выбросить в ошибку)
	//			//оператора там быть не может, в прошлом if очищается сразу же
	//			if (!lexema.empty()) {
	//				if (lexema == sin || lexema == cos || lexema == tg
	//					|| lexema == ctg) {
	//					lexems.push_back(lexema);
	//					lexema = "";
	//				}
	//				else if (numbers.count(lexema.back())); //если было число, то все ок, продолжаем
	//				else throw ("wrong expression, bye-bye");
	//			}
	//			lexema += l;
	//		}
	//		if (func.count(l)) {
	//			//если не пустая строка до,то что там может быть?
	//			//если число, очищаем
	//			//если функция = тогда она точно неполная, потому что сейчас тоже
	//			//добавляем букву от функции
	//			if (!lexema.empty()){
	//				if (numbers.count(lexema.back())){ // конец точно число
	//					lexems.push_back(lexema);
	//					lexema = "";
	//				}
	//				else if (lexema == "s" || lexema == "si" || lexema == "c"
	//					|| lexema == "co" || lexema == "t" || lexema == "ct") {
	//					lexems.push_back(lexema);
	//					lexema = "";
	//				}
	//				//полной лексемы там точно не м.б. т.к. тогда это неверное выражение
	//				else throw ("wrong expression, bye-bye");
	//			}
	//			lexema += l;
	//		}
	//	}
	//}
