#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 100000;

struct point {
	int nxt[26];
	int fail, cnt;
} a[maxn];

int cnt, root;
int que[maxn], head, tail;
char A[maxn];

inline void insert(char* s) {
	int now = root;
	for (int i = 0; s[i] != '\0'; ++i) {
		int x = s[i] - 'a';
		if (a[now].nxt[x] == 0) a[now].nxt[x] = cnt++;
		now = a[now].nxt[x];
	}
	return;
}

inline void build() {
	for (int i = 0; i < 26; ++i)  {
		if (a[root].nxt[i] != 0) {
			int p = a[root].nxt[i];
			a[p].fail = root;
			que[tail++] = p;
		}
	}
	while (head < tail) {
		int p = que[head++];
		for (int i = 0; i < 26; ++i) if (a[p].nxt[i]) {
				int x = a[p].nxt[i];
				int j = a[p].fail;
				while (j != root && a[j].nxt[i] == 0) j = a[j].fail;
				if (a[j].nxt[i]) j = a[j].nxt[i];
				a[x].fail = j;
				que[tail++] = x;
			}
	}
	return;
}

inline void solve(char* s) {
	int now = root;
	for (int i = 0; s[i] != '\0'; ++i) {
		int x = s[i] - 'a';
		while (now != root && a[now].nxt[x] == 0) now = a[now].fail;
		if (a[now].nxt[x]) now = a[now].nxt[x];
		++a[now].cnt;
	}
	for (int i = tail - 1; i >= 0; --i) {
		int p = a[que[i]].fail;
		a[p].cnt += a[que[i]].cnt;
	}
	return;
}

int main() {
	int n;
	cnt = 2;
	root = 1;
	scanf("%d", &n);
	while (n--) scanf("%s", A), insert(A);
	build();
	scanf("%s", A);
	solve(A);
	printf("%d", a[2].cnt);
	return 0;
}