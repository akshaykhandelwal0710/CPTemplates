inline void matmul(vector<vector<ll>> &a, vector<vector<ll>> &b, vector<vector<ll>> &res) {
    ll n = a.size(), m = b.size(), k = b[0].size();
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < k; j++) {
            __int128 tot = 0;
            for (ll w = 0; w < m; w++) {
                tot += a[i][w]*b[w][j];
            }
            res[i][j] = tot%mod;
        }
    }
}
void matpow(vector<vector<ll>> mat, ll k, vector<vector<ll>> &res) {
    ll n = mat.size();
    assert(mat[0].size() == n);
    for (ll i = 0; i < n; i++) fill(res[i].begin(), res[i].end(), 0);
    for (ll i = 0; i < n; i++) res[i][i] = 1;
    ll p = 1;
    vector<vector<ll>> tmp(n, vector<ll>(n, 0));
    while (p <= k) {
        if (p&k) {
            matmul(mat, res, tmp);
            swap(tmp, res);
        }
        matmul(mat, mat, tmp);
        swap(tmp, mat);
        p <<= 1;
    }
}
ll determinant(vector<vector<ll>> mat) {
    ll n = mat.size();
    ll det = 1;
    for (ll i = 0; i < n; i++) {
        ll pivot = i;
        while (pivot < n && mat[pivot][i] == 0) pivot++;
        if (pivot == n) return 0;
        if (pivot != i) {
            swap(mat[pivot], mat[i]);
            det = mod-det;
        }
        det = (det*mat[i][i])%mod;
        ll iv = mod_inv(mat[i][i], mod);
        for (ll j = i+1; j < n; j++) {
            ll f = (mat[j][i]*iv)%mod;
            for (ll k = i; k < n; k++) {
                mat[j][k] = (mat[j][k]-f*mat[i][k])%mod;
                if (mat[j][k] < 0) mat[j][k] += mod;
            }
        }
    }
    return det;
}