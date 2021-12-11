#include "_components.hh"
#include "atoment.hh"
#include "builtin.hh"

ATM::Language_Components ATM::Init() {
	ATM::Language_Components components;

	// init memory
	components.stack.push_back(0); // NULL
	components.stack.push_back(0); // accumulator

	// init variables
	components.variables["NULL"]      = 0;
	components.variables["MEM_ACC"]   = 1;
	components.variables["true"]      = 1;
	components.variables["false"]     = 0;
	components.variables["MEM_START"] = 2;
	
	return components;
}

void ATM::RegisterFunction(ATM::Language_Components &atm, string name, ATM::Function* function) {
	atm.functions[name] = function;
}

void ATM_AddBuiltInFunctions(ATM::Language_Components &atm) {
	ATM::RegisterFunction(atm, "push", builtin_push);
	ATM::RegisterFunction(atm, "pop", builtin_pop);
	ATM::RegisterFunction(atm, "println", builtin_println);
	ATM::RegisterFunction(atm, "putchar", builtin_putchar);
}