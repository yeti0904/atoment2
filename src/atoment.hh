#pragma once
#include "_components.hh"

struct ATM_Pointer {
	ATM_Integer address;
	ATM_Pointer(ATM_Integer addr): address(addr) {};
};

namespace ATM {
	typedef vector <variant <string, ATM_Integer, ATM_Pointer>> Arglist;
	struct Language_Components;
	typedef void (Function)(Language_Components&, Arglist);
	struct Language_Components {
		unordered_map <string, Function*>   functions;
		unordered_map <string, Function*>   keywords;
		unordered_map <string, ATM_Integer> variables;
		vector <ATM_Integer>			    stack;
	};
	ATM::Language_Components Init();
	void RegisterFunction(Language_Components &atm, string name, Function* function);
}

void ATM_AddBuiltInFunctions(ATM::Language_Components &atm);