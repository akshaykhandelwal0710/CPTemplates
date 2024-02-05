// might want to #include<bit>
const ll K = 20;
const ll N = 2e5;
ll spt[N][K];
constexpr auto log2_floor = [&](unsigned int i) {
    return std::bit_width(i) - 1;
};
auto func = [&](ll a, ll b)->ll{
    return min(a, b);
};
auto range = [&](ll l, ll r)->ll{
    ll k = log2_floor(r-l+1);
    return func(spt[l][k], spt[r-(1LL<<k)+1][k]);
};
auto construct = [&](vector<ll> &v)->void {
    ll n = v.size();
    for (ll i = 0; i < n; i++) spt[i][0] = v[i];
    for (ll i = n-1; i >= 0; i--)
        for (ll j = 1; (1LL<<j)+i-1 < n; j++)
            spt[i][j] = func(spt[i][j-1], spt[i+(1LL<<(j-1))][j-1]);
};