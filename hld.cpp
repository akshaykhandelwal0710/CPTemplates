// do not forget to construct
// n length ka segtree banao path query ke liye (in[h_num[c]] to in[c] ka range query karo)
const ll N = 2e5;
vector<ll> adj[N];
ll baap[N], h_num[N], dpth[N], sub[N], in[N], out[N];
struct hld{
    ll n;
    hld(ll n): n(n) {
        for (ll i = 0; i < n; i++) {
            adj[i].clear();
            baap[i] = h_num[i] = -1;
            dpth[i] = 0;
        }
    }
    void add_edge(ll u, ll v){
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void construct(ll root) {
        function<void(ll, ll)> dfs = [&](ll p, ll c)->void {
            baap[c] = p;
            sub[c] = 1LL;
            if (adj[c][0] == p && adj[c].size() > 1) swap(adj[c][0], adj[c][1]);
            for (auto &ele: adj[c]) if (ele != p) {
                    dpth[ele] = dpth[c]+1;
                    dfs(c, ele);
                    sub[c] += sub[ele];
                    if (sub[ele] > sub[adj[c][0]]) swap(ele, adj[c][0]);
                }
        };
        dfs(-1, root);
        ll cur = 0;
        function<void(ll, ll)> dfs1 = [&](ll p, ll c)->void {
            in[c] = cur++;
            for (auto &ele: adj[c]) if (ele != p) {
                    if (sub[ele] > (sub[c]-1) / 2) {
                        if (h_num[c] == -1) h_num[c] = c;
                        h_num[ele] = h_num[c];
                    }
                    dfs1(c, ele);
                }
            out[c] = cur;
        };
        dfs1(-1, root);
    }
    ll lca(ll a, ll b) {
        if (dpth[a] < dpth[b]) swap(a, b);
        while (a != b) {
            if (h_num[a] == -1) {
                a = baap[a];
            }
            else {
                if (h_num[b] == h_num[a]) a = b;
                else if (dpth[h_num[a]]-1 >= dpth[b]) a = baap[h_num[a]];
                else if (h_num[b] == -1) b = baap[b];
                else if (dpth[h_num[b]] > dpth[h_num[a]]) b = baap[h_num[b]];
                else a = baap[h_num[a]];
            }
            if (dpth[a] < dpth[b]) swap(a, b);
        }
        return a;
    }
};