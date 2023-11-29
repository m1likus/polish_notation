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
	//			//��� �������� �������� �������: ������ ������ � ������ �� ������
	//			//���� ������ �� ������,�� ���� ������� ����������, ��� � ��� ����.
	//			//���� ��� �� ����� � �� ������� �� �����������
	//			//�� ��������� ������� ��� ��� �����, � ������ ����������� ��������.
	//			if (!lexema.empty()) {
	//				if (lexema != sin && lexema != cos && lexema != tg && lexema != ctg
	//					&& numbers.count(lexema.back()) == 0)
	//					throw("wrong expression, bye-bye");
	//				//������, ����, ��� �� ������ ������� � ������� �� �������
	//				//������ ���� ������� ��, ��� ���� �� ��������� � �������
	//				lexems.push_back(lexema);
	//				lexema = "";
	//			}
	//			//� ������ ����� � � �������� �������� �����������, ���
	//			lexema += l;
	//			lexems.push_back(lexema);
	//			lexema = "";
	//		}
	//		if (numbers.count(l)) {
	//			//����������, ������ �.�. ������ � �� ������.
	//			//���� �� ������, �� ��� ���� �����, ���� �������
	//			//���� ���-��, ��� �� ����� ��������� � ������)
	//			//��������� ��� ���� �� �����, � ������� if ��������� ����� ��
	//			if (!lexema.empty()) {
	//				if (lexema == sin || lexema == cos || lexema == tg
	//					|| lexema == ctg) {
	//					lexems.push_back(lexema);
	//					lexema = "";
	//				}
	//				else if (numbers.count(lexema.back())); //���� ���� �����, �� ��� ��, ����������
	//				else throw ("wrong expression, bye-bye");
	//			}
	//			lexema += l;
	//		}
	//		if (func.count(l)) {
	//			//���� �� ������ ������ ��,�� ��� ��� ����� ����?
	//			//���� �����, �������
	//			//���� ������� = ����� ��� ����� ��������, ������ ��� ������ ����
	//			//��������� ����� �� �������
	//			if (!lexema.empty()){
	//				if (numbers.count(lexema.back())){ // ����� ����� �����
	//					lexems.push_back(lexema);
	//					lexema = "";
	//				}
	//				else if (lexema == "s" || lexema == "si" || lexema == "c"
	//					|| lexema == "co" || lexema == "t" || lexema == "ct") {
	//					lexems.push_back(lexema);
	//					lexema = "";
	//				}
	//				//������ ������� ��� ����� �� �.�. �.�. ����� ��� �������� ���������
	//				else throw ("wrong expression, bye-bye");
	//			}
	//			lexema += l;
	//		}
	//	}
	//}
