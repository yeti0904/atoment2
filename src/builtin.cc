#include <cstdio>
#include "atoment.hh"

void builtin_println(ATM::Language_Components& atm, ATM::Arglist args) {
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

void builtin_push(ATM::Language_Components& atm, ATM::Arglist args) {
	if (args.size() < 1) {
		printf("Error: push requires at least one argument\n");
		exit(1);
	}
	for (auto arg : args) {
		switch (arg.index()) {
			case 0: {
				printf("Error: push requires an integer or address\n");
				break;
			}
			case 1: {
				atm.stack.push_back(get<ATM_Integer>(arg));
				break;
			}
			case 2: {
				atm.stack.push_back(get<ATM_Pointer>(arg).address);
				break;
			}
		}
	}
}

void builtin_pop(ATM::Language_Components& atm, ATM::Arglist args) {
	if (args.size() > 0) {
		printf("Error: pop requires no arguments\n");
		exit(1);
	}
	atm.stack.pop_back();
}

void builtin_putchar(ATM::Language_Components& atm, ATM::Arglist args) {
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

void builtin_create_bytes(ATM::Language_Components& atm, ATM::Arglist args) {
	if (args.size() != 1) {
		printf("Error: create_bytes requires one argument\n");
		exit(1);
	}
	if (args[0].index() != 1) {
		printf("Error: create_bytes requires an integer argument\n");
		exit(1);
	}
	for (size_t i = 0; i < get<ATM_Integer>(args[0]); ++i) {
		atm.stack.push_back(0);
	}
}

void builtin_add(ATM::Language_Components& atm, ATM::Arglist args) {
	if (args.size() < 2) {
		printf("Error: add requires at least two arguments\n");
		exit(1);
	}
	for (auto arg : args) {
		if ((arg.index() != 1) && (arg.index() != 2)) {
			printf("Error: add requires integer or pointer arguments\n");
			exit(1);
		}
	}
	ATM_Integer addby;
	if (args[1].index() == 1) addby = get <ATM_Integer> (args[1]);
	else addby = get<2>(args[1]).address;

	if (args[0].index() == 1) { // source isn't a pointer, save the result in MEM_ACC
		atm.stack[atm.variables["MEM_ACC"]] = get<ATM_Integer>(args[0]) + addby;
	}
	else { // source is a pointer, save the result where the pointer is pointing to
		atm.stack[get<2>(args[0]).address] = atm.stack[get<2>(args[0]).address] + addby;
	}
}