#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#define N 10000
#define M 10000 + 5
using namespace std;

int T, n, m, x;
vector<int> V[N];

void init() {
	tot = 0;
	tim = 0;
	memset(dfn, 0, sizeof dfn);
	memset(vis, 0, sizeof vis);
	memset(scc, 0, sizeof scc);
	memset(low, 0, sizeof low);
	while (!s.empty()) s.pop();
	for (int i = 0; i <= 2 * n + 1; i++) V[i].clear();
}

int main() {
	scanf("%d", &T);
	while (T--) {
		init();
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			int a, b;
			char op1, op2;
			scanf("%*c%c%d %c%d", &op1, &a, &op2, &b);
			a <<= 1; if (op1 == 'h') a |= 1;
			b <<= 1; if (op2 == 'h') b |= 1;
			V[a ^ 1].push_back(b);
			V[b ^ 1].push_back(a);
		}
		for (int i = 2; i <= 2 * n + 1; i++) if (!dfn[i]) tarjan(i);
		bool f = true;
		for (int i = 1; i <= n; i++) {
			if (scc[i << 1] == scc[i << 1 | 1]) {
				f = false;
				break;
			}
		}
		if (f) puts("GOOD");
		else puts("BAD");
	}
	return 0;
}