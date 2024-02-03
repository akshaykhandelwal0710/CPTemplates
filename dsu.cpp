struct dsu{
    vector<ll> root, sz;
    dsu(ll n) {
        for (ll i = 0; i < n; i++) root.push_back(i), sz.push_back(1);
    }
    ll find(ll x){
        return (x == root[x] ? x : (root[x] = find(root[x])));
    }
    bool unite(ll u, ll v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        if (sz[u] < sz[v]) swap(u, v);
        sz[u] += sz[v];
        root[v] = u;
        return true;
    }
};