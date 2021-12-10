#include <cstdio>
#include <cstddef>
#include "_components.hh"
#include "fs.hh"
#include "lexer.hh"

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

	string programpath;
	// loop through args
	for (size_t i = 1; i<args.size(); ++i) {
		// if arg is a file
		if (args[i][0] != '-') {
			programpath = args[i];
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
	for (size_t i = 0; i<tokens.size(); ++i) {
		printf("{%d, %s, %ld, %ld}\n", (int)tokens[i].type, tokens[i].value.c_str(), tokens[i].line, tokens[i].column);
	}
	return 0;
}