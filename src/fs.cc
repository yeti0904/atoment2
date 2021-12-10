#include "_components.hh"
#include "fs.hh"

bool FS::Exists(string path) {
	ifstream file(path);
	return file.good();
}

string FS::ReadFile(string path) {
	ifstream fhnd(path);
	string buf;
	string line;
	while (getline(fhnd, line)) {
		buf += line + "\n";
	}
	return buf;
}