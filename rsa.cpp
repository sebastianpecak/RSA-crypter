#include "rsa.h"

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
Long RSA::_primeNumbers[RSA_PRIMES_COUNT] = {
		7, 11, 13, 17, 19,
		23, 29, 31, 37, 41
};

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
RSA::RSA() {
	selectPrimes();
	calculateN();
	generateKeys();
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
RSA::RSA(Long p, Long q) {
	// Here we should check out data correctness, but... who cares
	_p = p;
	_q = q;
	calculateN();
	generateKeys();
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

RSA::RSA(CString path) try {
	if(strlen(path) > 0) {
		String _path = path;
		if(_path.at(_path.length() - 1) != '/') _path += '/';
		File privFile((_path + "rsa.priv").c_str(), std::ios::in), pubFile((_path + "rsa.pub").c_str(), std::ios::in);
		try {
			if(privFile.is_open() && pubFile.is_open()) {
				try {
					_privateKey.set(getKeyFromFile(privFile));
					_publicKey.set(getKeyFromFile(pubFile));
				}
				catch(...) {
					// If threre were any failure set default
					selectPrimes();
					calculateN();
					generateKeys();
				}
			}
			else throw std::logic_error("RSA key files not found.");
		} catch(std::logic_error er) {
			std::cout<<"\n@@ RSA::RSA(CString): "<<er.what()<<"\n";
		}
	}
	else throw std::logic_error("Invalid rsa keys path.");
} catch(std::logic_error er) {
	std::cout <<"\n@@ RSA::RSA(CString): "<<er.what()<<"\n";
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
void RSA::saveToFile(CString path) const try {
	if(strlen(path) > 0) {
		String _path = path;
		if(_path.at(_path.length() - 1) != '/') _path+='/';
		_privateKey.saveToFile((_path + "rsa.priv").c_str());
		_publicKey.saveToFile((_path + "rsa.pub").c_str());
	}
	else throw std::logic_error("Invalid keys path.");
} catch(std::logic_error er) {
	std::cout <<"@@ RSA::saveToFile(CString): "<<er.what()<<"\n";
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
Key<Long, Long> RSA::getKeyFromFile(File& file) const {
	if(file.good()) {
		file.seekg(0);
		file.seekp(0);
		String line("");
		getline(file, line);
		String num1(""), num2(""), *target = &num1;
		for(char i : line) {
			if(i != ' ') *target+=i;
			else target = &num2;
		}
		
		Key<Long, Long> out;
		out.set((Long)std::stoi(num1, nullptr, 16), (Long)std::stoi(num2, nullptr, 16));
		return out;
	}
	else throw std::logic_error("RSA key file is not accessable.");
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
void RSA::selectPrimes() {
	srand(time(nullptr));
	_p = _primeNumbers[rand()%RSA_PRIMES_COUNT];
	_q = _primeNumbers[rand()%RSA_PRIMES_COUNT];
	while(_q == _p) _q = rand()%RSA_PRIMES_COUNT;
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
void RSA::calculateN() {
	_n = _p*_q;
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
Long RSA::fi() {
	return (_p-1)*(_q-1);
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
void RSA::getPrimes(Long* p, Long* q) const {
	if(p && q) {
		*p = _p;
		*q = _q;
	}
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
void RSA::setPrimes(Long p, Long q) {
	_p = p;
	_q = q;
	calculateN();
	generateKeys();
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
void RSA::generateKeys() {
	// Select numer e
	// e is low odd number
	unsigned e=3;
	while(nwd(e, fi()) != 1) e+=2;
	// Simple and very prone to mistakes method, thats all we need
	_publicKey.set(_n, e);
	
	//Long d = (fi() + 1) / e;
	
	// Liczymy odwrotność modulo
	// na podstawie:
	// https://pl.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/modular-inverses
	Long d = 1, _fi = fi();
	while(((e*d)%_fi) != 1) d++;
	
	_privateKey.set(_n, d);
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
// we are looking for the lowest number nws(a,b)=1
unsigned RSA::nwd(unsigned a, Long b) {
	while(a != b) {
		if(a > b) a-=b;
		else b-=a;
	}
	return a;
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
Key<Long, Long> RSA::getPrivateKey() const {
	return _privateKey;
}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
Key<Long, Long> RSA::getPublicKey() const {
	return _publicKey;
}