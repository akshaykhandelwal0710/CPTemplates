struct Lazy{
    // lazy data values

    Lazy(){
        // initialise
    }
};

struct Data{
    // data values

    Data(){
        // initialise
    }
};

Data idt = Data(); // additive identity
Data join_res = Data(); // store result of joining here
Data result = Data(); // any result from segtree gets stored here

Lazy idt_l = Lazy(); // additive identity
Lazy join_res_l = Lazy(); // store result of joining two lazy values here

void join(Data &left, Data &right){
    // function for joining
}

void join_lazy(Lazy &nw, Lazy &old){
    // function for combining two lazy values
}

void combine(Lazy &lazy, Data &val){
    // change data as per lazy value
}

void assign(Data &from, Data &to){
    // copy all the data in 'from' to 'to'
}

struct persistent_segtree {
    struct node {
        node *left, *right;
        int lo, hi;
        Data val;
        Lazy lazy;
        bool init;
        bool prop;
        int num_refs;

        node(int low, int high, bool bl = true) {
            num_refs = 1;
            lo = low, hi = high;
            val = Data();
            lazy = Lazy();
            init = bl;
            if (lo < hi) {
                int mid = (lo+hi)/2;
                left = new node(lo, mid, false);
                right = new node(mid+1, hi, false);
                update_val();
            }
        }

        node(node *nd) {
            num_refs = 1;
            lo = nd->lo, hi = nd->hi;
            left = nd->left;
            right = nd->right;
            init = nd->init;
            prop = nd->prop;
            val = Data();
            lazy = nd->lazy;
            assign(nd->val, val);

            if (lo < hi) {
                left->num_refs++;
                right->num_refs++;
            }
        }

        void update_val() {
            join(left->val, right->val);
            assign(join_res, val);
        }
        
        void push_down() {
            if (!prop) return;
            combine(lazy, val);
            prop = false;
            if (lo == hi) {
                lazy = idt_l;
                return;
            }
            if (left->num_refs > 1) {
                left->num_refs--;
                left = new node(left);
            }
            if (right->num_refs > 1) {
                right->num_refs--;
                right = new node(right);
            }
            left->prop = right->prop = true;
            join_lazy(lazy, left->lazy);
            left->lazy = join_res_l;
            join_lazy(lazy, right->lazy);
            right->lazy = join_res_l;
            lazy = idt_l;
        }

        void get_range(int l, int r) {
            if (init) assign(idt, result);
            push_down();
            if (lo > r || hi < l) return;
            if (lo >= l && hi <= r) {
                join(result, val);
                assign(join_res, result);
            }
            else {
                left->get_range(l, r);
                right->get_range(l, r);
            }
        }

        void change_val(int k, Data &nval) {
            push_down();
            if (lo == hi) {
                // change here to change behaviour
                assign(nval, val);
            }
            else {
                int mid = (lo+hi)/2;
                if (mid >= k) {
                    if (left->num_refs > 1) {
                        left->num_refs--;
                        left = new node(left);
                    }
                    left->change_val(k, nval);
                }
                else {
                    if (right->num_refs > 1) {
                        right->num_refs--;
                        right = new node(right);
                    }
                    right->change_val(k, nval);
                }

                update_val();
            }
        }
        
        void update_range(int l, int r, Lazy &lz) {
            push_down();
            if (lo > r || hi < l) return;
            if (lo >= l && hi <= r) {
                join_lazy(lz, lazy);
                lazy = join_res_l;
                prop = true;
                push_down();
            }
            else {
                if (left->num_refs > 1) {
                    left->num_refs--;
                    left = new node(left);
                }
                if (right->num_refs > 1) {
                    right->num_refs--;
                    right = new node(right);
                }
                left->update_range(l, r, lz);
                right->update_range(l, r, lz);
                update_val();
            }
        }
    };

    vector<node*> trees;
    
    persistent_segtree(int n) {
        trees.resize(n, nullptr);
    }

    void new_tree(int n, int m) {
        trees[n] = new node(0, m-1);
    }

    void copy_tree(int from, int to) {
        trees[to] = new node(trees[from]);
    }
    
    void range_copy(int from, int to, int l, int r) {
        range_copy(trees[from], trees[to], l, r);
    }
    
private:
    void range_copy(node *&from, node *&to, int l, int r) {
        to->push_down();
        from->push_down();
        if (from->lo > r || from->hi < l) return;
        if (from->lo >= l && from->hi <= r) {
            to->num_refs--;
            to = new node(from);
            return;
        }
        if (to->left->num_refs > 1) {
            to->left->num_refs--;
            to->left = new node(to->left);
        }
        range_copy(from->left, to->left, l, r);
        if (to->right->num_refs > 1) {
            to->right->num_refs--;
            to->right = new node(to->right);
        }
        range_copy(from->right, to->right, l, r);
        to->update_val();
    }
};
