const ll N = 2e5;
ll tree[N];
struct bit{
    ll n;
    bit(ll n): n(n){
        for (ll i = 0; i < n; i++) tree[i] = 0;
    }
    void add(ll i, ll k){
        for (; i < n; i = i|(i+1)) tree[i] += k;
    }
    ll sum(ll r){
        ll ret = 0;
        for (; r >= 0; r = (r&(r+1))-1) ret += tree[r];
        return ret;
    }
    ll sum(ll l, ll r){
        return sum(r)-sum(l-1);
    }
};