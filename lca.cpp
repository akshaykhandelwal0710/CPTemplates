int rt = 0;
const int M = 20;
vector<vector<int>> par(n, vector<int>(M, 0));
vector<int> dpth(n, 0);
function<void(int, int)> par_dfs = [&](int p, int c)->void {
    for (auto &ele: adj[c]) if (ele != p) {
        dpth[ele] = dpth[c]+1;
        par[ele][0] = c;
        for (int i = 1; i < M; i++) par[ele][i] = par[par[ele][i-1]][i-1];
        par_dfs(c, ele);
    }
};
par_dfs(-1, rt);
auto get_par = [&](int u, int k)->int {
    for (int i = 0; i < M; i++) if ((1<<i)&k) u = par[u][i];
    return u;
};
auto lca = [&](int u, int v)->ll {
    if (dpth[u] > dpth[v]) swap(u, v);
    int k = dpth[v]-dpth[u];
    v = get_par(v, k);
    if (u == v) return u;
    for (int i = M-1; i >= 0; i--) if (par[u][i] != par[v][i]) u = par[u][i], v = par[v][i];
    return par[u][0];
};