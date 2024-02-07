ll mod_pow(ll n, ll k, ll mod) {
    if (k == 0) return 1;
    ll w = mod_pow(n, k/2, mod);
    w = ((__int128)w*w)%mod;
    if (k&1) w = ((__int128)w*n)%mod;
    return w;
}
ll prim_root(ll p) {
    ll phi = p-1; // use phi function instead if p is not prime
    vector<ll> facts = factorize(phi); // requires a function that gives prime factors of a number
    for (ll i = 1; ; i++) {
        bool f = true;
        for (auto &x: facts) if (mod_pow(i, phi/x, p) == 1) f = false;
        if (f) return i;
    }
}