struct segtree {
    struct node {
        ll lo, hi, vl;
        node *left, *right;
 
        node(ll low, ll high) {
            lo = low, hi = high;
            vl = 0LL;
            left = right = nullptr;
 
            if (low < high) {
                ll mid = (lo+hi)/2;
                left = new node(lo, mid);
                right = new node(mid+1, hi);
                update();
            }
        }
 
        node (ll low, ll high, ll val, node *lt, node *rt) {
            lo = low, hi = high;
            vl = val;
            left = lt, right = rt;
        }
 
        void update() {
            vl = max(left->vl, right->vl);
        }
    };
 
    private:
    node *root;
    vector<node*> v;
    
    void set(ll i, ll vl, node *nd) {
        if (nd->lo > i || nd->hi < i) return;
        if (nd->lo == nd->hi) nd->vl = vl;
        else {
            set(i, vl, nd->left);
            set(i, vl, nd->right);
            nd->update();
        }
    }
 
    void r_gen(ll i, ll vl, node *nd) {
        if (nd->lo >= i) v.push_back(nd);
        else if (nd->hi < i) return;
        else {
            r_gen(i, vl, nd->left);
            r_gen(i, vl, nd->right);
        }
    }
 
    void l_gen(ll i, ll vl, node *nd) {
        if (nd->hi <= i) v.push_back(nd);
        else if (nd->lo > i) return;
        else {
            l_gen(i, vl, nd->right);
            l_gen(i, vl, nd->left);
        }
    }
 
    ll upper_bound(ll val, node *nd) {
        if (nd->vl <= val) return nd->hi+1LL;
        else if (nd->lo == nd->hi) return nd->lo;
        else if (nd->left->vl <= val) return upper_bound(val, nd->right);
        else return upper_bound(val, nd->left);
    }
 
    // Returns location-1 than the usual definition
    ll lower_bound(ll val, node *nd) {
        if (nd->vl <= val) return nd->lo-1LL;
        else if (nd->lo == nd->hi) return nd->lo;
        else if (nd->right->vl <= val) return lower_bound(val, nd->left);
        else return lower_bound(val, nd->right);
    }
 
    public:
    segtree (ll n) {
        root = new node(0, n-1);
    }
 
    void set(ll i, ll vl) {
        set(i, vl, root);
    }
 
    ll r_srch(ll i, ll vl) {
        v.clear();
        r_gen(i, vl, root);
        ll ret;
        for (auto nd: v) {
            ret = upper_bound(vl, nd)-1LL;
            if (ret < nd->hi) break;
        }
        return ret;
    }
 
    ll l_srch(ll i, ll vl) {
        v.clear();
        l_gen(i, vl, root);
        ll ret;
        for (auto nd: v) {
            ret = lower_bound(vl, nd)+1LL;
            if (ret > nd->lo) break;
        }
        return ret;
    }
};
