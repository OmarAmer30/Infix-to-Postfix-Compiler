#include <iostream>
#include <fstream>

using namespace std;

ifstream input("D:/My College/Level 3/Semester 2/Comp 304/Code/input.txt");
ofstream output("D:/My College/Level 3/Semester 2/Comp 304/Code/output.txt");

enum Tokens {
	NUM = 256,
	ID = 257,
	DIV = 258,
	MOD = 259,
	DONE = 300,
	NONE = -1
};

int lookahead;
int tokenval;
string st;
int linenum = 1;

int lexan() {
	int t;
	while (true) {
		t = input.get();
		if (t == ' ' || t == '\t') continue;
		if (t == '\n') {
			linenum++;
			continue;
		}

		if (isdigit(t)) {
			input.unget();
			input >> tokenval;
			return NUM;
		}

		if (isalpha(t)) {
			char buffer[20];
			int i = 0;

			buffer[i++] = t;
			while (isalnum(t = input.get()))
				buffer[i++] = t;
			buffer[i] = '\0';

			input.unget();
			st = string(buffer);

			tokenval = t;

			if (st == "div" || st == "DIV") return DIV;
			if (st == "mod" || st == "MOD") return MOD;

			return ID;
		}
		if (t == EOF) return DONE;

		return t;
	}
}

void error() {
	cout << "Error in line number " << linenum << endl;
	output << "Error in line number " << linenum << endl;
	exit(1);
}

void emit(int t, int value) {
	switch (t)
	{
	case '+':
	case '-':
	case '*':
	case '/':
		output << (char)t << ' ';
		break;
	case NUM:
		output << "NUM(" << value << ") ";
		break;
	case ID:
		output << "ID(" << st << ") ";
		break;
	case DIV:
		output << "DIV ";
		break;
	case MOD:
		output << "MOD ";
		break;
	}
}

void match(int t) {
	if (t == lookahead)
		lookahead = lexan();
	else error();
}

void expr();
void factor() {
	if (lookahead == '(') {
		match('(');
		expr();
		match(')');
	}
	else if (lookahead == NUM) {
		emit(NUM, tokenval);
		match(NUM);
	}
	else if (lookahead == ID) {
		emit(ID, 0);
		match(ID);
	}
	else error();
}

void term() {
	factor();
	while (1) {
		if (lookahead == '*') {
			match('*');
			factor();
			emit('*', NULL);
		}
		else if (lookahead == '/') {
			match('/');
			factor();
			emit('/', NULL);
		}
		else if (lookahead == DIV) {
			match(DIV);
			factor();
			emit(DIV, NULL);
		}
		else if (lookahead == MOD) {
			match(MOD);
			factor();
			emit(MOD, NULL);
		}
		else break;
	}
}

void expr() {
	term();
	while (1) {
		if (lookahead == '+') {
			match('+');
			term();
			emit('+', NULL);
		}
		else if (lookahead == '-') {
			match('-');
			term();
			emit('-', NULL);
		}
		else break;
	}
}

int main() {
	lookahead = lexan();

	expr();

	if (lookahead != DONE)
		error();

	return 0;
}