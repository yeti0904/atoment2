#include <cstdlib>
#include "lexer.hh"
#include "util.hh"

vector <Lexer::Token> Lexer::tokenize(string source) {
	vector <Lexer::Token> tokens;
	string                reading;
	size_t                line = 1;
	size_t                column = 0;
	bool                  inString = false;
	for (size_t i = 0; i<source.length(); ++i) {
		++ column;
		switch (source[i]) {
			case ':': { // function token
				tokens.push_back(Lexer::Token(Lexer::TokenType::Function, reading, line, column));
				reading = "";
				break;
			}
			case ']':
			case ';': { // end of statement
				if ((reading[0] == '"') && (reading[reading.length()-1] == '"')) {
					tokens.push_back(Lexer::Token(Lexer::TokenType::String, reading, line, column));
				}
				else if ((reading[0] == '\'') && (reading[reading.length()-1] == '\'')) {
					if (reading.length() == 3)
						tokens.push_back(Lexer::Token(Lexer::TokenType::Number, to_string((int)reading[1]), line, column));
					else {
						printf("Error: invalid character literal ('%s') at line %lu Col %lu\n", reading.c_str(), line, column);
						exit(1);
					}
				}
				else if (Util::IsNumber(reading)) {
					tokens.push_back(Lexer::Token(Lexer::TokenType::Number, reading, line, column));
				}
				else {
					tokens.push_back(Lexer::Token(Lexer::TokenType::Identifier, reading, line, column));
				}
				tokens.push_back(Lexer::Token(Lexer::TokenType::EndOfArguments, "", line, column));
				reading = "";
				break;
			}
			case '[': { // start of keyword
				tokens.push_back(Lexer::Token(Lexer::TokenType::Keyword, reading, line, column));
				reading = "";
				break;
			}
			case ',': { // argument separator
				if ((reading[0] == '"') && (reading[reading.length()-1] == '"')) {
					tokens.push_back(Lexer::Token(Lexer::TokenType::String, reading, line, column));
				}
				else if ((reading[0] == '\'') && (reading[reading.length()-1] == '\'')) {
					if (reading.length() == 3)
						tokens.push_back(Lexer::Token(Lexer::TokenType::Number, to_string((int)reading[1]), line, column));
					else {
						printf("Error: invalid character literal ('%s') at line %lu Col %lu\n", reading.c_str(), line, column);
						exit(1);
					}
				}
				else if (Util::IsNumber(reading)) {
					tokens.push_back(Lexer::Token(Lexer::TokenType::Number, reading, line, column));
				}
				else {
					tokens.push_back(Lexer::Token(Lexer::TokenType::Identifier, reading, line, column));
				}
				break;
			}
			case '"': {// string
				inString = !inString;
				reading += source[i];
				break;
			}
			case '\n': { // new line
				++ line;
				column = 0;
				break;
			}
			case ' ': {
				if (inString) {
					reading += source[i];
				}
				break;
			}
			case '/': { // comment
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
				break;
			}
			default: {
				reading += source[i];
			}
		}
	}
	return tokens;
}