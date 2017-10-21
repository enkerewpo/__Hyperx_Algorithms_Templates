#include <cstdio>
#include <iostream>
#include <bitset>
using namespace std;
#define MAXN 20

int main() {
	bitset<5> a("10010");
	bitset<5> b("01110");
	cout << (a ^ b) << endl; // 11100
	cout << (a & b) << endl; // 00010
	a.flip();
	cout << a << endl; // 01101
	return 0;
}