#include <bits/stdc++.h>
using namespace std;
#define N 1000 + 5
#define INF 0x7f7f7f7f
#define M 100000 + 5
int hd[N], nxt[2 * M], f[2 * M], to[2 * M], tot = 1;

int S, T;

void add(int a, int b, int c)
{
	nxt[++tot] = hd[a], to[hd[a] = tot] = b, f[tot] = c;
	nxt[++tot] = hd[b], to[hd[b] = tot] = a, f[tot] = 0;
}

int dis[N];
int que[N];

bool check()
{
	memset(dis, -1, sizeof dis);
	int head = 0, tail = -1;
	dis[que[++tail] = S] = 0;
	while (head <= tail) {
		int u = que[head++];
		for (int e = hd[u]; e; e = nxt[e]) {
			int v = to[e];
			if (dis[v] == -1 && f[e])
				dis[que[++tail] = v] = dis[u] + 1;
		}
	}
	return dis[T] != -1;
}

int argument(int u, int rem)
{
	if (u == T) return rem;
	int cnt = 0;
	for (int e = hd[u]; e && rem > cnt; e = nxt[e]) {
		int v = to[e];
		if (dis[u] + 1 == dis[v] && f[e]) {
			int ret = argument(v, min(rem - cnt, f[e]));
			f[e] -= ret;
			f[e ^ 1] += ret;
			cnt += ret;
		}
	}
	if (!cnt) dis[u] = -1;
	return cnt;
}

int dinic()
{
	int cnt = 0, tmp;
	while (check())
		while (tmp = argument(S, INF))
			cnt += tmp;
	return cnt;
}

int main()
{
	return 0;
}