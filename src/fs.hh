#pragma once
#include "_components.hh"

namespace FS {
	bool   Exists(string path);
	string ReadFile(string path);
}