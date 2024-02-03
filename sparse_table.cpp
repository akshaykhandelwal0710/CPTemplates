const ll K = 20;
const ll N = 5e5;
ll spt[N][K];
ll lg[N+1];
for (ll i = 1; i <= N; i++) lg[i] = ((1LL<<lg[i-1]) == (i>>1) ? lg[i-1]+1 : lg[i-1]);
auto func = [&](ll a, ll b)->ll{
    return min(a, b);
};
auto range = [&](ll l, ll r)->ll{
    ll k = (r-l+1);
    return func(spt[l][lg[k]], spt[r-(1LL<<lg[k])+1][lg[k]]);
};
auto construct = [&](vector<ll> &v)->void {
    ll n = v.size();
    for (ll i = 0; i < n; i++) spt[i][0] = v[i];
    for (ll i = n-1; i >= 0; i--)
        for (ll j = 1; (1LL<<j)+i-1 < n; j++)
            spt[i][j] = func(spt[i][j-1], spt[i+(1LL<<(j-1))][j-1]);
};