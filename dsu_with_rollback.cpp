struct dsu{
    vector<ll> root, sz;
    vector<pair<ll, ll>> ops;
    ll comps;
    dsu(ll n) {
        for (ll i = 0; i < n; i++) root.push_back(i), sz.push_back(1);
        comps = n;
    }
    ll find(ll x){
        return (x == root[x] ? x : find(root[x]));
    }
    bool unite(ll u, ll v){
        u = find(u), v = find(v);
        if (u == v) {
            ops.push_back({-1, -1});
            return false;
        }
        if (sz[u] < sz[v]) swap(u, v);
        sz[u] += sz[v];
        root[v] = u;
        ops.push_back({u, v});
        --comps;
        return true;
    }
    void rollback() {
        auto [u, v] = ops.back();
        ops.pop_back();
        if (u == -1) return;
        ++comps;
        root[v] = v;
        sz[u] -= sz[v];
    }
};
