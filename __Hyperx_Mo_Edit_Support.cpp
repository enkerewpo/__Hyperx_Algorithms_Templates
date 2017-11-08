#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 1000000 + 5
#define M 1000000 + 5
using namespace std;
#define int long long
int n, m, block;
int a[N], tmp[N], ans[M];

int qcnt;
struct query {
	query() {}
	query(int _l, int _r, int _d, int _i) : l(_l), r(_r), dfn(_d), id(_i) {}
	int l, r, dfn, id;
	bool operator < (const query &rhs) const {
		return (l / block) == (rhs.l / block) ? (r == rhs.r ? dfn < rhs.dfn : r < rhs.r) : l / block < rhs.l / block;
	}
	
} q[M];


int ccnt;
struct change {
	change() {}
	change(int _p, int _v, int _pr) : pos(_p), val(_v), pre(_pr) {}
	int pos, val, pre;
	
} c[M];

int cnt[N], tot;
int L, R, DFN;

void add(int p) { tot += (++cnt[p]) == 1; }
void del(int p) { tot -= (--cnt[p]) == 0; }
void rev(int p, int v) {
	if(L <= p && p <= R) add(v), del(a[p]);
	a[p] = v; 
}

void mo() {
	for(int i = 1; i <= qcnt; i++) {
		while(DFN < q[i].dfn) DFN++, rev(c[DFN].pos, c[DFN].val);
		while(DFN > q[i].dfn) rev(c[DFN].pos, c[DFN].pre), DFN--;
		while(R < q[i].r) R++, add(a[R]);
		while(R > q[i].r) del(a[R]), R--;
		while(L < q[i].l) del(a[L]), L++;
		while(L > q[i].l) L--, add(a[L]);
		ans[q[i].id] = tot;
	}
}

signed main() {
	scanf("%lld%lld", &n, &m);
	block = sqrt(n);
	for(int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		tmp[i] = a[i];
	}
	int a, b;
	for(int i = 1; i <= m; i++) {
		char op[3];
		scanf("%s%lld%lld", op, &a, &b);
		if(op[0] == 'Q') qcnt++, q[qcnt] = query(a, b, ccnt, qcnt);
		else c[++ccnt] = change(a, b, tmp[a]), tmp[a] = b;
	}
	sort(q + 1,q + qcnt + 1);
	mo();
	for(int i = 1; i <= qcnt; i++) printf("%lld\n", ans[i]);
	return 0;
}