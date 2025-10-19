// NOTE: This implementation asumes initial tree to be identity
struct Data {
    // data values
    Data() {
        // initialise
    }
};
Data idt = Data(); // additive identity
Data join_res = Data(); // store result of joining here
Data result = Data(); // any result from segtree gets stored here

void join(Data &left, Data &right) {
    // function for joining
}
void assign(Data &from, Data &to) {
    // copy all the data in 'from' to 'to'
}
struct DynamicSegtree {
    ll lo, hi;
    DynamicSegtree *left, *right;
    Data vl;
    DynamicSegtree(ll low, ll high): hi(high), lo(low) {
        left = right = nullptr;
        vl = Data();
    }
    void ensureLeft() {
        assert(lo < hi);
        if (left == nullptr) left = new DynamicSegtree(lo, (lo+hi)/2);
    }
    void ensureRight() {
        assert(lo < hi);
        if (right == nullptr) right = new DynamicSegtree((lo+hi)/2+1, hi);
    }
    void update() {
        assert(lo < hi);
        if (left != nullptr) {
            if (right != nullptr) {
                join(left->vl, right->vl);
                assign(join_res, vl);
            }
            else assign(left->vl, vl);
        }
        else if (right != nullptr) assign(right->vl, vl);
    }
    void change_val(ll i, Data &v) {
        if (lo == hi) assign(v, vl);
        else {
            if (i <= (lo+hi)/2) {
                ensureLeft();
                left->change_val(i, v);
            }
            else {
                ensureRight();
                right->change_val(i, v);
            }
            update();
        }
    }
    void get_range(ll l, ll r, bool init = true) {
        if (init) result = Data();
        if (hi < l || lo > r) return;
        if (lo >= l && hi <= r) {
            join(result, vl);
            assign(join_res, result);
        }
        else {
            if (left != nullptr) left->get_range(l, r, false);
            if (right != nullptr) right->get_range(l, r, false);
        }
    }
};
