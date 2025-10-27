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