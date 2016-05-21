#ifndef RSACRYPTER_H
#define RSACRYPTER_H

#include "rsa.h"
#include <stdexcept>
#include <cmath>
#include "tools.h"

class RSACrypter {
	RSA *_rsaObject;
	
public:
	explicit RSACrypter(RSA * = nullptr);
	
	template <typename T>
	Long encrypt(T) const;
	
	template <typename T>
	Long decrypt(T) const;
	
	void setRSAObject(RSA *);
	
	RSA* getRSAObject();
};

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
RSACrypter::RSACrypter(RSA *rsaObject) {
	_rsaObject = rsaObject;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void RSACrypter::setRSAObject(RSA *rsaObject) {
	_rsaObject = rsaObject;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
RSA* RSACrypter::getRSAObject() {
	return _rsaObject;
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template <typename T>
Long RSACrypter::encrypt(T value) const {
	if(_rsaObject) return Tools::modpowX<Long>(value, _rsaObject->getPublicKey()._b, _rsaObject->getPublicKey()._a);
	else throw std::logic_error("RSA object not defined.");
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
template <typename T>
Long RSACrypter::decrypt(T value) const {
	if(_rsaObject) return Tools::modpowX<Long>(value, _rsaObject->getPrivateKey()._b, _rsaObject->getPrivateKey()._a);
	else throw std::logic_error("RSA object not defined.");
}

#endif