#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>
using namespace std;

const int maxn = 1000;
struct Edge {
	int no, v, next; // no: Number of the edge
} edges[maxn];

int n, m, ebcnum; // number of nodes, number of undirected edges, number of edges_double connected components
int e, head[maxn];
int pre[maxn]; // The timestamp of the first visit
int dfs_clock; // timestamp
int isbridge[maxn]; // mark if the edge is a bridge
vector <int> ebc[maxn]; // Edge_double connected component

void addedges(int num, int u, int v) {// Add edge
	edges[e].no = num;
	edges[e].v = v;
	edges[e].next = head[u];
	head[u] = e++;
	edges[e].no = num++;
	edges[e].v = u;
	edges[e].next = head[v];
	head[v] = e++;
}

int dfs_findbridge(int u, int fa) {// Find all the bridges
	int lowu = pre[u] = ++dfs_clock;
	for (int i = head[u]; i != -1; i = edges[i].next) {
		int v = edges[i].v;
		if (! pre[v]) {
			int lowv = dfs_findbridge(v, u);
			lowu = min(lowu, lowv);
			if (lowv > pre[u]) {
				isbridge[edges[i].no] = 1; // bridge
			}
		} else if (pre[v] < pre[u] && v != fa) {
			lowu = min(lowu, pre[v]);
		}
	}
	return lowu;
}

void dfs_coutbridge(int u, int fa) {// Saves the information of the edge_double connected component
	ebc[ebcnum].push_back(u);
	pre[u] = ++dfs_clock;
	for (int i = head[u]; i != -1; i = edges[i].next) {
		int v = edges[i].v;
		if (! isbridge[edges[i].no] && ! pre[v]) dfs_coutbridge(v, u);
	}
}

void init() {
	memset(pre, 0, sizeof(pre));
	memset(isbridge, 0, sizeof(isbridge));
	memset(head, -1, sizeof(head));
	e = 0; ebcnum = 0;
}

int main() {
	int u, v;
	while (scanf("%d%d", &n, &m) != EOF) {
		init();
		for (int i = 0; i < m; i++) {
			scanf("%d%d", &u, &v);
			addedges(i, u, v);
		}
		dfs_findbridge(1, -1);
		memset(pre, 0, sizeof(pre));
		for (int i = 1; i <= n; i++) {
			if (! pre[i]) {
				ebc[ebcnum].clear();
				dfs_coutbridge(i, -1);
				ebcnum++;
			}
		}
		for (int i = 0; i < ebcnum; i++) {
			for (int j = 0; j < (int)ebc[i].size(); j++)
				cout << ebc[i][j] << " ";
			cout << endl;
		}
	}
	return 0;
}