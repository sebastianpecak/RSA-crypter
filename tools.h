#ifndef TOOLS_H
#define TOOLS_H

typedef long long Long;

class Tools {
public:
	template <typename T>
	static T modpowX(T, T, T);
};

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
template <typename T>
T Tools::modpowX(T a, T b, T m) {
	T i;
	T result = 1;
	Long x = a%m;
	 
	for (i=1; i<=b; i<<=1) {
		x %= m;
		if ((b&i) != 0) {
			result *= x;
			result %= m;
		}
		x *= x;
	}
	return result;
}

#endif