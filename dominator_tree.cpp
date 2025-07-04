struct DominatorTree {
  ll n;
  vector<vector<ll>> adj, rev, children, bucket;
  vector<ll> sdom, label, vertex, dom;
  vector<ll> parent, path_label;
  DominatorTree(ll nn) {
    n = nn;
    adj.resize(n, vector<ll>());
    rev.resize(n, vector<ll>());
    children.resize(n, vector<ll>());
    bucket.resize(n, vector<ll>());
    sdom.resize(n, 0LL);
    label.resize(n, 0LL);
    vertex.resize(n+1, 0LL);
    dom.resize(n, 0LL);
    parent.resize(n, 0LL);
    path_label.resize(n, 0LL);
  }
  
  ll find(ll u) {
    if (parent[u] == u) return path_label[u];
    ll v = find(parent[u]);
    parent[u] = parent[parent[u]];
    if (sdom[v] < sdom[path_label[u]]) path_label[u] = v;
    return path_label[u];
  }
  
  void dfs(ll nd, ll &tm) {
    label[nd] = ++tm;
    vertex[tm] = nd;
    for (auto child: adj[nd]) {
      if (!label[child]) {
        children[nd].push_back(child);
        dfs(child, tm);
      }
    }
  }
  
  vector<ll> build(ll s) {
    ll tm = 0LL;
    dfs(s, tm);
    for (ll i = 0; i < n; i++) parent[i] = path_label[i] = i, sdom[i] = label[i];
    
    for (ll i = n; i >= 1; i--) {
      ll u = vertex[i];
      for (auto w: rev[u]) sdom[u] = min(sdom[u], sdom[find(w)]);
      if (i > 1) bucket[vertex[sdom[u]]].push_back(u);
      for (auto w: bucket[u]) {
        ll v = find(w);
        if (sdom[v] < sdom[w]) dom[w] = v;
        else dom[w] = u;
      }
      for (auto w: children[u]) parent[w] = u;
    }
    
    for (ll i = 1; i <= n; i++) {
      ll u = vertex[i];
      if (dom[u] != vertex[sdom[u]]) dom[u] = dom[dom[u]];
    }
    return dom;
  }
  
  void add_edge(ll from, ll to) {
    adj[from].push_back(to);
    rev[to].push_back(from);
  }
};
