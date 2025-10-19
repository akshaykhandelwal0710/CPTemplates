struct FenwickTree{
    vector<ll> bit;
    ll n;
    FenwickTree(ll n) {
        this->n = n;
        bit.assign(n, 0);
    }
    FenwickTree(vector<ll> const &a): FenwickTree(a.size()) {
        for (ll i = 0; i < n; i++) {
            bit[i] += a[i];
            ll r = i|(i+1);
            if (r < n) bit[r] += bit[i];
        }
    }
    ll prefix_sum(ll r) {
        ll ret = 0;
        for (; r >= 0; r = (r&(r+1))-1) ret += bit[r];
        return ret;
    }
    ll range_sum(ll l, ll r) {
        return prefix_sum(r) - prefix_sum(l-1);
    }
    void add(ll i, ll k) {
        for (; i < n; i = i|(i+1)) bit[i] += k;
    }
};
