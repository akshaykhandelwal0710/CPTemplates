inline constexpr ll modPow(ll a, ll b, ll c) {
    return ((b & 1) ? (a * modPow(a, b ^ 1, c) % c) : (b == 0) ? 1 : (modPow(a*a % c, b >> 1, c)));
}
const int mod = 998244353;
const int root = 15311432;
const int root_1 = mod_inv(root, mod);
const int root_pw = 1<<23;
ll pows[1<<20]; // Change if required
void ntt(vector<int> &v, bool invert = false) {
    int n = v.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n>>1;
        for (; j&bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) swap(v[i], v[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1) wlen = ((ll)wlen*wlen)%mod;
        pows[0] = 1;
        for (int k = 1; k < len/2; k++) pows[k] = (pows[k-1]*wlen)%mod;
        for (int i = 0; i < n; i += len) {
            for (int j = 0; j < len/2; j++) {
                int a = v[i+j], b = (v[i+j+len/2]*pows[j])%mod;
                v[i+j] = a+b < mod ? a+b : a+b-mod;
                v[i+j+len/2] = a-b >= 0 ? a-b : a-b+mod;
            }
        }
    }
    if (invert) {
        ll n_1 = mod_inv(n, mod);
        for (int &x: v) x = (x*n_1)%mod;
    }
}
vector<int> mult(vector<int> a, vector<int> b) {
    int t = (int)a.size()+(int)b.size()-1;
    int n = 1;
    while (n < t) n <<= 1;
    a.resize(n, 0);
    b.resize(n, 0);
    ntt(a);
    ntt(b);
    for (int i = 0; i < n; i++) a[i] = ((ll)a[i]*b[i])%mod;
    ntt(a, true);
    a.resize(t);
    return a;
}
vector<int> multimul(vector<vector<int>> v) {
    vector<vector<int>> nv;
    int n = 1;
    for (int i = 0; i < v.size(); i++) n += (int)v[i].size()-1;
    int m = 1;
    while ((int)v.size() > 1) {
        int i = 0;
        int l = (int)v.size();
        nv.clear();
        while (i < l) {
            if (i == l-1) {
                nv.push_back(v[i]);
                ++i;
                break;
            }
            nv.push_back(mult(v[i], v[i+1]));
            i += 2;
        }
        swap(v, nv);
    }
    return v[0];
}
vector<int> diff(vector<int> &a) {
    int n = a.size();
    vector<int> ret(n-1, 0);
    for (ll i = 0; i+1 < n; i++) ret[i] = (a[i+1]*(i+1))%mod;
    return ret;
}
vector<int> integ(vector<int> &a) {
    ll n = a.size();
    vector<int> ret(n+1, 0);
    for (ll i = 1; i <= n; i++) ret[i] = (a[i-1]*mod_inv(i, mod))%mod;
    return ret;
}
vector<int> inverse(vector<int> &a) {
    vector<int> neg_a = a;
    for (auto &x: neg_a) x = x ? mod-x : 0;
    vector<int> q = {(int)mod_inv(a[0], mod)};
    ll n = 1, m = 1;
    while (n < (ll)a.size()) n <<= 1;
    neg_a.resize(n, 0);
    while (m < n) {
        vector<int> tmp(4*m, 0);
        q.resize(4*m, 0);
        for (int i = 0; i < 2*m; i++) tmp[i] = neg_a[i];
        ntt(q);
        ntt(tmp);
        for (int i = 0; i < 4*m; i++) tmp[i] = ((ll)q[i]*tmp[i])%mod;
        ntt(tmp, true);
        tmp[0] = tmp[0]+2 < mod ? tmp[0]+2 : tmp[0]+2-mod;
        ntt(tmp);
        for (int i = 0; i < 4*m; i++) q[i] = ((ll)q[i]*tmp[i])%mod;
        ntt(q, true);
        q.resize(2*m);
        m <<= 1;
    }
    q.resize((int)a.size());
    return q;
}
vector<int> log(vector<int> &a) {
    vector<int> tmp = mult(diff(a), inverse(a));
    tmp.resize((int)a.size()-1);
    return integ(tmp);
}
vector<int> exp(vector<int> &a) {
    int n = 1;
    while (n < (ll)a.size()) n <<= 1;
    vector<int> q = {1};
    vector<int> a_copy = a;
    a_copy.resize(n, 0);
    a_copy[0] = a_copy[0]+1 < mod ? a_copy[0]+1 : a_copy[0]+1-mod;
    int m = 1;
    while (m < n) {
        q.resize(2*m, 0);
        vector<int> tmp = log(q);
        for (ll i = 0; i < 2*m; i++) tmp[i] = a_copy[i] < tmp[i] ? a_copy[i]-tmp[i]+mod : a_copy[i]-tmp[i];
        q = mult(q, tmp);
        m <<= 1;
    }
    q.resize((int)a.size());
    return q;
}
vector<int> pow(vector<int> &a, ll k) {
    int n = a.size();
    if (k == 0) {
        vector<int> ret(n, 0);
        ret[0] = 1;
        return ret;
    }
    int st = 0;
    while (st < n && a[st] == 0) ++st;
    if (st == n || (__int128)k*st >= n) return vector<int>(n, 0);
    int alpha = a[st];
    int alpha_iv = mod_inv(a[st], mod);
    n -= st;
    vector<int> v(n, 0);
    for (int i = 0; i < n; i++) v[i] = ((ll)a[i+st]*alpha_iv)%mod;
    v = log(v);
    for (int i = 0; i < v.size(); i++) v[i] = ((__int128)k*v[i])%mod;
    v = exp(v);
    vector<int> ans(n+st, 0);
    alpha = modPow(alpha, k, mod);
    for (int i = 0; i+st*k < n+st; i++) ans[i+st*k] = ((ll)v[i]*alpha)%mod;
    return ans;
}
vector<int> compose(vector<int> &f, vector<int> &g) {
    int n = min((int)f.size(), (int)g.size());
    int m = ceil(sqrt(n));
    int t = (n+m-1)/m;
    vector<vector<int>> gpow(m);
    gpow[0] = vector<int>(n, 0);
    gpow[0][0] = 1;
    for (int i = 1; i < m; i++) {
        gpow[i] = mult(gpow[i-1], g);
        gpow[i].resize(n);
    }
    vector<int> G = mult(gpow[m-1], g);
    G.resize(n);
    vector<vector<int>> Gpow(t);
    Gpow[0] = vector<int>(n, 0);
    Gpow[0][0] = 1;
    for (int i = 1; i < t; i++) {
        Gpow[i] = mult(Gpow[i-1], G);
        Gpow[i].resize(n);
    }
    vector<vector<int>> Fj(t, vector<int>(m, 0));
    for (int i = 0; i < n; i++) Fj[i/m][i%m] = f[i];
    vector<vector<int>> Ej(t, vector<int>(n, 0));
    for (int j = 0; j < t; j++) {
        for (int x = 0; x < n; x++) {
            __int128 val = 0;
            for (int i = 0; i < m; i++) val += (ll)gpow[i][x]*Fj[j][i];
            Ej[j][x] = val%mod;
        }
    }
    vector<int> res(n, 0);
    for (int j = 0; j < t; j++) {
        vector<int> v = mult(Ej[j], Gpow[j]);
        for (int i = 0; i < n; i++) {
            res[i] += v[i];
            if (res[i] >= mod) res[i] -= mod;
        }
    }
    return res;
}
vector<int> comp_inv(vector<int> &a) {
    int n = 1;
    while (n < (int)a.size()) n <<= 1;
    vector<int> q = {0};
    int m = 1;
    while (m < n) {
        q.resize(2*m, 0);
        vector<int> f(2*m+1, 0);
        for (int i = 0; i < min(2*m+1, (int)a.size()); i++) f[i] = a[i];
        vector<int> fd = diff(f);
        f.pop_back();
        f = compose(f, q);
        fd = compose(fd, q);
        fd = inverse(fd);
        f[1] = f[1] == 0 ? mod-1 : f[1]-1;
        f = mult(f, fd);
        for (int i = 0; i < 2*m; i++) q[i] = q[i] < f[i] ? q[i]-f[i]+mod : q[i]-f[i];
        m <<= 1;
    }
    q.resize((int)a.size());
    return q;
}
pair<vector<int>, vector<int>> divide(vector<int> &num, vector<int> &den) {
    int n = num.size(), m = den.size();
    if (n < m) return {{}, num};
    int k = n-m+1;
    vector<int> numr = num;
    vector<int> denr = den;
    reverse(numr.begin(), numr.end());
    reverse(denr.begin(), denr.end());
    denr.resize(k, 0);
    denr = inverse(denr);
    vector<int> q = mult(numr, denr);
    q.resize(k);
    reverse(q.begin(), q.end());
    vector<int> r = mult(q, den);
    r.resize(m);
    for (int i = 0; i < min(n, m); i++) r[i] = num[i] < r[i] ? num[i]-r[i]+mod : num[i]-r[i];
    while (!r.empty() && r.back() == 0) r.pop_back();
    while (!q.empty() && q.back() == 0) q.pop_back();
    return {q, r};
}