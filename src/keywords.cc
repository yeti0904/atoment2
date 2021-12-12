#include "_components.hh"
#include "atoment.hh"

void keyword_def(ATM::Language_Components& atm, ATM::Arglist args) {
	if (args.size() != 2) {
		printf("keyword_def: requires 2 arguments (given %ld)\n", args.size());
		exit(1);
	}
	try {
		atm.variables[get<string>(args[0])] = get<ATM_Integer>(args[1]);
	}
	catch (std::invalid_argument& e) {
		printf("keyword_def: invalid arguments");
		exit(1);
	}
}

void keyword_delete(ATM::Language_Components& atm, ATM::Arglist args) {
	if (args.size() != 1) {
		printf("keyword_delete: requires 1 argument (given %ld)\n", args.size());
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