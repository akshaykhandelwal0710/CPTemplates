const ll inf = 1e18;
queue<ll> q;
vector<ll> from, to;
function<bool()> bfs = [&]()->bool {
    for (auto u: from) {
        if (!match[u]) {
            dist[u] = 0;
            q.push(u);
        }
        else {
            dist[u] = inf;
        }
    }
    dist[0] = inf;
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        if (dist[u] < dist[0]) {
            for (auto v: adj[u]) {
                if (dist[match[v]] == inf) {
                    dist[match[v]] = dist[u]+1;
                    q.push(match[v]);
                }
            }
        }
    }
    return dist[0] != inf;
};

function<bool(ll)> dfs = [&](ll u)->bool {
    if (u != 0) {
        for (auto v: adj[u]) {
            if (dist[match[v]] == dist[u]+1) {
                if (dfs(match[v])) {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
        }
        dist[u] = inf;
        return false;
    }
    return true;
};

function<ll()> Hop = [&]()->ll {
    ll matching = 0;
    for (auto u: from) match[u] = 0;
    for (auto v: to) match[v] = 0;
    while (bfs()) {
        for (auto u: from) {
            if (!match[u]) {
                if (dfs(u)) matching++;
            }
        }
    }

    return matching;
};