bool hungary(int u) {
    for (it = _v[u].begin(); it != _v[u].end(); it++) {
        int v = *it;
        if (!vis[v]) {
            vis[v] = true;
            if (!fa[v] || hungary(fa[v])) {
                fa[v] = u;
                return true;
            }
        }
    }
    return false;
}

int main() {
    for (int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof vis);
        hungary(i);
    }
    return 0;
}