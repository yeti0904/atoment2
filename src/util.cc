#include "util.hh"

bool Util::IsNumber(const string& str) {
    return str.find_first_not_of("0123456789") == string::npos;
}