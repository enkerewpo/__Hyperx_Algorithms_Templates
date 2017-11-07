#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
#include <stack>
using namespace std;

const int maxn = 1000;

struct Edge {// structure of the side of the stack
	int u, v;
	Edge(int uu, int vv) {
		u = uu;
		v = vv;
	}
};
stack <Edge> s;

struct edge {// The edge structure of the chained forward starburst
	int v, next;
} edges[maxn];

int n, m; // The number of nodes, the number of undirected edges
int e, head[maxn];
int pre[maxn]; // The timestamp of the first visit
int dfs_clock; // timestamp
int iscut[maxn]; // mark whether the node is cut top
int bcc_cnt; // dot_ The number of double connected components
int bccno[maxn]; // The point to which the node belongs _ The number of the dual connected component
vector <int> bcc[maxn]; // dot_double connected component

void addedges(int u, int v) {// Add edge
	edges[e].v = v;
	edges[e].next = head[u];
	head[u] = e ++;
	edges[e].v = u;
	edges[e].next = head[v];
	head[v] = e ++;
}

int dfs(int u, int fa) {
	int lowu = pre[u] = ++ dfs_clock;
	int child = 0;
	for (int i = head[u]; i != -1; i = edges[i].next) {
		int v = edges[i].v;
		Edge e = (Edge) {u, v};
		if (! pre[v]) {
			s.push(e);
			child ++;
			int lowv = dfs(v, u);
			lowu = min(lowu, lowv); // Update lowu with descendants
			if (lowv >= pre[u]) { // Find a subtree that satisfies the condition of the cut
				iscut[u] = 1;
				bcc_cnt ++;
				bcc[bcc_cnt].clear();
				for (;;) { // save the bcc information
					Edge x = s.top(); s.pop();
					if (bccno[x.u] != bcc_cnt) {bcc[bcc_cnt].push_back(x.u); bccno[x.u] = bcc_cnt;}
					if (bccno[x.v] != bcc_cnt) {bcc[bcc_cnt].push_back(x.v); bccno[x.v] = bcc_cnt;}
					if (x.u == u && x.v == v) break;

				}
			}
		} else if (pre[v] < pre[u] && v != fa) { // Update lowu
			s.push(e);
			lowu = min(lowu, pre[v]);
		}
	}
	if (fa < 0 && child == 1) iscut[u] = 0; // If the root node has only one subtree then it is not a cut
	return lowu;
}

void init() {
	memset(pre, 0, sizeof(pre));
	memset(iscut, 0, sizeof(iscut));
	memset(head, -1, sizeof(head));
	memset(bccno, 0, sizeof(bccno));
	e = 0; dfs_clock = 0; bcc_cnt = 0;
}

int main() {
	int u, v;
	while (scanf("%d%d", &n, &m) != EOF) {
		init();
		for (int i = 0; i < m; i ++) {
			scanf("%d%d", &u, &v);
			addedges(u, v);
		}
		dfs(1, -1);
		for (int i = 1; i <= bcc_cnt; i ++) {
			for (int j = 0; j < (int)bcc[i].size(); j ++)
				cout << bcc[i][j] << "";
			cout << endl;
		}
	}
	return 0;
}