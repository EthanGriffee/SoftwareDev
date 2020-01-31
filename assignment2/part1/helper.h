//lang: CwC
#pragma once
#include <iostream>
class Cout {
public:
	// print
	void p(char* s) { std::cout << s; }
	void p(int i) { std::cout << i; }
	void p(const char* s) { std::cout << s; }

	// char* = array of characters
	// "hello" is a const char* but won't be using in Cwc except with literal strings
	void pln(char* s) { std::cout << s << "\n"; }
	void pln(int i) { std::cout << i << "\n"; }
	void pln(const char* s) { std::cout << s << "\n"; }

    void t_true(const bool val) {
        if (val) {
            pln("The test passed");
        } else {
            pln("The test failed");
        }
    }

};