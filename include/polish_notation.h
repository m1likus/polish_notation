#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>

/*
currentStatus 				lexemeType 			nextStatus
waitSt						number				numberSt
waitSt						bin_operator			errorSt
waitSt						function			funcSt
waitSt						end				end
numberSt					number				errorSt
numberSt 					bin_operator			binOperatorSt
numberSt					function			errorSt
numberSt					end				end
binOperatorSt					number				numberSt
binOperatorSt					bin_operator			errorSt
binOperatorSt					function			funcSt
binOperatorSt					end				errorSt
funcSt						number				numberSt
funcSt						bin_operator			errorSt
funcSt						function			funcSt
funcSt						end				errorSt
*/
using namespace std;
bool isDigit(char c) {
	return (c >= '0' && c <= '9');
}

enum TypeLexeme {
	number,
	bin_operator,
	function
};

struct Lexema {
	int value = 0;
	TypeLexeme type = TypeLexeme::number;
	string name;
};

enum Status {
	waitSt,
	numberSt,
	binOperatorSt,
	errorSt,
	funcSt
};

vector<Lexema> lexemas;

Lexema getLexema(string input, int pos, int& nextPos) {
	Lexema lexeme;
	//if the symbols is number we start searching
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
	// if the symbol is a binary operator
	if (input[pos]=="+" ||  input[pos]=="-" || input[pos]=="*" || input[pos]=="/"){
		nextPos++;
		lexeme.type = bin_opeartor;
		lexeme.name = input[pos];
	}
	//if there's function
	
	return lexeme;
}

vector<Lexema> parse(string input) {
	Status status = waitSt;
	int pos = 0, next_pos = 0;
	vector<Lexema> v;
	while (next_pos != input.size()) {
		Lexema l = getLexema(input, pos, next_pos);
	switch(status):
		case waitSt:
			if (l.type == number) status = numberSt;
			else if (l.type==bin_operator) status = errorSt;
			else if(l.type == function) status = funcSt;
			else if(next_pos==input.size()) break;
		case numberSt:
			if (l.type == number) status = errorSt;
			else if (l.type==bin_operator) status = binOperatorSt;
			else if(l.type == function) status = errorSt;
			else if(next_pos==input.size()) break;
		case binOperatorSt:
			if (l.type == number) status = numberSt;
			else if (l.type==bin_operator) status = errorSt;
			else if(l.type == function) status = funcSt;
			else if(next_pos==input.size()) status=errorSt;
		case funcSt:
			if (l.type == number) status = numberSt;
			else if (l.type==bin_operator) status = errorSt;
			else if(l.type == function) status = funcSt;
			else if(next_pos==input.size()) status==errorSt;
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
	//			//à òåïåðü ìîæåì è ñ íûíåøíåé ëåêñåìîé ðàçîáðàòüñÿ, óðà
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
