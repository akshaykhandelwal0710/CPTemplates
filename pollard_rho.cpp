ll gcd(ll a, ll b) {
    return (b ? gcd(b, a % b) : a);
}
ll ab(ll x) {
    return (x < 0 ? -x : x);
}
// use only for composite n to find a divisor of n
ll pollard_rho(ll n) {
    ll st = 0;
    if (n % 2 == 0) return 2;
    while (true) {
        st++;
        ll x = 2, y = 2, d = 1;
        auto g = [&](ll x)->ll {
            return ((__int128)x*x + st) % n;
        };
        while (d == 1) {
            x = g(x), y = g(g(y));
            d = gcd(ab(x-y), n);
        }
        if (d != n) return d;
    }
}