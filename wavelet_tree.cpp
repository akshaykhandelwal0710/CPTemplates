struct wavelet_tree{
    vector<vector<int>> l, r;
    vector<int> lo, hi, mid;
    vector<int> left, right;
    int cur;
    void build(vector<int> v) {
        l.push_back(vector<int>());
        r.push_back(vector<int>());
        left.push_back(-1);
        right.push_back(-1);
        int k = cur++;
        mid.push_back((lo[k]+hi[k])/2);
        for (auto &ele: v) {
            if (ele <= mid[k]) l[k].push_back(ele);
            else r[k].push_back(ele);
        }
        if (lo[k] == hi[k]) return;
        if (!l[k].empty()){
            left[k] = cur;
            lo.push_back(lo[k]);
            hi.push_back(mid[k]);
            build(l[k]);
        }
        if (!r[k].empty()){
            right[k] = cur;
            lo.push_back(mid[k]+1);
            hi.push_back(hi[k]);
            build(r[k]);
        }
        l[k].clear();
        r[k].clear();
        l[k].push_back(0);
        r[k].push_back(0);
        for (auto &ele: v) {
            l[k].push_back(l[k].back()+(ele<=mid[k]));
            r[k].push_back(r[k].back()+(ele>mid[k]));
        }
    }
    wavelet_tree(int mn, int mx, vector<int> &v){
        cur = 0;
        lo.push_back(mn);
        hi.push_back(mx);
        build(v);
    }
    int quantile(int st, int en, int x, int k = 0){
        if (lo[k] == hi[k]) return lo[k];
        int c = l[k][en] - l[k][st-1];
        if (x <= c) return quantile(l[k][st-1]+1, l[k][en], x, left[k]);
        else return quantile(r[k][st-1]+1, r[k][en], x-c, right[k]);
    }
};
