vector<bool> stop(n, false), flag(n, false);
vector<ll> dpth(n, 0), sub(n, 0);
auto centroid_decomposition = [&](auto &&centroid_decomposition, ll root)->void {
    ll m = 0;
    auto sz_dfs = [&](auto &&sz_dfs, ll p, ll c)->void {
        ++m;
        sub[c] = 1;
        for (auto &ele: adj[c]) {
            if (ele != p && !stop[ele]) {
                sz_dfs(sz_dfs, c, ele);
                sub[c] += sub[ele];
            }
        }
    };
    sz_dfs(sz_dfs, -1, root);
    ll centroid = root;
    auto find_centroid = [&](auto &&find_centroid, ll p, ll c)->void {
        flag[c] = (m-sub[c]<=m/2);
        for (auto &ele: adj[c]) {
            if (ele != p && !stop[ele]) {
                if (sub[ele]>m/2) flag[c] = false;
                find_centroid(find_centroid, c, ele);
            }
        }
        if (flag[c]) centroid = c;
    };
    find_centroid(find_centroid, -1, root);
    // do what you want

    stop[centroid] = true;
    for (auto &ele: adj[centroid]) if (!stop[ele]){
        centroid_decomposition(centroid_decomposition, ele);
    }
};