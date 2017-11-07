#include <cstdio>
#include <algorithm>
#include <stack>
#include <cstring>

#define N 100 + 5
#define M 500 + 5
using namespace std;

int dp[N][M];

int hd[N], nxt[N], to[N], tot;
int hd2[N], nxt2[N], to2[N], in2[N], tot2;
void add (int a, int b) { nxt [++tot ] = hd [a], to [hd [a] = tot ] = b; }
void add2(int a, int b) { nxt2[++tot2] = hd2[a], to2[hd2[a] = tot2] = b, in2[b]++; }

int n, m, _n, color[N], low[N], dfn[N], tim, sv[N], sw[N];
int v[N], w[N];
bool vis[N];
stack<int> s;

void tarjan(int u) {
	low[u] = dfn[u] = ++tim;
	s.push(u);
	vis[u] = true;
	for (int e = hd[u]; e; e = nxt[e]) {
		int v = to[e];
		if (!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		} else if (vis[v])low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		_n++; int x; do {
			x = s.top();
			s.pop();
			vis[x] = false;
			color[x] = _n;
			sv[_n] += v[x];
			sw[_n] += w[x];
		} while (x != u);
	}
}

void dfs(int i) {
	for (int e = hd2[i]; e; e = nxt2[e]) {
		int v = to2[e];
		dfs(v);
		for (int j = m - sw[i]; j >= 0; j--) {
			for (int k = 0; k <= j; k++) {
				dp[i][j] = max(dp[i][j], dp[i][k] + dp[v][j - k]);
			}
		}
	}
	for (int j = m; j >= 0; j--) {
		if (j >= sw[i]) dp[i][j] = dp[i][j - sw[i]] + sv[i];
		else dp[i][j] = 0;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
	for (int i = 1; i <= n; i++) scanf("%d", &v[i]);
	for (int i = 1; i <= n; i++) {
		int a;
		scanf("%d", &a);
		if (a) add(a, i);
	}
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	for (int i = 1; i <= n; i++) {
		for (int e = hd[i]; e; e = nxt[e]) {
			int v = to[e];
			if (color[v] != color[i]) add2(color[i], color[v]);
		}
	}
	for (int i = 1; i <= _n; i++) if (in2[i] == 0) add2(_n + 1, i);
	dfs(_n + 1);
	printf("%d\n", dp[_n + 1][m]);
	return 0;
}