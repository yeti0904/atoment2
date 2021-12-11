#include <cstdio>
#include "atoment.hh"

void builtin_println(ATM::Language_Components atm, ATM::Arglist args) {
	if (args.size() < 1) {
		printf("Error: println requires at least one argument\n");
	}
	for (auto arg : args) {
		if (arg.index() == 0) {
			atm.stack[atm.variables["MEM_ACC"]] = printf("%s", get<0>(arg).c_str());
		}
		else if (arg.index() == 2) {
			for (size_t i = atm.stack[get<2>(arg).address]; atm.stack[i] != 0; ++i) {
				putchar(atm.stack[i]);
			}
		}
		else {
			atm.stack[atm.variables["MEM_ACC"]] = printf("%u", get<1>(arg));
		}
	}
	putchar(10);
}

void builtin_push(ATM::Language_Components atm, ATM::Arglist args) {
	if (args.size() < 1) {
		printf("Error: push requires at least one argument\n");
		exit(1);
	}
	for (auto arg : args) {
		ATM::Arglist test;
		test.push_back(65);
		try {
			atm.stack.push_back(get<ATM_Integer>(test[0]));
		}
		catch (const std::bad_variant_access&) {
			printf("Error: push requires integer arguments\n");
			exit(1);
		}
	}
}

void builtin_pop(ATM::Language_Components atm, ATM::Arglist args) {
	if (args.size() > 0) {
		printf("Error: pop requires no arguments\n");
		exit(1);
	}
	atm.stack.pop_back();
}

void builtin_putchar(ATM::Language_Components atm, ATM::Arglist args) {
	if (args.size() < 1) {
		printf("Error: putchar requires at least one argument\n");
		exit(1);
	}
	for (auto arg : args) {
		if (arg.index() == 0) {
			printf("Error: putchar requires integer arguments\n");
			exit(1);
		}
		atm.stack[atm.variables["MEM_ACC"]] = putchar(get<1>(arg));
	}
}