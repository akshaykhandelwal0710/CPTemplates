vector<ll> dist(n, inf);
vector<bool> done(n, false);
priority_queue<pair<ll, ll>> q;
q.push({0, s});
dist[s] = 0;
while (!q.empty()) {
    auto [_, u] = q.top();
    q.pop();
    if (done[u]) continue;
    done[u] = true;
    for (auto [v, w]: adj[u]) if (dist[v] > dist[u]+w) {
        dist[v] = dist[u]+w;
        q.push({-dist[v], v});
    }
}