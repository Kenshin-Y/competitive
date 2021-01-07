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
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct SegmentTree{
private:
    int n;
    vector<T> node;
    T identity;
public:
    T merge(T x,T y){
        return /* マージ結果　*/ max(x,y);
    }
    SegmentTree(vector<T> v,T id){
        int sz=(int)v.size();
        n=1; while(n<sz)n*=2;
        identity=id;
        node.resize(2*n-1,id);
        for(int i=0;i<sz;i++) node[i+n-1]=v[i];
        for(int i=n-2;i>=0;i--){
            node[i]=merge(node[2*i+1],node[2*i+2]);
        }
    }
    void update(int x,T val){
        x+=(n-1);
        node[x]=val;
        while(x>0){
            x=(x-1)/2;
            node[x]=merge(node[2*x+1],node[2*x+2]);
        }
    }
    T query(int a,int b,int idx=0,int l=0,int r=-1){ /* get [a,b) */
        if(r<0) r=n;
        if(r<=a||b<=l) return identity;
        if(a<=l&&r<=b) return node[idx];
        T vl=query(a,b,2*idx+1,l,(l+r)/2);
        T vr=query(a,b,2*idx+2,(l+r)/2,r);
        return merge(vl,vr);
    };
    T operator[](int k){return node[k+n-1];}
};
/*
 *区間更新区間取得　遅延伝播Segment Tree
    *クエリでそのノードにアクセスした時に更新する.
    *使用条件は,
        1.区間をマージしてから作用しても作用してからマージしても同じ.
        2.複数の作用をマージしてから一度にできる(add,updateなど)
    *目次
        * RMQ + RUQ
        * RMQ + RAQ
        * RSQ + RAQ
        * RSQ + RUQ
 */

