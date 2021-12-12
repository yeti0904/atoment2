#include "_components.hh"
#include "atoment.hh"
#include "lexer.hh"
#include "keywords.hh"

ATM::Arglist createArguments(size_t &i, vector <Lexer::Token> &tokens, ATM::Language_Components &atm) {
	ATM::Arglist arglist;
	size_t j = i + 1;
	for (; tokens[j].type != Lexer::TokenType::EndOfArguments; ++j) {
		switch (tokens[j].type) {
			case Lexer::TokenType::Number: {
				try {
					arglist.push_back(stoi(tokens[j].value));
				}
				catch (const std::invalid_argument& ia) {
					printf("Invalid argument at line %ld col %ld\n", tokens[j].line, tokens[j].column);
					exit(1);
				}
				break;
			}
			case Lexer::TokenType::String: {
				arglist.push_back(tokens[j].value);
				break;
			}
			case Lexer::TokenType::Identifier: {
				arglist.push_back(atm.variables[tokens[j].value]);
				break;
			}
			case Lexer::TokenType::Pointer: {
				try {
					arglist.push_back(ATM_Pointer(atm.variables[tokens[j].value]));
				}
				catch (const std::invalid_argument& ia) {
					printf("Invalid argument at line %ld col %ld\n", tokens[j].line, tokens[j].column);
					exit(1);
				}
				break;
			}
			case Lexer::TokenType::Dereference: {
				try {
					arglist.push_back(atm.stack[atm.variables[tokens[j].value]]);
				}
				catch (const std::invalid_argument& ia) {
					printf("Invalid argument at line %ld col %ld\n", tokens[j].line, tokens[j].column);
					exit(1);
				}
				break;
			}
			default: {
				printf("Error: unexpected token %d in arguments list (index %ld) at line %ld col %ld\n", (int)tokens[i].type, j, tokens[j].line, tokens[j].column);
			}
		}
	}
	i = j;
	return arglist;
}

void interpretTokens(vector <Lexer::Token> tokens, ATM::Language_Components& atm) {
	for (size_t i = 0; i<tokens.size(); ++i) {
		atm.variables["MEM_SIZE"] = atm.stack.size();
		switch (tokens[i].type) {
			case Lexer::TokenType::Function: {
				if (atm.functions[tokens[i].value] == nullptr) {
					printf("Function %s not found at line %ld col %ld\n", tokens[i].value.c_str(), tokens[i].line, tokens[i].column);
					exit(1);
				}
				string function = tokens[i].value; // save it because we modify i later

				// create arguments vector
				ATM::Arglist arglist = createArguments(i, tokens, atm);
				
				// call function
				atm.functions[function](atm, arglist);
				break;
			}
			case Lexer::TokenType::Keyword: {
				Lexer::Token keyword = tokens[i];
				ATM::Arglist arglist = createArguments(i, tokens, atm);
				if (keyword.value == "def") {
					keyword_def(atm, arglist);
				}
				else if (keyword.value == "delete") {
					keyword_delete(atm, arglist);
				}
				break;
			}
			default: {
				printf("Error: Unexpected token %d at line %ld col %ld\n", (int)tokens[i].type, tokens[i].line, tokens[i].column);
				exit(1);
			}
		}
	}
}
