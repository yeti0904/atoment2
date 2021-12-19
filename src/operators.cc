#include "operators.hh"

void Operators::Equal(ATM::Language_Components& atm, ATM::Arglist args) {
	if (args.size() != 2) {
		printf("Error: too many arguments on equal operator (given %d)\n", (int)args.size());
		exit(1);
	}
	if (args[0].index() != 0) {
		printf("Error: invalid lvalue on equal operator (given %d)\n", (int)args[0].index());
		exit(1);
	}
	if ((args[1].index() != 1) && (args[1].index() != 2)) {
		printf("Error: variables may only hold an integer or a pointer\n");
		exit(1);
	}
	if (args[1].index() == 1) atm.variables[get <string>(args[0])] = get <ATM_Integer>(args[1]);
	if (args[1].index() == 2) atm.variables[get <string>(args[0])] = get <ATM_Pointer>(args[1]).address;
}