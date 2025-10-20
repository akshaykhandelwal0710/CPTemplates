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

struct segmentTree{
    int low, high;
    bool init;
    segmentTree *left;
    segmentTree *right;
    Data val;
    Lazy lazy;
    bool prop;

    void update_val(){
        join(left->val, right->val);
        assign(join_res, val);
    }

    void push_down(){
        if (!prop) return;
        prop = false;
        if (low == high){
            lazy = idt_l;
            return;
        }
        left->prop = right->prop = true;
        combine(lazy, left->val);
        join_lazy( lazy, left->lazy);
        left->lazy = join_res_l;
        combine(lazy, right->val);
        join_lazy(lazy, right->lazy);
        right->lazy = join_res_l;
        lazy = idt_l;
    }

    segmentTree(int l, int h, bool bl = true){
        low = l;
        high = h;
        val = Data();
        lazy = Lazy();
        prop = false;
        init = bl;
        if (l < h){
            int mid = (low + high)/2;
            left = (segmentTree *)malloc(sizeof(segmentTree));
            right = (segmentTree *)malloc(sizeof(segmentTree));
            *left = segmentTree(low, mid, false);
            *right = segmentTree(mid+1, high, false);
            update_val();
        }
    }

    void get(){
        assign(val, result);
    }

    void get_range(int l, int h){
        if (init){
            assign(idt, result);
        }

        if (low >= l && high <= h){
            join(result, val);
            assign(join_res, result);
        }
        else{
            push_down();
            if (left->high >= l) left->get_range(l, h);
            if (right->low <= h) right->get_range(l, h);
        }
    }

    void update_range(int l, int h, Lazy &lz){
        if (low >= l && high <= h){
            join_lazy(lz, lazy);
            lazy = join_res_l;
            prop = true;
            combine(lz, val);
        }
        else{
            push_down();
            if (left->high >= l) left->update_range(l, h, lz);
            if (right->low <= h) right->update_range(l, h, lz);
            update_val();
        }
    }

    void change_val(int k, Data &vl){
        if (low == high){
            assign(vl, val);
        }
        else{
            push_down();
            if (left->high >= k) left->change_val(k, vl);
            else right->change_val(k, vl);
            update_val();
        }
    }
};
