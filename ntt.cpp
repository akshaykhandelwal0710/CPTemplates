// large mod = 9223372036737335297 prim_root = 3, use int128 for multiplication and addition operations
const ll MOD = 998244353;
constexpr ll mAdd(ll a, ll b, ll c) {
   return (a+b >= c ? a+b-c : a+b);
}
constexpr ll mSub(ll a, ll b, ll c) {
   return (a < b ? a-b+c : a-b);
}
constexpr ll modPow(ll a, ll b, ll c) {
   return ((b & 1) ? (a * modPow(a, b ^ 1, c) % c) : (b == 0) ? 1 : (modPow(a*a % c, b >> 1, c)));
}
// Preconditions: P is prime, n = 2^m, 2^m | P-1, 3 is a generator of P
void ntt(vector<ll>& v, bool invert = false) {
   ll n = v.size();
   for (int i = 0; i < n; ++i) {
       int t = 0;
       for (int j = 0; (1<<j) < n; ++j) {
           if (i & (1<<j)) t |= n >> (j+1);
       }
       if (i < t) swap(v[i], v[t]);
   }
   ll root = modPow(3, (invert ? (n-1) : 1) * (ll)(MOD-1) / n, MOD);
   for (int h = 1; h < n; h <<= 1) {
       ll curr = 1, mult = modPow(root, n / (2*h), MOD);
       for (int j = 0; j < h; ++j) {
           for (int i = j; i < n; i += 2*h) {
               ll w = (curr * v[i^h]) % MOD;
               v[i^h] = mSub(v[i], w, MOD);
               v[i] = mAdd(v[i], w, MOD);
           }
           curr = (curr * mult) % MOD;
       }
   }
}
vector<ll> mult(vector<ll> a, vector<ll> b) {
   ll n = 1, t = (int)a.size() + b.size() - 1;
   while(n < t) n <<= 1;
   a.resize(n, 0); b.resize(n, 0);
   ntt(a, 0); ntt(b, 0);
   vector<ll> c(n);
   int n_inv = modPow(n, MOD-2, MOD);
   for (int i = 0; i < n; ++i) c[i] = (ll)a[i]*b[i] % MOD * n_inv % MOD;
   ntt(c, 1);
   c.resize(t);
   return c;
}
