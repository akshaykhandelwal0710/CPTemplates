const ll mod = 1e9 + 7;
const ll p1 = 23;
const ll p2 = 29;
vector<ll> p_hash1(n, 0), p_hash2(n, 0), s_hash1(n+1, 0), s_hash2(n+1, 0);
for (ll i = 0; i < n; i++) {
    p_hash1[i] = ((i ? p_hash1[i-1] : 0LL)*p1+s[i])%mod;
    p_hash2[i] = ((i ? p_hash2[i-1] : 0LL)*p2+s[i])%mod;
}
for (ll i = n-1; i >= 0; i--) {
    s_hash1[i] = (s_hash1[i+1]*p1+s[i])%mod;
    s_hash2[i] = (s_hash2[i+1]*p2+s[i])%mod;
}

vector<ll> pow1(n+1, 1), pow2(n+1, 1);
for (ll i = 1; i <= n; i++) {
    pow1[i] = (pow1[i-1]*p1)%mod;
    pow2[i] = (pow2[i-1]*p2)%mod;
}

ll h1, h2;
auto get_p = [&](ll l, ll r)->pair<ll, ll>{
    h1 = p_hash1[r];
    h2 = p_hash2[r];

    if (l) {
        h1 -= (p_hash1[l-1]*pow1[r-l+1])%mod;
        h1 += mod;
        h1 %= mod;

        h2 -= (p_hash2[l-1]*pow2[r-l+1])%mod;
        h2 += mod;
        h2 %= mod;
    }
    return {h1, h2};
};
auto get_s = [&](ll l, ll r)->pair<ll, ll>{
    h1 = s_hash1[l];
    h2 = s_hash2[l];

    h1 -= (s_hash1[r+1]*pow1[r-l+1])%mod;
    h1 += mod;
    h1 %= mod;
    h2 -= (s_hash2[r+1]*pow2[r-l+1])%mod;
    h2 += mod;
    h2 %= mod;
    return {h1, h2};
};