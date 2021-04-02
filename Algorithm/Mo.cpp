/*
    @created: 2020-8
    @verified: Atcoder Beginers Contest 174-F Range Set query
    @description:
        * Mo's algorithm
        * クエリの処理順を工夫する [l,mid)と[mid,r)をマージできない（できるならセグ木でいい）
        * 区間の伸縮ができる場合に使える
        * lについて平方分割し、rについて順に見ていく。横にはNを√N回走り、縦は一つの点で高々√NなのでQ√N
        * 時間計算量Θ((N+Q)√N*(追加処理)) 定数倍がきつい感じ
        * クエリの処理順 sortは、pair(l/sq,r)でやる　lについて平方分割しているので、l[i]/sq==l[j]/sqはのときl[i],l[j]は同一視
        * add(x):追加操作　del(x):削除操作
*/

// todo : 復習
#include <bits/stdc++.h>
using namespace std;

int nl=0,nr=0; //[nl,nr)
auto add[&](int i){ hoge; };
auto del[&](int i){ hoge; };
for(int i:query){
    while(nl> l[i]) add(--nl);
    while(nl< l[i]) del(nl++);
    while(nr< r[i]) add(nr++);
    while(nr> r[i]) del(--nr);
    /*  結果  */
}
/*  ここまで　 */

/* 実装例　Atcoder Beginers Contest 174-F Range Set query 1229ms */
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)
#define ALL(a) (a).begin(),(a).end()
signed main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,q; cin >> n >> q;
    int sq=sqrt(n);
    vector<int> c(n);
    rep(i,n){
        cin >> c[i];
        c[i]--;
    }
    vector<int> l(q),r(q);
    rep(i,q){
        cin >> l[i] >> r[i];
        l[i]--;
    }
    
    vector<int> qu(q);
    rep(i,q) qu[i]=i;
    sort(ALL(qu),[&](int i,int j){if(l[i]/sq!=l[j]/sq) return l[i]<l[j]; else return r[i]<r[j];});

    vector<int> ans(q);
    vector<int> cnt(n,0);
    int nl=0,nr=0;
    int res=0;
    auto add=[&](int i){if(cnt[c[i]]++==0) res++;};
    auto del=[&](int i){if(--cnt[c[i]]==0) res--;};
    for(int i:qu){
        while(nl> l[i]) add(--nl);
        while(nl< l[i]) del(nl++);
        while(nr< r[i]) add(nr++);
        while(nr> r[i]) del(--nr);
        /* ここから結果 */
        ans[i]=res;
    }
    rep(i,q) cout << ans[i] << "\n";
}
