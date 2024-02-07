ll mod_pow(ll n, ll k, ll mod) {
    if (k == 0) return 1;
    ll w = mod_pow(n, k/2, mod);
    w = ((__int128)w*w)%mod;
    if (k&1) w = ((__int128)w*n)%mod;
    return w;
}
// Miller Rabin Test (probabilistic, use multiple times (atleast 5) to be sure)
bool mr_test(ll n) {
    ll d = n-1, s = 0;
    while (d % 2 == 0) {
        s++;
        d /= 2;
    }
    ll a = rand_int(2, n-1);
    ll x = mod_pow(a, d, n);
    if (x == 1 || x == n-1) return true;
    for (ll r = 0; r < s; r++) {
        x = ((__int128)x*x)%n;
        if (x == n-1) return true;
    }
    return false;
}