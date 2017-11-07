#include <bits/stdc++.h>

using namespace std;
const int N = 5005;

int a[N], b[N], f[N][N], g[N][N];

void work(int x, int y, int z) {
    if (!z) return;
    while (a[x] != b[y]) --x;
    work(x, g[x][y], z - 1);
    printf("%d ", b[y]);
}
int main() {
    int n, m, i, tma, pre, j, ans = 0, t;
    scanf("%d", &n);
    for (i = 1; i <= n; ++i) scanf("%d", &a[i]);
    scanf("%d", &m);
    for (i = 1; i <= m; ++i) scanf("%d", &b[i]);
    for (i = 1; i <= n; ++i)
        for (tma = 0, j = 1; j <= m; ++j) {
            if (b[j] < a[i] && f[i - 1][j] > tma) tma = f[i - 1][pre = j];
            if (a[i] == b[j]) {f[i][j] = tma + 1; g[i][j]=pre;} else f[i][j] = f[i - 1][j];
            if (f[i][j] > ans) ans = f[i][t = j];
        }
    printf("%d\n", ans);
    if (ans) {
        work(n, t, ans);
        printf("\n");
    }
    return 0;
}