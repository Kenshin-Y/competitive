/*
    @created: 2020-9
    @ updated: 2022-3
    @verified: AOJ DSL
    @description:
        * node: f: T×T -> T, g: T×E -> T
        * lazy: h: E×E -> E
        * p(a,b) := g(a,a,a,...,a) E×N -> E
        * 内部実装は1-indexed 実装は0-indexedでOK
        * 単位元はg,hについて
        * int sz=1; while(sz<n) sz*=2;
        * vector<T> v(sz);
        * LazySegmentTree<T,E> lst(f,g,h,idT,idE);
        * lst.build(v);
        *
*/
#include <bits/stdc++.h>
using namespace std;

// code from here
template<typename T,typename E>
struct LazySegmentTree
{
    using F = function<T(T,T)>;
    using G = function<T(T,E)>;
    using H = function<E(E,E)>;
    int sz_,height;
    F f; G g; H h;
    T identity_T;
    E identity_E;
    vector<T> node;
    vector<E> lazy;
    LazySegmentTree(F f_,G g_,H h_,T identity_T_,E identity_E_):
        f(f_),g(g_),h(h_),identity_T(identity_T_),identity_E(identity_E_){}

    void init(int n_)
    {
        sz_=1; height=0;
        while(sz_<n_){ sz_<<=1; height++; }
        node.assign(2*sz_,identity_T);
        lazy.assign(2*sz_,identity_E);
    }
    void build(vector<T> &v)
    {
        int n_=(int)v.size();
        init(n_);
        for(int i_=0;i_<sz_;i_++){
            node[sz_+i_]=v[i_];
        }
        for(int i_=sz_-1;i_;i_--){
            node[i_]=f(node[(i_<<1)|0],node[(i_<<1)|1]);
        }
    }

    inline T reflect(int k_)
    {
        return lazy[k_]==identity_E ? node[k_] :g(node[k_],lazy[k_]);
    }

    inline void thrust(int k_)
    {
        for(int i_=height;i_;i_--) eval(k_>>i_);
    }

    inline void recalc(int k_)
    {
        while(k_>>=1){
            node[k_]=f(reflect((k_<<1)|0),reflect((k_<<1)|1));
        }
    }

    inline void eval(int k_)
    {
        if(lazy[k_]==identity_E) return;
        lazy[(k_<<1)|0]=h(lazy[(k_<<1)|0],lazy[k_]);
        lazy[(k_<<1)|1]=h(lazy[(k_<<1)|1],lazy[k_]);
        node[k_]=reflect(k_);
        lazy[k_]=identity_E;
    }

    void update(int a,int b,E x_)
    {
        thrust(a+=sz_);
        thrust(b+=sz_-1);
        for(int l=a,r=b+1;l<r;l>>=1,r>>=1){
            if(l&1){ lazy[l]=h(lazy[l],x_); ++l; }
            if(r&1){ --r; lazy[r]=h(lazy[r],x_); }
        }
        recalc(a);
        recalc(b);
    }

    void set_val(int a,T x)
    {
      thrust(a+=sz_);
      node[a]=x; lazy[a]=identity_E;
      recalc(a);
    }

    T query(int a,int b)
    {
      //assert(0<=a&&a<=b&&b<=sz_);
      thrust(a+=sz_);
      thrust(b+=sz_-1);
      T vl=identity_T,vr=identity_T;
      for(int l=a,r=b+1;l<r;l>>=1,r>>=1) {
        if(l&1) vl=f(vl,reflect(l++));
        if(r&1) vr=f(reflect(--r),vr);
      }
      return f(vl,vr);
    }
};

#endif // LAZYSEGMENTTREE

/*  Sample
 *  
 *  sumは区間長を持ちたいのでpairで持っておく updateは更新されないような単位元を持っておく
 *
 *  Range add Range sum
 *  T:Pll E:ll
 *  auto f=[](Pll a,Pll b){return Pll{a.fi+b.fi,a.se+b.se};};
 *  auto g=[](Pll a,ll b){return Pll{a.fi+a.se*b,a.se};};
 *  auto h=[](ll a,ll b){return a+b;};
 *
 *  Range add Range min
 *  auto f=[](ll a,ll b){return min(a,b);};
 *  auto g=[](ll a,ll b){return a+b;};
 *  auto h=[](ll a,ll b){return a+b;};
 *
 *  Range update Range sum
 *  auto f=[](Pll a,Pll b){return Pll{a.fi+b.fi,a.se+b.se}; };
 *  auto g=[](Pll a,ll b){return Pll{a.se*b,a.se}; };
 *  auto h=[](ll a,ll b){return b; };
 *
 *  Range update Range min
 *  auto f=[](ll a,ll b){return min(a,b);};
 *  auto g=[](ll a,ll b){return b;};
 *  auto h=[](ll a,ll b){return b; };
 *
 *  Range affine Range sum
 *  auto f=[](Pll a,Pll b){
 *      return Pll{(a.fi+b.fi)%MOD,a.se+b.se};
 *   };
 *  auto g=[](Pll a,Pll b){
 *    return Pll{(a.fi*b.fi+b.se*a.se)%MOD,a.se};
 *  };
 *  auto h=[](Pll a,Pll b){
 *    return Pll{(a.fi*b.fi)%MOD,(a.se*b.fi+b.se)%MOD};
 *  };
 */


