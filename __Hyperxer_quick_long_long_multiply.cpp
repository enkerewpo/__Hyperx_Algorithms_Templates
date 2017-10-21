long long mul(long long a, long long b, long long p) {
    long long ret = (a * b - (long long)((long double)a / p * b) * p) % p;
    if(ret < 0) ret += p;
    return ret;
}
