using ldb = long double;
using cd = complex<ldb>;
const double PI = acosl(-1);
void fft(vector<cd> &v, bool invert = false) {
   ll n = v.size();
   for (ll i = 1, j = 0; i < n; i++) {
       ll bit = n >> 1;
       for (; j & bit; bit >>= 1) j ^= bit;
       j ^= bit;
       if (i < j) swap(v[i], v[j]);
   }
   cd w, wk, a, b;
   ldb alpha;
   for (ll len = 2; len <= n; len <<= 1) {
       for (ll i = 0; i < n; i += len) {
           alpha = 2 * PI / len * (invert ? 1 : -1);
           w = {cosl(alpha), sinl(alpha)};
           wk = 1;
           for (ll j = 0; j < len/2; j++) {
               a = v[i+j], b = v[i+j+len/2] * wk;
               v[i+j] = a+b;
               v[i+j+len/2] = a-b;
               wk *= w;
           }
       }
   }
   if (invert) {
       for (ll i = 0; i < n; i++) v[i] /= n;
   }
}