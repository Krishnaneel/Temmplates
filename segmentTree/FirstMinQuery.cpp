// You have given an array A of n integers. Your task is to answer q queries. Each query contains an integer x. 
// For each query, print the minimum index i such that Ai ≥ x, and then decrease the value at position i by x, i.e., Ai = Ai - x. If there doesn't exist any index i satisfying the condition, then simply print 0.



#include<bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef long double ld;


struct node {
    ll value;
    // change this constructor acc to the question
    node() {
        value = INT_MIN;
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

        c.value = max(a.value,b.value);

        return c;
    }

    // build(0,0,n-1,arr) always

    void build(ll idx, ll low, ll high, vector<ll> &arr) {
        if (low == high) {
            seg[idx].value = arr[low];
            return;
        }
        ll mid = low + (high - low) / 2;
        build(idx * 2 + 1, low, mid, arr);
        build(idx * 2 + 2, mid + 1, high, arr);
        seg[idx] = merge(seg[2 * idx + 1], seg[2 * idx + 2]);
    }

    // query(0,0,n-1,leftRange,rightRange)

    int query(ll idx, ll low, ll high, ll x) {
        if (seg[idx].value<x) return -1;  
        if (low == high) return low;

        ll mid = low + (high - low) / 2;
        if(seg[2*idx+1].value>=x)
            return query(idx * 2 + 1, low, mid, x);
        return query(idx * 2 + 2, mid + 1, high, x);
    }

    //update (0,0,n-1,positon,updatedValue)

    void update(ll idx, ll low, ll high, ll i, ll val) {
        if (i < low || i > high) return;  // add bounds check here
        if (low == high) {
            seg[idx].value -= val;
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
    cin >> n ;
    cin>>q;
    
    vector<ll> arr(n);
    for (ll i = 0; i < n; i++)
        cin >> arr[i];
 
    SGTree st(n);
    st.build(0, 0, n - 1, arr);
 
 
    while (q--) {
        ll x;
        cin>>x;
        ll idx = st.query(0,0,n-1,x);
        cout<<idx+1<<"\n";
        if(idx!=-1) st.update(0,0,n-1,idx,x);
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
