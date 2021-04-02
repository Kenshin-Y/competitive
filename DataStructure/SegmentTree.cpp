/*
 @created: 2020-8
 @verifyed: fin
 @description:
    * 一点更新区間取得 Segment Tree
    * vectorで管理　xを更新するとき、これを含む最下段のノードはx+(n-1)
    * iの下は2i+1,2i+2でこれをマージすれば良い
    * vector<T> v(n);
    * SegmentTree<ll> seg(v);
    *
*/
#ifndef SEGMENTTREE
#define SEGMENTTREE
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct SegmentTree
{
private:
    int n;
    vector<T> node;
    T identity;

public:
    T merge(T x,T y){
        return /* マージ結果　*/ max(x,y);
    }
    SegmentTree(vector<T> v,T id)
    {
        int sz=(int)v.size();
        n=1; while(n<sz)n*=2;
        identity=id;
        node.resize(2*n-1,id);
        for(int i=0;i<sz;i++) node[i+n-1]=v[i];
        for(int i=n-2;i>=0;i--){
            node[i]=merge(node[2*i+1],node[2*i+2]);
        }
    }
    void update(int x,T val)
    {
        x+=(n-1);
        node[x]=val;
        while(x>0){
            x=(x-1)/2;
            node[x]=merge(node[2*x+1],node[2*x+2]);
        }
    }
    T query(int a,int b,int idx=0,int l=0,int r=-1) /* get [a,b) */
    { 
        if(r<0) r=n;
        if(r<=a||b<=l) return identity;
        if(a<=l&&r<=b) return node[idx];
        T vl=query(a,b,2*idx+1,l,(l+r)/2);
        T vr=query(a,b,2*idx+2,(l+r)/2,r);
        return merge(vl,vr);
    };
    T operator[](int k){return node[k+n-1];}
};
#endif // SEGMENTTREE