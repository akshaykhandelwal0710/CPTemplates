ll mod_inv(ll a, ll m) {
    ll g = m, r = a, x = 0, y = 1;
    while (r != 0) {
        ll q = g / r;
        g %= r; swap(g, r);
        x -= q * y; swap(x, y);
    }
    return (x%m + m)%m;
}
