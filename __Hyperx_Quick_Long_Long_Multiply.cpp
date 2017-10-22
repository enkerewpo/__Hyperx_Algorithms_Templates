#define EPS 1e-8
long long mul(long long a, long long b, long long p) {
    long long ret = (a * b - (long long)((long double)a / p * b + EPS) * p);
    return ret < 0 ? ret + p : ret;
}
