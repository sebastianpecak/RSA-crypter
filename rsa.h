#ifndef RSA_H
#define RSA_H

#include "key.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

#define RSA_PRIMES_COUNT 10

typedef long long Long;

class RSA {
	
	static Long _primeNumbers[RSA_PRIMES_COUNT];
	
	// Big primes
	Long _p, _q, _n;
	
	void selectPrimes();
	void calculateN();
	Long fi();
	void generateKeys();
	unsigned nwd(unsigned, Long);
	
	Key<Long, Long> _privateKey;
	Key<Long, Long> _publicKey;
	
	Key<Long, Long> getKeyFromFile(File&) const;
	
public:
	RSA();
	RSA(Long, Long);
	// This constructor opens files containing keys
	// So that we can use exsisting keys
	explicit RSA(CString);
	
	void setPrimes(Long, Long);
	void getPrimes(Long*, Long*) const;
	void saveToFile(CString) const;
	
	Key<Long, Long> getPublicKey() const;
	Key<Long, Long> getPrivateKey() const;
};

#endif