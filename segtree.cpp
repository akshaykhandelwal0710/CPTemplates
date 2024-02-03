struct Data {
   // define data items
   Data() {
       // initialise data items
   }
};
Data op(Data &l, Data &r) {
   // modify this
}
struct segtree{
   vector<Data> d;
   int _n, log, size;
   unsigned int bit_ceil(unsigned int n) {
       unsigned int x = 1;
       while (x < (unsigned int)(n)) x <<= 1;
       return x;
   }
   segtree(int n): _n(n) {
       size = (int)bit_ceil((unsigned int)(n));
       log = __builtin_ctz((unsigned int)size);
       d.resize(2*size, Data());
   }
   void update(int k) { d[k] = op(d[2*k], d[2*k+1]); }
   void set(int p, Data x) {
       p += size;
       d[p] = x;
       for (int i = 1; i <= log; i++) update(p >> i);
   }
   Data prod(int l, int r) { // !!! q(l,r) return l to r-1
       if (l == r) return Data();
       l += size;
       r += size;
       Data sml = Data(), smr = Data();
       while (l < r) {
           if (l&1) sml = op(sml, d[l++]);
           if (r&1) smr = op(d[--r], smr);
           l >>= 1;
           r >>= 1;
       }
       return op(sml, smr);
   }
};
