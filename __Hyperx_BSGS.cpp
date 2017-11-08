# include <stdio.h>
# include <math.h>
# include <map>
using namespace std;
typedef long long LL;
LL bsgs(LL A, LL B, LL C) {
    LL m, v, e = 1, i;
    m = ceil(sqrt(C));
    v = pow(A, C - 1 - m, C);
    map<LL, LL> hash;
    hash[1] = m;
    for (i = 1; i < m; ++i) {
        e = (e * A) % C;
        if (!hash[e]) hash[e] = i;
    }
    for (i = 0; i < m; ++i) {
        if (hash[B]) {
            LL ret = hash[B];
            hash.clear();
            return i * m + (ret == m ? 0 : ret);
        }
        B = (B * v) % C;
    }
    return -1;
}
int main() {
    LL A, B, C;
    // A ^ x = B mod C
    while (scanf("%lld%lld%lld", &C, &A, &B) != EOF) {
        LL ans = bsgs(A, B, C);
        if (ans == -1) printf("no solution\n");
        else printf("%lld\n", ans);
    }
    return 0;
}