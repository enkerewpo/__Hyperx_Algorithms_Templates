#define LL long long
LL CRT(int n, LL *m, LL *a) {
    LL M = 1, d, y, x = 0;
    for (int i = 1; i <= n; i++) M *= m[i];
    for (int i = 1; i <= n; i++) {
        LL w = M / m[i];
        exgcd(m[i], w, d, d, y);
        x = (x + y * w * a[i]) % M;
    }
    return (x + M) % M;
}
LL m[15], a[15];
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld%lld", &m[i], &a[i]);
    printf("%lld", CRT(n, m, a));
}