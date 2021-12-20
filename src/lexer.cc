#include <cstdlib>
#include "lexer.hh"
#include "util.hh"

vector <Lexer::Token> Lexer::Tokenize(string source) {
	vector <Lexer::Token> tokens;
	string                reading;
	ATM_Integer           line = 1;
	ATM_Integer           column = 0;
	bool                  inString = false;
	for (ATM_Integer i = 0; i<source.length(); ++i) {
		++ column;
		switch (source[i]) {
			case ':': { // function token
				if (!inString) {
					tokens.push_back(Lexer::Token(Lexer::TokenType::Function, reading, line, column));
					reading = "";
				}
				else {
					reading += source[i];
				}
				break;
			}
			case ']':
			case ';': { // end of statement
				if ((tokens.size() == 0) || (tokens[tokens.size()-1].type == Lexer::TokenType::EndOfArguments)) {
					if (!inString) {
						tokens.push_back(Lexer::Token(Lexer::TokenType::Function, reading, line, column));
						reading = "";
					}
					else {
						reading += source[i];
					}
					tokens.push_back(Lexer::Token(Lexer::TokenType::EndOfArguments, "", line, column));
					break;
				}
				else if ((!inString) && (reading[0] == '"') && (reading[reading.length()-1] == '"')) {
					tokens.push_back(Lexer::Token(Lexer::TokenType::String, reading.substr(1, reading.length() - 2), line, column));
				}
				else if ((reading[0] == '\'') && (reading[reading.length()-1] == '\'')) {
					if (reading.length() == 3)
						tokens.push_back(Lexer::Token(Lexer::TokenType::Number, to_string((int)reading[1]), line, column));
					else {
						printf("Error: invalid character literal ('%s') at line %u Col %u\n", reading.c_str(), line, column);
						exit(1);
					}
				}
				else if (Util::IsNumber(reading)) {
					tokens.push_back(Lexer::Token(Lexer::TokenType::Number, reading, line, column));
				}
				else {
					switch (reading[0]) {
						case '@': {
							tokens.push_back(Lexer::Token(Lexer::TokenType::Pointer, reading.substr(1), line, column));
							break;
						}
						case '^': {
							tokens.push_back(Lexer::Token(Lexer::TokenType::Dereference, reading.substr(1), line, column));
							break;
						}
						default: {
							tokens.push_back(Lexer::Token(Lexer::TokenType::Identifier, reading, line, column));
						}
					}
				}
				tokens.push_back(Lexer::Token(Lexer::TokenType::EndOfArguments, "", line, column));
				reading = "";
				break;
			}
			case '[': { // start of keyword
				if (!inString) {
					tokens.push_back(Lexer::Token(Lexer::TokenType::Keyword, reading, line, column));
					reading = "";
				}
				break;
			}
			case ',': { // argument separator
				if (inString) {
					reading += source[i];
					break;
				}
				if ((reading[0] == '"') && (reading[reading.length()-1] == '"')) {
					tokens.push_back(Lexer::Token(Lexer::TokenType::String, reading.substr(1, reading.length() - 2), line, column));
					reading = "";
				}
				else if ((reading[0] == '\'') && (reading[reading.length()-1] == '\'')) {
					if (reading.length() == 3)
						tokens.push_back(Lexer::Token(Lexer::TokenType::Number, to_string((int)reading[1]), line, column));
					else {
						printf("Error: invalid character literal ('%s') at line %u Col %u\n", reading.c_str(), line, column);
						exit(1);
					}
				}
				else if (Util::IsNumber(reading)) {
					tokens.push_back(Lexer::Token(Lexer::TokenType::Number, reading, line, column));
				}
				else {
					switch (reading[0]) {
						case '@': {
							tokens.push_back(Lexer::Token(Lexer::TokenType::Pointer, reading.substr(1), line, column));
							break;
						}
						case '^': {
							tokens.push_back(Lexer::Token(Lexer::TokenType::Dereference, reading.substr(1), line, column));
							break;
						}
						default: {
							tokens.push_back(Lexer::Token(Lexer::TokenType::Identifier, reading, line, column));
						}
					}
				}
				break;
			}
			case '"': {// string
				inString = !inString;
				reading += source[i];
				break;
			}
			case '\\': { // string escape
				if (inString) {
					++ i;
					switch (source[i]) {
						case 'n': {
							reading += '\n';
							break;
						}
						case 't': {
							reading += '\t';
							break;
						}
						case 'r': {
							reading += '\r';
							break;
						}
						case 'e': {
							reading += '\x1b';
							break;
						}
						case '\\': {
							reading += '\\';
							break;
						}
						case '\'': {
							reading += '\'';
							break;
						}
						case '"': {
							reading += '"';
							break;
						}
						default: {
							printf("Error: invalid escape sequence '\\%c' at line %u Col %u\n", source[i], line, column);
							exit(1);
						}
					}
				}
				break;
			}
			case '\n': { // new line
				++ line;
				column = 0;
				break;
			}
			case '\t':  // tab
			case ' ': { // space
				if (inString) {
					reading += source[i];
				}
				break;
			}
			case '/': { // comment
				if (!inString)
				switch (source[i+1]) {
					case '/': { // single line comment
						while (source[i] != '\n') {
							++i;
						}
						break;
					}
					case '*': { // multi line comment
						while (source[i] != '*' || source[i+1] != '/') {
							++i;
						}
						break;
					}
				}
				else {
					reading += source[i];
				}
				break;
			}
			case '=': { // operator
				Lexer::Token token(Lexer::TokenType::Operator, reading, line, column);
				token.extrach = source[i];
				tokens.push_back(token);
				reading = "";
				break;
			}
			default: {
				reading += source[i];
			}
		}
	}
	return tokens;
}

string Lexer::ToString(Lexer::TokenType type) {
	switch (type) {
		case Lexer::TokenType::Function: return "Function";
		case Lexer::TokenType::Keyword:  return "Keyword";
		case Lexer::TokenType::String:   return "String";
		case Lexer::TokenType::Number:   return "Number";
		case Lexer::TokenType::Identifier: return "Identifier";
		case Lexer::TokenType::EndOfArguments: return "EndOfArguments";
		case Lexer::TokenType::EndOfFile: return "EndOfFile";
		case Lexer::TokenType::Pointer: return "Pointer";
		case Lexer::TokenType::Dereference: return "Dereference";
		case Lexer::TokenType::Operator: return "Operator";
	}
	return ""; // this will literally not happen but gcc think it will so its here to make it happy
}