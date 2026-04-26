#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

ifstream input("./input.txt");
ofstream output("./output.txt");

enum Tokens {
	NUM = 256,
	ID = 257,
	DIV = 258,
	MOD = 259,
	DONE = 300,
	NONE = -1,
};

#define STRMAX 999
#define SYMMAX 100

int lookahead;
int tokenval;
int linenum = 1;

struct Entry {
	const char *lexptr;
	int token;
};

char lexems[STRMAX];
int lastchar = -1;

Entry symtable[SYMMAX];
int lastindex = 0;

Entry keywords[] = {
	{"div", DIV},
	{"mod", MOD},
	{0, 0}
};

int lookup(const char s[]) {
	for (int p = lastindex; p > 0; p--)
		if (strcmp(symtable[p].lexptr, s) == 0)
			return p;
	return 0;	
}

int insert(const char s[], int tok) {
	int length = strlen(s);

	if (lastindex + 1 >= SYMMAX) { cout << "symbol table full\n";  exit(1); }
	if (lastchar + length + 1 >= STRMAX) { cout << "lexemes array full\n"; exit(1); }

	lastindex++;
	symtable[lastindex].lexptr = &lexems[lastchar + 1];
	symtable[lastindex].token = tok;
	lastchar = lastchar + length + 1;
	strcpy((char*)symtable[lastindex].lexptr, s);

	return lastindex;
}

void init() {
	for (Entry* p = keywords; p->token; p++)
		insert((char *)p->lexptr, p->token);
}

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
			char buffer[128];
			int i = 0;

			buffer[i++] = t;
			while (isalnum(t = input.get()))
				buffer[i++] = t;
			buffer[i] = '\0';

			input.unget();

			int p = lookup(buffer);
			if (p == 0) p = insert(buffer, ID);
			tokenval = p;
			return symtable[p].token;
		}
		if (t == EOF) return DONE;

		tokenval = NONE;
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
		output << "ID(" << symtable[value].lexptr << ") ";
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
		emit(ID, tokenval);
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
			emit('*', 0);
		}
		else if (lookahead == '/') {
			match('/');
			factor();
			emit('/', 0);
		}
		else if (lookahead == DIV) {
			match(DIV);
			factor();
			emit(DIV, 0);
		}
		else if (lookahead == MOD) {
			match(MOD);
			factor();
			emit(MOD, 0);
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
			emit('+', 0);
		}
		else if (lookahead == '-') {
			match('-');
			term();
			emit('-', 0);
		}
		else break;
	}
}

void parse() {
	lookahead = lexan();
	while (lookahead != DONE) {
		expr();
		match(';');
		output << '\n';
	}
}

int main() {
	init();
	parse();
	return 0;
}