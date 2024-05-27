// Two types of queries:

// 1. Find min element in a range and also the find number of minimum elements present in that range
// 2. Update the value of the specified index


#include<bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef long double ld;


struct node {
    ll value;
    ll count;
    // change this constructor acc to the question
    node() {
        value = INT_MAX;
        count = 0;
    }
};
 
class SGTree {
public:
    vector<node> seg;

    // size of the vector
    SGTree(ll n) {
        seg.resize(4 * n + 5);
    }

    // merging logic, fill this

    node merge(node& a, node& b) {
        node c;
        c.value = min(a.value,b.value);

        if(c.value==a.value && c.value==b.value){
            c.count = a.count+b.count;
        }else if(c.value==a.value){
            c.count = a.count;
        }else if(c.value==b.value){
            c.count = b.count;
        }

        return c;
    }

    // build(0,0,n-1,arr) always

    void build(ll idx, ll low, ll high, vector<ll> &arr) {
        if (low == high) {
            seg[idx].value = arr[low];
            seg[idx].count = 1;
            return;
        }
        ll mid = low + (high - low) / 2;
        build(idx * 2 + 1, low, mid, arr);
        build(idx * 2 + 2, mid + 1, high, arr);
        seg[idx] = merge(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    // query(0,0,n-1,leftRange,rightRange)

    node query(ll idx, ll low, ll high, ll l, ll r) {
        if (l > high || r < low) return node();  
        if (low >= l && high <= r) return seg[idx];
        ll mid = low + (high - low) / 2;
        node lh = query(idx * 2 + 1, low, mid, l, r);
        node rh = query(idx * 2 + 2, mid + 1, high, l, r);
        return merge(lh, rh);
    }
    //update (0,0,n-1,positon,updatedValue)
    void update(ll idx, ll low, ll high, ll i, ll val) {
        if (i < low || i > high) return;  // add bounds check here
        if (low == high) {
            seg[idx].value = val;
            seg[idx].count = 1;
            return;
        }
        ll mid = low + (high - low) / 2;
        update(2 * idx + 1, low, mid, i, val);
        update(2 * idx + 2, mid + 1, high, i, val);
        seg[idx] = merge(seg[2 * idx + 1], seg[2 * idx + 2]);
    }
};


void solve(){
    ll n, q;
    cin >> n >> q;
    vector<ll> arr(n);
    for (ll i = 0; i < n; i++)
        cin >> arr[i];
 
    SGTree st(n);
    st.build(0, 0, n - 1, arr);
 
 
    while (q--) {
        ll type;
        cin >> type;
        if (type == 2) {
            ll l, r;
            cin >> l >> r;
            l--, r--;
            node res = st.query(0, 0, n - 1, l, r);
            cout << res.value << " " << res.count << "\n";
        } else if (type == 1) {
            ll i, val;
            cin >> i >> val;
            i--;
            st.update(0, 0, n - 1, i, val);
            arr[i] = val;
        }
    }
}



int main() {

#ifndef ONLINE_JUDGE
     freopen("Input.txt", "r", stdin);
     freopen("Output.txt", "w", stdout);
#endif

     ios_base::sync_with_stdio(false);
     cin.tie(nullptr);
     cout.tie(nullptr);

     ll t;
     t = 1;
     //cin >> t;
     while (t--)
     {
          solve();
     }

     return 0;
}
