/*
    @ created: 2020-10
    @ updated: 2023-3
    @ verified: Speed Run 001 J
    @ description:
        * 転倒数を O(NlogN) で求める．バブルソートの交換回数．
        * count:  i < j かつ a[i] > a[j] なる (i,j) の組を求める．
        * bit.sum(a[j]) は i<j で a[i] <= a[j] なる要素数なので，j-bit.sum(a[j]) を足せばよい．
        * 座標圧縮が必要なら行う．
*/
#include<bits/stdc++.h>
using namespace std;

template<typename T>
struct BIT{
    int n;
    vector<T> bit;
    BIT(int n_){
        n = n_+1;
        bit.resize(n, 0);
    }
    // a[i] に x を加算
    void add(int i, T x){
        // (x & -x) は x の二進表現で１となる最下位．
        for(int idx=i;idx<n;idx+=(idx&-idx)){
            bit[idx] += x;
        }
    }
    T sum(int i){
        T s(0);
        for(int idx=i;idx>0;idx-=(idx&-idx)){
            s += bit[idx];
        }
        return s;
    }
};


// 座標圧縮
vector<int> shrink(vector<long long> a){
    vector<long long> val = a;
    vector<int> ret(a.size());

    sort(val.begin(),val.end());
    val.erase(unique(val.begin(),val.end()),val.end());

    for(int i=0;i<int(a.size());i++){
        int idx = int(lower_bound(val.begin(), val.end(), a[i])-val.begin());
        ret[i] = idx+1;
    }

    return ret;
}

int main(){
    int n; cin >> n;
    vector<long long> a(n);
    for(int i=0;i<n;i++) cin >> a[i];
    vector<int> v = shrink(a);
    BIT<int> bit(n);
    long long ans = 0;
    for(int i=0;i<n;i++){
        ans += i-bit.sum(v[i]);
        bit.add(v[i], 1);
    }
    cout << ans << endl;
}
