#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <ctime>
#define inf (long long)100000000
using namespace std;
struct node {
	int to; int next; int len;
}; node edge[500010], bian[2000010];
int in[200010], out[200010], dep[200010], f[200010][21], root;
int tim = 0, fir[200010], first[200010], n, a, b, m, Q, stack[200010];
int sum = 0, Size = 0, len, top, list[200010], que[200010];
long long Dp[200010][3];
bool instack[200010], mark[200010];
bool comp(const int &x, const int &y) {return in[x] < in[y];}
bool check(int x, int y) {return in[x] <= in[y] && out[x] >= out[y];}
void add(int x, int y) {
	edge[++sum].to = y;
	edge[sum].next = fir[x];
	fir[x] = sum;
}
void insert(int x, int y, int z) {
	bian[++Size].to = y;
	bian[Size].next = first[x];
	first[x] = Size;
	bian[Size].len = z;
}
void dfs(int x, int depth, int Anc) {
	dep[x] = depth;
	f[x][0] = Anc;
	in[x] = ++tim;
	for (int i = 1; i <= 20; i ++)
		f[x][i] = f[f[x][i - 1]][i - 1];
	for (int u = fir[x]; u; u = edge[u].next)
		if (dep[edge[u].to] == 0)
			dfs(edge[u].to, depth + 1, x);
	out[x] = ++tim;
}
int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);
	for (int i = 20; i >= 0; i --)
		if (dep[f[x][i]] >= dep[y])
			x = f[x][i];
	if (x == y) return x;
	for (int i = 20; i >= 0; i --)
		if (f[x][i] != f[y][i])
			x = f[x][i], y = f[y][i];
	return f[x][0];
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n - 1; i ++) {
		scanf("%d%d", &a, &b);
		add(a, b);
		add(b, a);
	}
	dfs(1, 1, 1);
	scanf("%d", &Q);
	while (Q --) {
		scanf("%d", &m); len = m; top = 0; root = 0;
		for (int i = 1; i <= m; i ++) scanf("%d", &list[i]), que[i] = list[i];
		sort(list + 1, list + m + 1, comp);
		for (int i = 1; i < m; i ++)
			list[++len] = lca(list[i], list[i + 1]);
		sort(list + 1, list + len + 1, comp);
		len = unique(list + 1, list + len + 1) - list - 1;
		for (int i = 1; i <= len; i ++) {
			while (top > 0 && !check(stack[top], list[i]))
				top --;
			if (stack[top] == 0) root = list[i];
			else {
				int s = stack[top], t = list[i];
				insert(s, t, dep[t] - dep[s]);
			}
			stack[++top] = list[i];
		}
		for (int i = 1; i <= len; i ++) instack[list[i]] = true;
		for (int i = 1; i <= m; i ++) mark[que[i]] = true;
		for (int i = 1; i <= len; i ++) instack[list[i]] = false;
		for (int i = 1; i <= m; i ++) mark[que[i]] = false;
		for (int i = 1; i <= len; i ++) first[list[i]] = 0;
		Size = 0;
	}
	return 0;
}