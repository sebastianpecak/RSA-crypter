#include "rsaCrypter.h"
#include <iostream>

using namespace std;

main() {
	int num = 0;
	cout <<"Number: ";
	cin >>num;
	
	// Generuje klucze
	RSA rsa(53, 101);
	// Szyfruje / deszyfruje
	RSACrypter crypter(&rsa);
	
	cout <<"\nPrivate key: ("<<rsa.getPrivateKey()._a<<", "<<rsa.getPrivateKey()._b<<")\n";
	cout <<"Public key: ("<<rsa.getPublicKey()._a<<", "<<rsa.getPublicKey()._b<<")\n";
	
	Long encrypted = crypter.encrypt<int>(num);
	
	cout <<"Ecrypted: "<<encrypted;
	cout <<"\nDecrypted: "<<crypter.decrypt<Long>(encrypted)<<endl;
}