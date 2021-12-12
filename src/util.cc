#include "atoment.hh"
#include "util.hh"

bool Util::IsNumber(const string& str) {
	return str.find_first_not_of("0123456789") == string::npos;
}

void Util::logArguments(ATM::Arglist args) {
	for (size_t i = 0; i < args.size(); i++) {
		switch (args[i].index()) {
			case 0: { // string
				printf("Index %ld type string: %s\n", i, get <string> (args[i]).c_str());
				break;
			}
			case 1: { // integer
				printf("Index %ld type integer: %d\n", i, get <ATM_Integer> (args[i]));
				break;
			}
			case 2: { // pointer
				printf("Index %ld type pointer: %d\n", i, get <ATM_Pointer> (args[i]).address);
				break;
			}
			default: {
				printf("Index %ld: unrecognised\n", i);
				exit(1);
			}
		}
	}
}