#ifndef RSABLOCKCRYPTER_H
#define RSABLOCKCRYPTER_H

#include <istream>
#include <ostream>
#include "rsaCrypter.h"

typedef std::basic_istream<char> InStream;
typedef std::basic_ostream<char> OutStream;
typedef char Byte;

class RSABlockCrypter {
	static unsigned STDBLOCKSIZE;
	
	RSACrypter *_rsaCrypter;
	
public:
	explicit RSABlockCrypter(RSACrypter * = nullptr);
	
	void setRSACrypter(RSACrypter*);
	
	void encrypt(InStream*, OutStream*) const;
	void decrypt(InStream*, OutStream*) const;
	
	static void setStdBlockSize(unsigned);
};

// 2 bajty jako std rozmiar bloku kodowania
unsigned RSABlockCrypter::STDBLOCKSIZE = 1;

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
RSABlockCrypter::RSABlockCrypter(RSACrypter *rsaCrypter) : _rsaCrypter(rsaCrypter) {}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void RSABlockCrypter::setRSACrypter(RSACrypter *rsaCrypter) {
	_rsaCrypter = rsaCrypter;
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void RSABlockCrypter::setStdBlockSize(unsigned size) {
	if(size > 0) RSABlockCrypter::STDBLOCKSIZE = size;
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void RSABlockCrypter::encrypt(InStream *ins, OutStream *outs) const try {
	if(_rsaCrypter && ins && outs) {
		// Create bytes buffer
		try {
			Byte *buffer = new Byte[STDBLOCKSIZE];
			if(buffer) {
				while(!ins->eof()) {
					ins->read(buffer, STDBLOCKSIZE);
					char value = *(char*)buffer;
					Long lvalue = value;
					Long enc = _rsaCrypter->encrypt<Long>(lvalue);
					outs->write((char*)&enc, 8);
				}
			}
			else throw std::logic_error("Cannot create bytes buffer.");
		} catch(...) {
			// Propagate excetion
			throw;
		}
	}
	else throw std::logic_error("No RSACrypter object set.");
} catch(std::logic_error er) {
	std::cout <<"\n@@ RSABlockCrypter::encrypt(InStream&, OutStream&): "<<er.what()<<"\n";
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void RSABlockCrypter::decrypt(InStream *ins, OutStream *outs) const try {
	if(_rsaCrypter && ins && outs) {
		// Create bytes buffer
		try {
			Byte *buffer = new Byte[8];
			if(buffer) {
				while(!ins->eof()) { 
					ins->read(buffer, 8);
					Long value = *(Long*)buffer;
					Long dec = _rsaCrypter->decrypt<Long>(value);
					char outValue = dec;
					outs->write(&outValue, 1);
				}
			}
			else throw std::logic_error("Cannot create bytes buffer.");
		} catch(...) {
			// Propagate excetion
			throw;
		}
	}
	else throw std::logic_error("No RSACrypter object set.");
} catch(std::logic_error er) {
	std::cout <<"\n@@ RSABlockCrypter::encrypt(InStream&, OutStream&): "<<er.what()<<"\n";
} catch(...) {
	std::cout <<"\n@@ RSABlockCrypter::encrypt(InStream&, OutStream&): Other error.\n";
}

#endif