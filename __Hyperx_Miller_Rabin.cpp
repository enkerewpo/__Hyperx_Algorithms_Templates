#include <bits/stdc++.h>

/* QUICK POWER */
template <typename T>
T power(T A, T B, T P) {
	T ret = 1;
	while(B) {
		if(B & 1) ret = ret * A % P;
		A = A * A % P;B >>= 1;
	} return ret;
}

/* MILLER RABIN PRIME */
const int u[15]={2,3,5,7,11,13,17,19,23,29,31,37}, cas = 12;

template <typename T>
bool miller_check(T a, T p) {
	T x = p - 1;
	if(power<T>(a, p-1, p) != 1) return false;
	while(~x & 1) x >>= 1; /* x is an even number */
	a = power<T>(a, x, p);
	while(x < p-1) {
		if(a != 1 && a != p-1) {
			a = a * a % p;
			if(a == 1) return false;
		} else a = a * a % p;
		x <<= 1;
	}
	return true;
}
template <typename T>
bool miller(T p) {
	if(p == 1 || p == 0) return 0;
	for(int i = 0; i < cas; i++) {
		//printf("P: %d NOW: %d\n", p, u[i]);
		if(p == u[i]) return true;
		if(!miller_check<T>(u[i],p)) return false;
	}
	return true;
}

int main() {
    return 0;
}
