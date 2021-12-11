#include "_components.hh"

namespace ATM {
	typedef vector <variant <string, ATM_Integer>> Arglist;
	struct Language_Components {
		unordered_map <string, Function*>   functions;
		unordered_map <string, Function*>   keywords;
		unordered_map <string, ATM_Integer> variables;
		vector <ATM_Integer>			    stack;
	};
	typedef void (Function)(Language_Components, Arglist);
}