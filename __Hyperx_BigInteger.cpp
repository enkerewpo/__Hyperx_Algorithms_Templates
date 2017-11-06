#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 1005;
const LL zip = 1e8;
class BigInt {
public:
    LL a[N];
    bool minus;
    BigInt() { minus = false; memset(a, 0, sizeof a); }
    template <typename _Tp>
    BigInt(_Tp x) {
        int p = 1, tmp = 0, y; a[0] = 1;
        while (x) {
            y = x % 10; tmp += y * pow(10, p - 1); p %= 8; x /= 10; if (p == 0) { a[a[0]] = tmp; tmp = 0; a[0]++; } p++;
        } if (tmp) a[a[0]] = tmp; else a[0]--;
    }
    void read() {
        char s[N]; scanf("%s", s + 1); int len = strlen(s + 1), st = 1; if (s[1] == '-') st = 2, minus = true;
        int p = 1, tmp = 0, y; a[0] = 1;
        for (int i = len; i >= st; i--) {
            y = (s[i] - '0') % 10, tmp += y * pow(10, p - 1), p %= 8; if (p == 0) { a[a[0]] = tmp; tmp = 0; a[0]++; } p++;
        } if (tmp) a[a[0]] = tmp; else a[0]--;
    }
    void print() {
        if ((a[0] == 0) || ((a[0] == 1) && (a[1] == 0))) { printf("0"); return;}
        if (minus) { printf("-"); if (a[a[0]]) printf("%lld", a[a[0]]); for (int i = a[0] - 1; i; i--) printf("%08lld", a[i]); return; }
        if (a[a[0]]) { printf("%lld", a[a[0]]); } for (int i = a[0] - 1; i; i--) printf("%08lld", a[i]);
    }
    BigInt abs() { BigInt ret = *this; ret.minus = 0; return ret; }
    LL operator [] (const unsigned int idx) const { return a[idx]; }
    LL& operator [] (const unsigned int idx) { return a[idx]; }
    friend bool operator == (const BigInt lhs, const BigInt rhs) {
        if(lhs.minus ^ rhs.minus) return false;
        if (lhs[0] == rhs[0]) {
            for (int i = 1; i <= lhs[0]; i++) { if (lhs[i] != rhs[i]) return false; } return true;
        } else return false;
    }
    friend bool operator > (const BigInt lhs, const BigInt rhs) {
        if (lhs[0] == rhs[0]) {
            for (int i = 1; i <= lhs[0]; i++) { if (lhs[i] > rhs[i]) return true; else return false; } return false;
        } else return lhs[0] > rhs[0];
    }
    friend BigInt operator + (BigInt a, BigInt b) {
        BigInt ret; bool f = a.minus ^ b.minus, g = false;
        if (f) { if (a.minus) g = true; a = a.abs(), b = b.abs(), ret = a - b; if(g) ret.minus ^= 1; return ret; }
        for (int i = 1; i <= max(a[0], b[0]); i++) { ret[i] += a[i] + b[i]; ret[i + 1] = ret[i] / zip; ret[i] %= zip;}
        ret[0] = max(a[0], b[0]);
        if (ret[ret[0] + 1]) {ret[0]++;} if (a.minus) ret.minus = true; return ret;
    }
    BigInt operator * (int rhs) {
        bool f = (rhs < 0) ^ minus; BigInt c; rhs = std::abs(rhs);
        for (int i = 1; i <= a[0]; i++) { c.a[i] += a[i] * rhs; if (c.a[i] >= zip) c.a[i + 1] += c.a[i] / zip, c.a[i] %= zip; }
        c.a[0] = a[0]; if (c.a[c.a[0] + 1] > 0) c.a[0]++; if (f) c.minus = true; return c;
    }
    BigInt operator * (const BigInt rhs) const {
        BigInt ret; bool f = false; if (minus || rhs.minus) f = true;
        for (int i = 1; i <= a[0]; i++)
            for (int j = 1; j <= rhs[0]; j++)
                ret[i + j - 1] += a[i] * rhs[j], ret[i + j] += ret[i + j - 1] / zip, ret[i + j - 1] %= zip;
        ret[0] = max(0LL, a[0] + rhs[0] - 1);
        if (ret[a[0] + rhs[0]]) {ret[0]++;} if (f) ret.minus = true; return ret;
    }
    friend BigInt operator - (BigInt lhs, BigInt rhs) {
        if (lhs == rhs) {return BigInt(0);}
        if(lhs.minus ^ rhs.minus) { if(rhs.minus) return lhs + rhs.abs(); else { BigInt ret = lhs.abs() + rhs.abs(); ret.minus = true; return ret; } }
        bool right = lhs > rhs;
        lhs = lhs.abs(), rhs = rhs.abs();
        if (rhs > lhs) swap(lhs, rhs);
        BigInt ret; memcpy(ret.a, lhs.a, sizeof lhs.a);
        for (int i = 1; i <= lhs.a[0]; i++) { ret[i] -= rhs[i]; if (ret[i] < 0) ret[i + 1]--, ret[i] += zip; }
        while (ret[0] >= 1 && !ret[ret[0]]) ret[0]--;
        if (!right) ret.minus = true;
        return ret;
    }
    BigInt operator / (int rhs) {
        BigInt c; LL x = 0; for (int i = a[0]; i; i--) x = x * zip + a[i], c.a[i] = x / rhs, x = x % rhs;
        c.a[0] = a[0]; if (c.a[0] && !c.a[c.a[0]]) c.a[0]--; return c;
    }
    LL operator % (int rhs) {
        BigInt c; LL x = 0; for (int i = a[0]; i; i--) x = x * zip + a[i], c.a[i] = x / rhs, x = x % rhs;
        c.a[0] = a[0]; if (c.a[0] && !c.a[c.a[0]]) c.a[0]--; return x;
    }
};

int main() {
    BigInt a, b;
    a.read(), b.read();
    BigInt c = a + b;
    c.print();
    return 0;
}