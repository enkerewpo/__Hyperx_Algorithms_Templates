#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cmath>
#define N 500000 + 5
#define inf 0x7fffffff
using namespace std;
#define mem(x) memset(x, 0, sizeof (x))

int fa[N], vis[N], dis[N], maxdis, maxi;
int hd[N], nxt[N], to[N], w[N], tot;
int n, s, diameter, ans;
int dia[N], dtot;
bool f;

void add(int a, int b, int c) {
    nxt[++tot] = hd[a], to[hd[a] = tot] = b, w[tot] = c;
    nxt[++tot] = hd[b], to[hd[b] = tot] = a, w[tot] = c;
}
void push(int u) { f = 1; while (u) { dia[++dtot] = u; u = fa[u]; } }
void dfs(int u, int Fa, int final) {
    if (final == 1 && dis[u] == maxdis && !f) { push(u); return; } fa[u] = Fa;
    for (int e = hd[u]; e; e = nxt[e]) {
        int v = to[e]; if (v != Fa) {
            if (final == 2 && vis[v]) continue;
            dis[v] = dis[u] + w[e];
            if (dis[v] > maxdis) maxdis = dis[v], maxi = v;
            dfs(v, u, final);
        }
    }
}
int main() {
    read(n), read(s); ans = inf;
    for (int i = 1; i < n; i++) { int a, b, c; read(a), read(b), read(c); add(a, b, c); }
    int tmp; dfs(1, 0, 0), maxdis = 0, mem(dis), mem(fa), dfs(tmp = maxi, 0, 0), dfs(tmp, 0, 1);
    diameter = maxdis;
    return 0;
}