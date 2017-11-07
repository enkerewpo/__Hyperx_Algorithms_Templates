#include <bits/stdc++.h>
#define N 10000000 + 5
using namespace std;

typedef long long ll;
ll ans;
char str[N], t[N];

ll nxt[N];
int main() {
	scanf("%s", t + 1);
	scanf("%s", str + 1);
	int lent = strlen(t + 1);
	int lenstr = strlen(str + 1);
	int j = 0;
	nxt[1] = 0;
	for (int i = 2; i <= lent; i++) {
		while (j > 0 && t[i] != t[j + 1]) j = nxt[j];
		if (t[j + 1] == t[i]) j++;
		nxt[i] = j;
	}
	j = 0;
	for (int i = 1; i <= lenstr; i++) {
		while (j > 0 && str[i] != t[j + 1]) j = nxt[j];
		if (t[j + 1] == str[i]) j++;
		if (j == lent) {

			ans++;
			j = nxt[j];
		}
	}
	printf("%lld\n", ans);
	return 0;
}
/*
abcab
acacabcabcabcab
 */