#include "_components.hh"

namespace Lexer {
	enum class TokenType {
		Function = 0,
		Keyword = 1,
		String = 2,
		Number = 3,
		EndOfArguments = 4,
		EndOfFile = 5
	};
	struct Token {
		TokenType type;
		string    value;
		size_t    line, column;
		Token(TokenType type, string value, size_t ln, size_t col) : type(type), value(value), line(ln), column(col) {}
	};
	vector <Token> tokenize(string source);
}