#include "_components.hh"
#include "atoment.hh"

void keyword_def(ATM::Language_Components& atm, ATM::Arglist args) {
	if (args.size() != 2) {
		printf("keyword_def: requires 2 arguments (given %d)\n", (int)args.size());
		exit(1);
	}
	if (args[0].index() != 0) {
		printf("keyword_def: first argument must be a string (given %d)\n", (int)args[0].index());
		exit(1);
	}
	if ((args[1].index() != 1) && (args[1].index() != 2)) {
		printf("keyword_def: second argument must be an integer or a pointer (given %d)\n", (int)args[1].index());
		exit(1);
	}
	if (args[1].index() == 1) atm.variables[get <string> (args[0])] = get <ATM_Integer> (args[1]);
	else atm.variables[get <string> (args[0])] = get <ATM_Pointer> (args[1]).address;
}

void keyword_delete(ATM::Language_Components& atm, ATM::Arglist args) {
	if (args.size() != 1) {
		printf("keyword_delete: requires 1 argument (given %d)\n", (int)args.size());
		exit(1);
	}
	try {
		atm.variables.erase(get<string>(args[0]));
	}
	catch (std::invalid_argument& e) {
		printf("keyword_delete: invalid arguments");
		exit(1);
	}
}