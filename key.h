#ifndef KEY_H
#define KEY_H

#include <fstream>
#include <stdexcept>
#include <cstring>
#include <string>
#include <sstream>
#include <iostream>

typedef std::string String;
typedef const char* CString;
typedef std::fstream File;

template <typename A, typename B>
struct Key {
	A _a;
	B _b;
	
	void set(A a, B b) {
		_a = a;
		_b = b;
	}
	
	void set(Key);
	
	void saveToFile(CString) const;
};

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
template <typename A, typename B>
void Key<A, B>::saveToFile(CString fileName) const try {
	if(strlen(fileName) > 0) {
		File keyFile(fileName, std::ios::out);
		if(keyFile.is_open()) {
			std::stringstream textNumber;
			textNumber << std::hex << _a;
			String out = textNumber.str() + " ";
			textNumber.str("");
			textNumber << std::hex << _b;
			out += textNumber.str();
			keyFile << out;
			keyFile.close();
		}
		else throw std::logic_error("Cannot open required file.");
	}
	else throw std::logic_error("Invalid file name.");
} catch(std::logic_error e) {
	std::cout <<"\n@@ Key<A,B>::saveToFile(CString): "<<e.what()<<"\n";
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
template <typename A, typename B>
void Key<A, B>::set(Key key) {
	_a = key._a;
	_b = key._b;
}

#endif