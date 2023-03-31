/*
    @ created: 2023-3
    @ updated: None
    @ verified: 
    @ description:
        * Binary Indexed Tree.
        * 一点加算 O(logN)，区間和取得 O(logN) で行う．
        * セグ木の不要な部分を消すことで，配列長 N でよい．
        * n=8 で区間和 [1], [1,2], [3], [1-4], [5], [5,6], [7], [1-8] を持つ．
        * 1-indexed であることに注意．
    @ usage:
        * BIT<int> bit(n);
        * rep(i,n) {int a; cin >> a; bit.add(i+1, a);}
        * bit.sum(place)
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
