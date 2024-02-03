struct Data {
   // define data items
   Data() {
       // initialise data items
   }
};
struct Lazy {
   // define lazy items
   Lazy() {
       // initialise
   }
};
Data op(Data &l, Data &r) {
   // combine left and right data items
}
Lazy composition(Lazy &nw, Lazy &old) {
   // combine old and new lazy values
}
void combine(Lazy &lz, Data &data) {
   // apply the lazy values to data
}
struct segtree{
   vector<Data> d;
   vector<Lazy> lz;
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
       lz.resize(size, Lazy());
   }
   void update(int k) { d[k] = op(d[2*k], d[2*k+1]); }
   void all_apply (int k, Lazy &f) {
       combine(f, d[k]);
       if (k < size) lz[k] = composition(f, lz[k]);
   }
   void push(int k) {
       all_apply(2*k, lz[k]);
       all_apply(2*k+1, lz[k]);
       lz[k] = Lazy();
   }
   void set(int p, Data x) {
       p += size;
       for (int i = log; i >= 1; i--) push(p >> i);
       d[p] = x;
       for (int i = 1; i <= log; i++) update(p >> i);
   }
   Data prod(int l, int r) { // !!! q(l,r) return l to r-1
       if (l == r) return Data();
       l += size;
       r += size;
       for (int i = log; i >= 1; i--) {
           if (((l>>i)<<i) != l) push(l>>i);
           if (((r>>i)<<i) != r) push((r-1)>>i);
       }
       Data sml = Data(), smr = Data();
       while (l < r) {
           if (l&1) sml = op(sml, d[l++]);
           if (r&1) smr = op(d[--r], smr);
           l >>= 1;
           r >>= 1;
       }
       return op(sml, smr);
   }
   void apply(int l, int r, Lazy &f) {
       if (l == r) return;
       l += size;
       r += size;
       for (int i = log; i >= 1; i--) {
           if (((l>>i)<<i) != l) push(l>>i);
           if (((r>>i)<<i) != r) push((r-1)>>i);
       }
       {
           int l2 = l, r2 = r;
           while (l < r) {
               if (l&1) all_apply(l++, f);
               if (r&1) all_apply(--r, f);
               l >>= 1;
               r >>= 1;
           }
           l = l2;
           r = r2;
       }
       for (int i = 1; i <= log; i++) {
           if (((l>>i)<<i) != l) update(l>>i);
           if (((r>>i)<<i) != r) update((r-1)>>i);
       }
   }
};
