// There is an array consisting of n integers. Some values of the array will be updated, and after each update, your task is to report the maximum subarray sum in the array.


#include<bits/stdc++.h>

using namespace std;

typedef long long int ll;
typedef long double ld;

struct node
{
    ll maxi,pre,suff,total;
    node(){
        maxi=0;
        pre=0;
        suff=0;
        total=0;
    }
};

class SGTree{

public:

    vector<node>tree;

    SGTree(ll n){
        tree.resize(4*n+5);
    }

    node merge(node left,node right){
        node res;

        res.maxi = max({left.maxi,right.maxi,left.suff+right.pre});
        res.pre = max({left.pre,left.total+right.pre});
        res.suff = max({right.suff,right.total+left.suff});
        res.total = left.total+right.total;

        return res;
    }

    void build(ll idx,ll low,ll high,vector<ll>& nums){
        if(low==high){
            tree[idx].maxi = max(nums[low],0*1ll); // tricky here
            tree[idx].pre = nums[low];
            tree[idx].suff = nums[low];
            tree[idx].total = nums[low];
            return;
        }

        ll mid = low+(high-low)/2;

        build(2*idx+1,low,mid,nums);
        build(2*idx+2,mid+1,high,nums);

        tree[idx] = merge(tree[2*idx+1],tree[2*idx+2]);
    }

    node query(ll idx,ll low,ll high,ll l,ll h){
        if(l>high || low>h) return node();
        if(l<=low && h>=high) return tree[idx];

        ll mid = low+(high-low)/2;
        node lh = query(2*idx+1,low,mid,l,h);
        node rh = query(2*idx+2,mid+1,high,l,h);

        return merge(lh,rh);

    }

    void update(ll idx,ll low,ll high,ll pos,ll x){
        if(pos<low || pos>high) return;
        if(low==high){
            tree[idx].maxi = max(x,0*1ll);  //tricky here
            tree[idx].pre = x;
            tree[idx].suff = x;
            tree[idx].total = x;
            return;
        }

        ll mid = low+(high-low)/2;

        update(2*idx+1,low,mid,pos,x);
        update(2*idx+2,mid+1,high,pos,x);

        tree[idx] = merge(tree[2*idx+1],tree[2*idx+2]);

    }

};


void solve(){
    ll n,q;
    cin>>n>>q;

    vector<ll>nums(n);
    for(ll i=0;i<n;i++)
        cin>>nums[i];

    SGTree sgt(n);

    sgt.build(0,0,n-1,nums);

    ll pos,x;

    while(q--){
        cin>>pos>>x;
        pos--;
        sgt.update(0,0,n-1,pos,x);
        node res = sgt.query(0,0,n-1,0,n-1);
        cout<<res.maxi<<"\n";
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

