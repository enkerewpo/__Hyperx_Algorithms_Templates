#include <bits/stdc++.h>
using namespace std;
int dep[10], fa[10][10];
int lca(int x, int y)
{
	if(dep[x] < dep[y]) swap(x, y);
	int d = dep[x] - dep[y];
	for(int i = 0; i <= 18; i++) {
		if(d & (1 << i)) x = fa[x][i];
	}
	for(int i = 18; i >= 0; i--) {
		if(fa[x][i] != fa[y][i]) {
			x = fa[x][i], y = fa[y][i];
		}
	}
	if(x == y) return x;
	else return fa[x][0];
}

int main() {
	return 0;
}