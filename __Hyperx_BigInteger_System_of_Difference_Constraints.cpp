#include <algorithm>
#include <cstring>
#include <cstdio>
#include <queue>
#include <cassert>

#define N 200005 + 5
#define inf 1e9
using namespace std;
#define int long long

int hd[2 * N], nxt[2 * N], to[2 * N], w[2 * N], tot;
int n, k;
void add(int a, int b, int c) {
	nxt[++tot] = hd[a], to[hd[a] = tot] = b, w[tot] = c;
}

int dis[4 * N];
int cnt[4 * N];
bool vis[4 * N];

int spfa() {
	memset(dis, -inf, sizeof dis);
	queue<int> q;
	q.push(0);
	vis[0] = true;
	dis[0] = 0;
	cnt[0]++;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (cnt[u] == n + 1) return false;
		vis[u] = false;
		for (int e = hd[u]; e != -1; e = nxt[e]) {
			int v = to[e];
			if (dis[u] + w[e] > dis[v]) {
				dis[v] = dis[u] + w[e];
				if (!vis[v]) {
					q.push(v);
					cnt[v]++;
					vis[v] = true;
				}
			}
		}
	}
	return true;
}

signed main() {
	memset(hd, -1, sizeof hd);
	scanf("%lld%lld", &n, &k);
	while (k--) {
		int x, a, b;
		scanf("%lld%lld%lld", &x, &a, &b);
		switch (x) {
		case 1 : { add(a, b, 0), add(b, a, 0); break;}                           //  A   =   B
		case 2 : { if (a == b) return puts("-1"), 0; else add(a, b, 1); break;}  //  A   <   B
		case 3 : { add(b, a, 0); break;}										 //  A   >=  B
		case 4 : { if (a == b) return puts("-1"), 0; else add(b, a, 1); break;}  //  A   >   B
		case 5 : { add(a, b, 0); break;}										 //  A   <=  B
		}
	}
	for (int i = n; i >= 1; i--) add(0, i, 1);
	if (spfa()) {
		int ans = 0;
		for (int i = 1; i <= n; i++) ans += dis[i];
		printf("%lld\n", ans);
	} else puts("-1");
	return 0;
}