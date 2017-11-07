// BZOJ 1991
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <cmath>
#define slope_optimize
using namespace std;
#define N 1000000 + 5
typedef long long ll;
#define int ll
int n;
ll a, b, c;
ll A[N], S[N], dp[N];
struct point {
	point() {}
	point(int _, int __) : x(_), y(__) {}
	point(int _, int __, int ___) : x(_), y(__), id(___) {}
	int x, y, id;
};
template <typename _Tp>
void read(_Tp &a, char c = 0, int op = 1) {
	for (c = getchar(); !isdigit(c); c = getchar()) c == '-' ? op = -1 : op = 1;
	for (a = 0; isdigit(c); a = a * 10 + c - '0', c = getchar());
	a *= op;
}
double slp(point a, point b) { return double(b.y - a.y) / double(b.x - a.x); }
ll w(int x, int y) { ll s = S[y] - S[x - 1]; return a * s * s + b * s + c; }
point q[N];
int l, r;
signed main() {
	read(n), read(a), read(b), read(c);
	for (int i = 1; i <= n; i++) read(A[i]), S[i] = S[i - 1] + A[i];
	slope_optimize {
		for (int i = 1; i <= n; i++) {
			double k = S[i];
			while (l < r && slp(q[l], q[l + 1]) < k) l++;
			point bst = q[l];
			dp[i] = dp[bst.id] + w(bst.id + 1, i);
			point now = point(2 * a * S[i], dp[i] + a * S[i] * S[i] - b * S[i], i);
			while (l < r && slp(q[r], now) < slp(q[r - 1], q[r])) r--;
			q[++r] = now;
		}
	}
	printf("%lld\n", dp[n]);
	return 0;

}