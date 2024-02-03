vector<ll> z_function(string &s) {
    ll n = s.size();
    vector<ll> z(n);
    ll l = 0, r = 0;
    for(ll i = 1; i < n; i++) {
        z[i] = (i < r ? min(r-i, z[i-l]) : 0LL);
        while(i+z[i] < n && s[z[i]] == s[i+z[i]]) z[i]++;
        if (i+z[i] > r) l = i, r = i+z[i];
    }
    return z;
}