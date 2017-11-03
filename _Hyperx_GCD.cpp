#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

typedef long long ll;
const int N = 10000000 + 5;
const int sqrtN = sqrt(N);
int st[N], tot, d[N][5];
int _gcd[sqrtN + 5][sqrtN + 5];
bool notp[N];

void sieve() {
    notp[1] = d[1][0] = d[1][1] = d[1][2] = 1;
    for (ll i = 2; i <= N; i++) {
        if (!notp[i]) {
            d[i][0] = d[i][1] = 1;
            d[i][2] = i;
            st[++tot] = i;
        }
        for (ll j = 1; j <= tot && i * st[j] <= N; j++) {
            ll k = i * st[j];
            notp[k] = true;
            ll p = d[i][0] * st[j];
            if (p < d[i][1]) {
                d[k][0] = p;
                d[k][1] = d[i][1];
                d[k][2] = d[i][2];
            } else if (p < d[i][2]) {
                d[k][0] = d[i][1];
                d[k][1] = p;
                d[k][2] = d[i][2];
            } else {
                d[k][0] = d[i][1];
                d[k][1] = d[i][2];
                d[k][2] = p;
            }
            if (i % st[j]); else break;
        }
    }
}

void calc() {
    for (ll i = 0; i <= sqrtN; i++) _gcd[i][0] = _gcd[0][i] = i;
    for (ll i = 1; i <= sqrtN; i++) {
        for (ll j = 1; j <= i; j++) _gcd[i][j] = _gcd[j][i] = _gcd[i - j][j];
    }
}

ll gcd(ll a, ll b) {
    int *x = d[a], g = 1;
    for (ll i = 0; i < 3; i++) {
        ll d;
        if (x[i] <= sqrtN) d = _gcd[x[i]][b % x[i]];
        else if (b % x[i]) d = 1;
        else d = x[i];
        g *= d; b /= d;
    }
    return g;
}

ll A, B;

int main() {
    sieve();
    calc();
    return 0;
}

