pair<ll, ll> extended_gcd(ll a, ll b){
   pair<ll, ll> aa = {1, 0}, bb = {0, 1};
   while (b){
       aa.first -= bb.first*(a/b);
       aa.second -= bb.second*(a/b);
       a %= b;
       swap(a, b);
       swap(aa, bb);
   }
   return aa;
}
