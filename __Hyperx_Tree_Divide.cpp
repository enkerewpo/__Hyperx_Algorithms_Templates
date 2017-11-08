#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define N 1000 + 5
using namespace std;
vector<int> _v[N];
int stack[N], top = -1;
int n, b;
int color[N], capital[N], cnt;

void dfs(int u, int fa) {
	int limit = top;
	vector<int>::iterator i;
	for (i = _v[u].begin(); i != _v[u].end(); i++) {
		int v = *i;
		if (v != fa) {
			dfs(v, u);
			if (top - limit >= b) {
				capital[++cnt] = u;
				while (top != limit) color[stack[top--]] = cnt;
			}
		}
	}
	stack[++top] = u;
}

int main() {
	scanf("%d%d", &n, &b);
	for (int i = 1; i < n; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		_v[a].push_back(b);
		_v[b].push_back(a);
	}
	dfs(1, 0);
	while (top >= 0) color[stack[top--]] = cnt;
	printf("%d\n", cnt);
	for (int i = 1; i <= n; i++) printf("%d ", color[i]);
	puts("");
	for (int i = 1; i <= cnt; i++) printf("%d ", capital[i]);
	puts("");
	return 0;
}