#define EPS 1e-8
long long mul(long long a, long long b, long long p) {
	long long ret = a * b - (long long)((long double)a / p * b + EPS) * p;
	return ret < 0 ? ret + p : ret;
}

long long mul(long long a, long long b, long long p) {
	long long ret = 0;
	while (b) {
		if (b & 1) ret = (ret + a) % p;
		a = (a + a) % p;
		a >>= 1;
	}
	return ret;
}
