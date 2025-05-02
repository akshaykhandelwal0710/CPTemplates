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

struct persistent_segtree {
    struct node {
        node *left, *right;
        int lo, hi;
        Data val;
        bool init;
        int num_refs;

        node(int low, int high, bool bl = true) {
            num_refs = 1;
            lo = low, hi = high;
            val = Data();
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
            val = Data();
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

        void get_range(int l, int r) {
            if (init) assign(idt, result);
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
};
