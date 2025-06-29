const ll inf = 1e18;

struct Line {
    ll m, c;

    Line() {
        m = 0LL;
        c = -inf;
    }

    Line(ll slope, ll cons) {
        m = slope;
        c = cons;
    }
};

ll f(Line &line, ll x) {
    auto [m, c] = line;
    return m*x+c;
}

struct LiChao{
    Line line;
    ll low, high;
    LiChao *left, *right;

    LiChao(ll lo, ll hi) {
        line = Line();
        low = lo;
        high = hi;
        if (low < high) {
            ll mid = (low+high)/2;
            left = new LiChao(low, mid);
            right = new LiChao(mid+1, high);
        }
    }

    void add_line_segment(Line new_line, ll l, ll r) {
        if (low > r || high < l) return;
        if (low >= l && high <= r) {
            ll m = (low+high)/2;
            bool mid = f(new_line, m) > f(line, m);
            bool rig = f(new_line, high) > f(line, high);
            if (mid) swap(new_line, line);
            if (low == high) return;
            else if (rig != mid) right->add_line_segment(new_line, l, r);
            else left->add_line_segment(new_line, l, r);
        }
        else {
            left->add_line_segment(new_line, l, r);
            right->add_line_segment(new_line, l, r);
        }
    }

    ll get(ll x) {
        ll m = (low+high)/2;
        if (low == high) return f(line, x);
        else if (x <= m) return max(f(line, x), left->get(x));
        else return max(f(line, x), right->get(x));
    }
};
