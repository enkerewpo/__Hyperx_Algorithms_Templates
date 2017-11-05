#ifndef __HYPERX_BIGINTEGET_HPP
#define __HYPERX_BIGINTEGET_HPP

#include <bits/stdc++.h>

const int zip = 1e8;
class BigInt {
public:
	int a[1005];
	BigInt() { memset(a, 0, sizeof a); }

	BigInt(int x) {
		memset(a, 0, sizeof a);
		int p = 1, tmp = 0; a[0] = 1; while (x) {
			int y = x % 10; tmp += y * pow(10, p - 1); p %= 8; x /= 10;
			if (p == 0) { a[a[0]] = tmp; tmp = 0; a[0]++; } p++;
		} if (tmp) a[a[0]] = tmp;
	}

	void read() {

	}

	void print() {
		if ((a[0] == 0) || ((a[0] == 1) && (a[1] == 0))) { printf("0"); return;}
		if (a[a[0]]) printf("%lld", a[a[0]]);
		for (int i = a[0] - 1; i; i--) printf("%08lld", a[i]);
	}
	int operator [] (const unsigned int idx) const { return a[idx]; }
	int& operator [] (const unsigned int idx) { return a[idx]; }

	BigInt operator * (const BigInt& rhs) const {
		BigInt ret;
		for (int i = 1; i <= a[0]; i++)
			for (int j = 1; j <= rhs[0]; j++)
				ret[i + j - 1] += a[i] * rhs[j], ret[i + j] += ret[i + j - 1] / zip, ret[i + j - 1] %= zip;
		ret[0] = max(0ll, a[0] + rhs[0] - 1);
		if (ret[a[0] + rhs[0]]) ret[0]++; return ret;
	}

	BigInt operator + (const int rhs) {
		BigInt b(rhs), ret;
		for (int i = 1; i <= max(a[0], b[0]); i++) { ret[i] += a[i] + b[i]; ret[i + 1] = ret[i] / zip; ret[i] %= zip;}
		ret[0] = max(a[0], b[0]);
		if (ret[ret[0] + 1]) ret[0]++; return ret;
	}

	BigInt operator - (const BigInt rhs) {
		BigInt ret;
		memcpy(ret.a, a, sizeof a);
		for (int i = 1; i <= a[0]; i++) {
			ret[i] -= rhs[i];
			if (ret[i] < 0) ret[i + 1]--, ret[i] += zip;
		}
		while (ret[0] >= 0 && !ret[ret[0]]) ret[0]--; return ret;
	}

};
#endif //__HYPERX_BIGINTEGET_HPP
