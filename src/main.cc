#include <cstdio>
#include <cstddef>
#include "_components.hh"
#include "fs.hh"
#include "lexer.hh"
#include "interpreter.hh"
#include "atoment.hh"

int main(int argc, char** argv) {
	// convert argv into string vector
	vector <string> args;
	for (int i = 0; i<argc; ++i) {
		args.push_back(argv[i]);
	}

	if (args.size() < 2) {
		printf("Usage: %s [program path]\n", argv[0]);
		return 0;
	}

	// settings
	bool lexerDebug = false;
	bool showStack  = false;

	string programpath;
	// loop through args
	for (size_t i = 1; i<args.size(); ++i) {
		// if arg is a file
		if (args[i][0] != '-') {
			programpath = args[i];
		}
		else {
			if (args[i] == "--lexer-debug") {
				lexerDebug = true;
			}
			else if (args[i] == "--show-stack") {
				showStack = true;
			}
		}
	}

	if (programpath.empty()) {
		printf("Didn't give file argument\n");
		return 1;
	}
	
	if (!FS::Exists(programpath)) {
		printf("Non-existant file: %s\n", programpath.c_str());
		return 1;
	}

	// read file from programpath
	string file = FS::ReadFile(programpath);
	
	// lex the source code
	vector <Lexer::Token> tokens = Lexer::tokenize(file);
	if (lexerDebug) {
		for (size_t i = 0; i<tokens.size(); ++i) {
			printf("{%d, %s, %d, %d}\n", (int)tokens[i].type, tokens[i].value.c_str(), tokens[i].line, tokens[i].column);
		}
		exit(0);
	}

	// setup built in functions
	ATM::Language_Components atm = ATM::Init();
	ATM_AddBuiltInFunctions(atm);

	// run interpreter
	interpretTokens(tokens, atm);

	if (showStack) {
		printf("Program finished, memory reached size %d\n", (int)atm.stack.size());
		for (size_t i = 0; i<atm.stack.size(); ++i) {
			printf("{%d}, ", atm.stack[i]);
		}
		putchar(10);
	}

	return 0;
}