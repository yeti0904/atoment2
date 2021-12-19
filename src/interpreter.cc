#include "_components.hh"
#include "atoment.hh"
#include "lexer.hh"
#include "keywords.hh"
#include "util.hh"
#include "operators.hh"

ATM::Arglist createArguments(uint32_t &i, vector <Lexer::Token> &tokens, ATM::Language_Components &atm) {
	ATM::Arglist arglist;
	uint32_t j = i + 1;
	for (; tokens[j].type != Lexer::TokenType::EndOfArguments; ++j) {
		if (tokens[j].value.length() > 0)
		switch (tokens[j].type) {
			case Lexer::TokenType::Number: {
				try {
					arglist.push_back(stoi(tokens[j].value));
				}
				catch (const std::invalid_argument& ia) {
					printf("Invalid argument at line %d col %d\n", (int)tokens[j].line, (int)tokens[j].column);
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
					printf("Invalid argument at line %d col %d\n", (int)tokens[j].line, (int)tokens[j].column);
					exit(1);
				}
				break;
			}
			case Lexer::TokenType::Dereference: {
				try {
					arglist.push_back(atm.stack[atm.variables[tokens[j].value]]);
				}
				catch (const std::invalid_argument& ia) {
					printf("Invalid argument at line %d col %d\n", (int)tokens[j].line, (int)tokens[j].column);
					exit(1);
				}
				break;
			}
			case Lexer::TokenType::Operator: {
				arglist.push_back(tokens[j].value);
				break;
			}
			default: {
				printf("Error: unexpected token '%s' in arguments list (index %d) at line %d col %d\n", Lexer::ToString(tokens[j].type).c_str(), j, (int)tokens[j].line, (int)tokens[j].column);
			}
		}
	}
	/*printf("Logging arguments for call %s\n", tokens[i].value.c_str());
	Util::logArguments(arglist);*/
	i = j;
	return arglist;
}

void interpretTokens(vector <Lexer::Token> tokens, ATM::Language_Components& atm) {
	for (uint32_t i = 0; i<tokens.size(); ++i) {
		atm.variables["MEM_SIZE"] = atm.stack.size();
		switch (tokens[i].type) {
			case Lexer::TokenType::Function: {
				if (atm.functions[tokens[i].value] == nullptr) {
					printf("Function %s not found at line %d col %d\n", tokens[i].value.c_str(), (int)tokens[i].line, (int)tokens[i].column);
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
				if (keyword.value == "let") {
					keyword_let(atm, arglist);
				}
				else if (keyword.value == "delete") {
					keyword_delete(atm, arglist);
				}
				break;
			}
			case Lexer::TokenType::Operator: {
				switch (tokens[i].extrach) {
					case '=': {
						ATM_Integer ti = i - 1; // temp i
						Operators::Equal(atm, createArguments(ti, tokens, atm));
						i = ti;
						break;
					}
				}
				break;
			}
			default: {
				printf("Error: Unexpected token %d at line %d col %d\n", (int)tokens[i].type, (int)tokens[i].line, (int)tokens[i].column);
				exit(1);
			}
		}
	}
}