/*
 *Range Minimun Query + Range Update Query
 *  区間更新は遅延配列のフラグが立っているかどうかのboolian配列が必要.
 *  verified: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_F

template<typename T>
struct LazySegmentTree{
private:
    int n;
    vector<T> node,lazy;
    vector<bool> flg;
public:
    T SUP=(1ull<<31)-1; // 初期値　
    T merge(T x,T y){
        return min(x,y);
    }
    LazySegmentTree(vector<T> v){
        int sz=(int)v.size();
        n=1; while(n<sz) n*=2;
        node.resize(2*n-1);
        lazy.resize(2*n-1,SUP);
        flg.resize(2*n-1,false);
        for(int i=0;i<sz;i++) node[i+n-1]=v[i];
        for(int i=n-2;i>=0;i--){
            node[i]=merge(node[2*i+1],node[2*i+2]);
        }
    }
    void eval(int idx,int l,int r){
        if(flg[idx]){
            node[idx]=lazy[idx];
            flg[idx]=false;
            if(r-l>1){
                // node[idx]からの伝播 
                lazy[2*idx+1]=lazy[2*idx+2]=lazy[idx];
                flg[2*idx+1]=flg[2*idx+2]=true;
            }
            lazy[idx]=0;
        }
    }
    void update(int a,int b,T x,int idx=0,int l=0,int r=-1){
        if(r<0) r=n;
        eval(idx,l,r);
        if(b<=l||r<=a) return;
        if(a<=l&&r<=b){
            lazy[idx]=x;
            flg[idx]=true;
            eval(idx,l,r);
        }else{
            update(a,b,x,2*idx+1,l,(l+r)/2);
            update(a,b,x,2*idx+2,(l+r)/2,r);
            node[idx]=merge(node[2*idx+1],node[2*idx+2]);
        }
    }
    T query(int a,int b,int idx=0,int l=0,int r=-1){
        if(r<0) r=n;
        if(b<=l || r<=a) return SUP;
        eval(idx,l,r);
        if(a<=l && r<=b) return node[idx];
        T vl = query(a,b,2*idx+1,l,(l+r)/2);
        T vr = query(a,b,2*idx+2,(l+r)/2,r);
        return merge(vl,vr);
    };
};

 * Range Minimun Query + Range Add Query
 *  verified: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H
 
template<typename T>
struct LazySegmentTree{
private:
    int n;
    vector<T> node,lazy;
public:
    T SUP=0; // 初期値
    T merge(T x,T y){
        return min(x,y);
    }
    LazySegmentTree(vector<T> v){
        int sz=(int)v.size();
        n=1; while(n<sz) n*=2;
        node.resize(2*n-1);
        lazy.resize(2*n-1,0);
        for(int i=0;i<sz;i++) node[i+n-1]=v[i];
        for(int i=n-2;i>=0;i--){
            node[i]=merge(node[2*i+1],node[2*i+2]);
        }
    }
    void eval(int idx,int l,int r){
        if(lazy[idx]!=0){
            node[idx]+=lazy[idx];
            if(r-l>1){
                // node[idx]からの伝播
                lazy[2*idx+1]+=lazy[idx];
                lazy[2*idx+2]+=lazy[idx];
            }
            lazy[idx]=0;
        }
    }
    void update(int a,int b,T x,int idx=0,int l=0,int r=-1){
        if(r<0) r=n;
        eval(idx,l,r);
        if(b<=l||r<=a) return;
        if(a<=l&&r<=b){
            lazy[idx]+=x;
            eval(idx,l,r);
        }else{
            update(a,b,x,2*idx+1,l,(l+r)/2);
            update(a,b,x,2*idx+2,(l+r)/2,r);
            node[idx]=merge(node[2*idx+1],node[2*idx+2]);
        }
    }
    T query(int a,int b,int idx=0,int l=0,int r=-1){
        if(r<0) r=n;
        if(b<=l || r<=a) return 1e15;
        eval(idx,l,r);
        if(a<=l && r<=b) return node[idx];
        T vl = query(a,b,2*idx+1,l,(l+r)/2);
        T vr = query(a,b,2*idx+2,(l+r)/2,r);
        return merge(vl,vr);
    };
};

 * Range Sum Query + Range Add Query
    * verified: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G
 

template<typename T>
struct LazySegmentTree{
private:
    int n;
    vector<T> node,lazy;
public:
    T SUP=0; // 初期値　
    T merge(T x,T y){
        return x+y;
    }
    LazySegmentTree(vector<T> v){
        int sz=(int)v.size();
        n=1; while(n<sz) n*=2;
        node.resize(2*n-1);
        lazy.resize(2*n-1,0);
        for(int i=0;i<sz;i++) node[i+n-1]=v[i];
        for(int i=n-2;i>=0;i--) node[i]=merge(node[2*i+1],node[2*i+2]);
    }
    void eval(int idx,int l,int r){
        if(lazy[idx]!=0){
            node[idx]+=lazy[idx];
            if(r-l>1){
                // node[idx]からの伝播  
                lazy[2*idx+1]+=lazy[idx]/2;
                lazy[2*idx+2]+=lazy[idx]/2;
            }
            lazy[idx]=0;
        }
    }
    void update(int a,int b,T x,int idx=0,int l=0,int r=-1){
        if(r<0) r=n;
        eval(idx,l,r);
        if(b<=l||r<=a) return;
        if(a<=l&&r<=b){
            lazy[idx]+=x*(r-l);
            eval(idx,l,r);
        }else{
            update(a,b,x,2*idx+1,l,(l+r)/2);
            update(a,b,x,2*idx+2,(l+r)/2,r);
            node[idx]=merge(node[2*idx+1],node[2*idx+2]);
        }
    }
    T query(int a,int b,int idx=0,int l=0,int r=-1){
        if(r<0) r=n;
        if(b<=l || r<=a) return 0;
        eval(idx,l,r);
        if(a<=l && r<=b) return node[idx];
        T vl = query(a,b,2*idx+1,l,(l+r)/2);
        T vr = query(a,b,2*idx+2,(l+r)/2,r);
        return merge(vl,vr);
    };
};

 *Range Sum Query + Range Update Query
   *verified: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I

template<typename T>
struct LazySegmentTree{
private:
    int n;
    vector<T> node,lazy;
    vector<bool> flg;
public:
    T SUP=0; // 初期値
    T merge(T x,T y){
        return x+y;
    }
    LazySegmentTree(vector<T> v){
        int sz=(int)v.size();
        n=1; while(n<sz) n*=2;
        node.resize(2*n-1);
        lazy.resize(2*n-1,0);
        flg.resize(2*n-1,false);
        for(int i=0;i<sz;i++) node[i+n-1]=v[i];
        for(int i=n-2;i>=0;i--) node[i]=merge(node[2*i+1],node[2*i+2]);
    }
    void eval(int idx,int l,int r){
        if(flg[idx]){
            flg[idx]=false;
            node[idx]=lazy[idx];
            if(r-l>1){
                // node[idx]からの伝播 
                lazy[2*idx+1]=lazy[idx]/2;
                lazy[2*idx+2]=lazy[idx]/2;
                flg[2*idx+1]=flg[2*idx+2]=true;
            }
            lazy[idx]=0;
        }
    }
    void update(int a,int b,T x,int idx=0,int l=0,int r=-1){
        if(r<0) r=n;
        eval(idx,l,r);
        if(b<=l||r<=a) return;
        if(a<=l&&r<=b){
            lazy[idx]=x*(r-l);
            flg[idx]=true;
            eval(idx,l,r);
        }else{
            update(a,b,x,2*idx+1,l,(l+r)/2);
            update(a,b,x,2*idx+2,(l+r)/2,r);
            node[idx]=merge(node[2*idx+1],node[2*idx+2]);
        }
    }
    T query(int a,int b,int idx=0,int l=0,int r=-1){
        if(r<0) r=n;
        if(b<=l || r<=a) return 0;
        eval(idx,l,r);
        if(a<=l && r<=b) return node[idx];
        T vl = query(a,b,2*idx+1,l,(l+r)/2);
        T vr = query(a,b,2*idx+2,(l+r)/2,r);
        return merge(vl,vr);
    };
};
*/
