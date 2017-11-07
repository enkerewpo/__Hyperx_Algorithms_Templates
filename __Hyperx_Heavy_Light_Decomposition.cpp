#include <bits/stdc++.h>
using namespace std;

#define N 30000 + 5
#define inf 0x7f7f7f7f

int n, q, hd[N], nxt[N], to[N], w[N], edge, tot;
int siz[N], dep[N], u_son[N], fa[N], top[N], tr[N], dtr[N];

namespace segtree {

int TR[4 * N], MAX[4 * N];

void up(int p) {
	TR[p] = TR[p << 1] + TR[p << 1 | 1];
	MAX[p] = max(MAX[p << 1], MAX[p << 1 | 1]);
}

void build(int l, int r, int p) {
	if (l == r) {
		TR[p] = w[dtr[l]];
		MAX[p] = TR[p];
		return;
	}
	int mid = (l + r) / 2;
	build(l, mid , p << 1);
	build(mid + 1, r, p << 1 | 1);
	up(p);
}

void change(int l, int r, int P, int val, int p) {
	if (l == r && l == P) {
		TR[p] = val;
		MAX[p] = TR[p];
		return;
	}
	int mid = (l + r) / 2;
	if (P <= mid) change(l, mid, P, val, p << 1);
	else change(mid + 1, r, P, val, p << 1 | 1);
	up(p);
}

int ask_max(int l, int r, int L, int R, int p) {
	if (l > R || r < L) return -inf;
	if (L <= l && r <= R) return MAX[p];
	int mid = (l + r) / 2;
	return max(ask_max(l, mid, L, R, p << 1), ask_max(mid + 1, r, L, R, p << 1 | 1));
}

int ask_sum(int l, int r, int L, int R, int p) {
	if (l > R || r < L) return 0;
	if (L <= l && r <= R) return TR[p];
	int mid = (l + r) / 2;
	return ask_sum(l, mid, L, R, p << 1) + ask_sum(mid + 1, r, L, R, p << 1 | 1);
}

}

namespace HLD {

void add(int a, int b) {
	nxt[++edge] = hd[a], to[edge] = b, hd[a] = edge;
	nxt[++edge] = hd[b], to[edge] = a, hd[b] = edge;
}

void dfs1(int u, int __fa, int __dep) {
	fa[u] = __fa;
	dep[u] = __dep;
	siz[u] = 1;
	for (int c = hd[u]; c; c = nxt[c]) {
		int v = to[c];
		if (v != __fa) {
			dfs1(v, u, __dep + 1);
			siz[u] += siz[v];
			if (!u_son[u] || siz[v] > siz[u_son[u]]) u_son[u] = v;
		}
	}
}

void dfs2(int u, int id) {
	top[u] = id;
	tr[u] = ++tot;
	dtr[tot] = u;
	if (!u_son[u]) return;
	dfs2(u_son[u], id);
	for (int c = hd[u]; c; c = nxt[c]) {
		int v = to[c];
		if (v != u_son[u] && v != fa[u]) dfs2(v, v);
	}
}

int max(int a, int b) {
	int f1, f2, ret = -inf;
	f1 = top[a];
	f2 = top[b];
	while (f1 != f2) {
		if (dep[f1] < dep[f2]) swap(a, b), swap(f1, f2);
		ret = std::max(ret, segtree::ask_max(1, n, tr[f1], tr[a], 1));
		a = fa[f1];
		f1 = top[a];
	}
	if (dep[a] < dep[b]) swap(a, b);
	ret = std::max(ret, segtree::ask_max(1, n, tr[b], tr[a], 1));
	return ret;
}

int sum(int a, int b) {
	int f1, f2, ret = 0;
	f1 = top[a];
	f2 = top[b];
	while (f1 != f2) {
		if (dep[f1] < dep[f2]) swap(a, b), swap(f1, f2);
		ret += segtree::ask_sum(1, n, tr[f1], tr[a], 1);
		a = fa[f1];
		f1 = top[a];
	}
	if (dep[a] < dep[b]) swap(a, b);
	ret += segtree::ask_sum(1, n, tr[b], tr[a], 1);
	return ret;
}

}

int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		HLD::add(a, b);
	}
	HLD::dfs1(1, 0, 1);
	HLD::dfs2(1, 1);
	for (int i = 1; i <= n; i++) scanf("%d", &w[i]);
	segtree::build(1, n, 1);
	scanf("%d", &q);
	while (q--) {
		string op;
		cin >> op;
		int a, b;
		scanf("%d%d", &a, &b);
		if      (op == "QMAX")     printf("%d\n", HLD::max(a, b));
		else if (op == "QSUM")     printf("%d\n", HLD::sum(a, b));
		else                       segtree::change(1, n, tr[a], b, 1);
	}
	return 0;
}