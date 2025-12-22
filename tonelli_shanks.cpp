ll modPow(ll n, ll k, ll m) {
    ll ret = 1;
    for (; k; k >>= 1) {
        if (k&1) ret = (ret*n)%m;
        n = (n*n)%m;
    }
    return ret;
}
ll tonelli_shanks(ll n, ll p) {
    if (n == 0) {
        return 0;
    }
    else if (n == 1) {
        return 1;
    }
    else if (p%4 == 3) {
        ll r = modPow(n, (p+1)/4, p);
        if (modPow(r, 2, p) == n) {
            return r;
        }
        else {
            return -1;
        }
    }
    else if (modPow(n, (p-1)/2, p) != 1) {
        return -1;
    }
    else {
        ll q = p-1;
        ll s = 0;
        while (q%2 == 0) {
            q >>= 1;
            s++;
        }
        ll z = 1;
        while (modPow(z, (p-1)/2, p) == 1) z = rand_int(1, p-1);
        ll m = s;
        ll c = modPow(z, q, p);
        ll t = modPow(n, q, p);
        ll r = modPow(n, (q+1)/2, p);
        while (t != 1) {
            ll k = 0;
            ll y = t;
            while (y != 1) {
                k++;
                y = (y*y)%p;
            }
            ll b = c;
            for (int j = 0; j < m-k-1; j++) b = (b*b)%p;
            m = k;
            c = (b*b)%p;
            t = (t*c)%p;
            r = (r*b)%p;
        }
        return r;
    }
}