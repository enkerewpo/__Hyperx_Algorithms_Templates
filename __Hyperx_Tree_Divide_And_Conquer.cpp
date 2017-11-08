#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define M 20200
using namespace std;
struct node {
    int to, f, nxt;
    bool ban;
} e[M << 1];
int head[M], tot = 1;
int n, ans;
int Siz[M];
void add(int x, int y, int z) {
    e[++tot].to = y;
    e[tot].f = z;
    e[tot].nxt = head[x];
    head[x] = tot;
}
void get_center(int x, int from, int Size, int &cg) {
    int i; Siz[x] = 1;
    bool flag = 1;
    for (i = head[x]; i; i = e[i].nxt) {
        if (e[i].ban || e[i].to == from) continue;
        get_center(e[i].to, x, Size, cg);
        if (Siz[e[i].to] > Size >> 1)
            flag = 0;
        Siz[x] += Siz[e[i].to];
    }
    if (Size - Siz[x] > Size >> 1) flag = 0;
    if (flag) cg = x;
}
void dfs(int x, int from, int dis, int cnt[]) {
    int i;
    Siz[x] = 1;
    cnt[dis]++;
    for (i = head[x]; i; i = e[i].nxt) {
        if (e[i].ban || e[i].to == from)
            continue;
        dfs(e[i].to, x, (dis + e[i].f) % 3, cnt);
        Siz[x] += Siz[e[i].to];
    }
}
void clac(int x) {
    int i;
    int cnt[3] = {1, 0, 0};
    for (i = head[x]; i; i = e[i].nxt) {
        if (e[i].ban) continue;
        int _cnt[3] = {0};
        dfs(e[i].to, x, e[i].f, _cnt);
        ans += cnt[0] * _cnt[0];
        ans += cnt[1] * _cnt[2];
        ans += cnt[2] * _cnt[1];
        cnt[0] += _cnt[0];
        cnt[1] += _cnt[1];
        cnt[2] += _cnt[2];
    }
}
void divide_and_conquer(int root, int Size) {
    int i, cg;
    if (Size == 1) return;
    get_center(root, 0, Size, cg);
    clac(cg);
    for (i = head[cg]; i; i = e[i].nxt) {
        if (e[i].ban)
            continue;
        e[i].ban = e[i ^ 1].ban = 1;
        divide_and_conquer(e[i].to, Siz[e[i].to]);
    }
}

int main() {
    int i, x, y, z;
    cin >> n;
    for (i = 1; i < n; i++) {
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z % 3);
        add(y, x, z % 3);
    }
    divide_and_conquer((1 + n) >> 1, n);
    ans = ans * 2 + n;
    int gcd = __gcd(ans, n * n);
    cout << ans / gcd << '/' << n*n / gcd << endl;
}