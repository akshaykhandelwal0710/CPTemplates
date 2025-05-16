    ll n; // graph ka size
    vector<vector<ll>> adj(n, vector<ll>()), rev_adj(n, vector<ll>()); // directed graph ka edges
    vector<ll> tour;
    vector<ll> co(n, 0); // nodes ka component number
    vector<vector<ll>> comp_adj(n, vector<ll>()); // components ka adjacency list
    function<void(ll)> dfs = [&](ll nd)->void {
        vis[nd] = true;
        for (auto &ele: adj[nd]) if (!vis[ele]) dfs(ele);
        tour.push_back(nd);
    };
    ll cur;
    function<void(ll)> dfs1 = [&](ll nd)->void {
        co[nd] = cur;
        vis[nd] = true;
        for (auto &ele: rev_adj[nd]) {
            if (!vis[ele]) dfs1(ele);
        }
    };
    auto kosaraju = [&]()->void {
        for (ll i = 0; i < n; i++) vis[i] = false;
        tour.clear();
        for (ll i = 0; i < n; i++) if (!vis[i]) dfs(i);
        reverse(tour.begin(), tour.end());
        for (ll i = 0; i < n; i++) vis[i] = false;
        cur = 0;
        for (auto &ele: tour) if (!vis[ele]) {
            dfs1(ele);
            cur++;
        }
        for (ll i = 0; i < cur; i++) comp_adj[i].clear();
        for (ll i = 0; i < n; i++) {
            for (auto &ele: rev_adj[i]) if (co[ele] != co[i]){
                comp_adj[co[ele]].push_back(co[i]);
            }
        }
    };
