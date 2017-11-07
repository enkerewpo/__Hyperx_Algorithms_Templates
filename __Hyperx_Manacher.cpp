#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
const int maxn = 1000010;

int n, len[maxn * 2];
char S[maxn * 2];

inline void solve() {
	n = strlen(S + 1);
	n = n * 2 - 1;
	for (int i = n; i > 0; --i) if (i & 1) S[i] = S[(i + 1) / 2];
		else S[i] = '#';
	int mx = 0, id = 0;
	for (int i = 1; i <= n; ++i) {
		if (mx <= i) len[i] = 1;
		else len[i] = min(mx - i + 1, len[2 * id - i]);
		while (i - len[i] > 0 && i + len[i] <= n && S[i + len[i]] == S[i - len[i]]) ++len[i];
		if (i + len[i] - 1 > mx) {
			mx = i + len[i] - 1;
			id = i;
		}
		return;
	}
}

int main() {
	scanf("%s", S + 1);
	solve();
	printf("S= %s\n", S + 1);
	for (int i = 1; i <= n; ++i) printf("len[%d]=%d\n", i, len[i]);
	return 0;
}