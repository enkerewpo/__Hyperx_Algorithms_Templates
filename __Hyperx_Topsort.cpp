#include <algorithm>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <bitset>
#include <stack>
#define N (2000 + 5)
#define M (N * N >> 1) + 5
using namespace std;

int hd[N], nxt[M], to[M], tot;
int hd2[N], nxt2[M], to2[M], tot2;
int in[N];
void add(int a, int b) { nxt[++tot] = hd[a], to[hd[a] = tot] = b; }
void add2(int a, int b) { nxt2[++tot2] = hd2[a], to2[hd2[a] = tot2] = b, in[b]++; }

bitset<N> dp[N];
int n, _n, scc[N], siz[N], ans;

void topological_sort() {
	int q[N], head = 0, tail = -1;
	memset(q, 0, sizeof q);
	for (int i = 1; i <= _n; i++) {
		if (in[i] == 0) {
			q[++tail] = i;
			ans += siz[i] * dp[i].count();
		}
	}
	while (head <= tail) {
		int u = q[head++];
		for (int e = hd2[u]; e; e = nxt2[e]) {
			int v = to2[e];
			dp[v] |= dp[u];
			if (--in[v] == 0) {
				q[++tail] = v;
				ans += siz[v] * dp[v].count();
			}
		}
	}

}

bool vis[N];
int low[N], dfn[N], tim, x;
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
		} else if (vis[v]) low[u] = min(low[u], dfn[v]);
	}
	if (low[u] == dfn[u]) {
		_n++; do {
			x = s.top();
			s.pop();
			vis[x] = false;
			scc[x] = _n;
			siz[_n]++;
			dp[_n][x] = 1;
		} while (x != u);
	}
}

void prerequites() {
	for (int i = 1; i <= n; i++) if (!dfn[i]) tarjan(i);
	for (int u = 1; u <= n; u++) {
		for (int e = hd[u]; e; e = nxt[e]) {
			int v = to[e];
			if (scc[v] != scc[u]) {
				add2(scc[u], scc[v]);
			}
		}
	}
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		char s[N];
		scanf("%s", s + 1);
		for (int j = 1; j <= n; j++) {
			if (s[j] - '0') add(j, i);
		}
	}
	prerequites();
	topological_sort();
	printf("%d\n", ans);
	return 0;
}