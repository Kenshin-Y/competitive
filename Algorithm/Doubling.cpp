/*
    @created: 2020-8
    @verified:
    @description:
        全体のサイズMとして,N番目を求めるのに前処理O(MlogM)クエリO(logN)
        ret[i][j]:=jの2^i回先のもの 一回先さえ求めれば良い
        return:0からN番目の数字
        0-indexed
 */
#include <bits/stdc++.h>
using namespace std;
template<typename T>
int doubling(int st,long long k,vector<int> &a){
    const int n=(int)a.size();
    int logK=log2(k)+1;
    vector<vector<int>> ret(logK,vector<int>(n));
    rep(i,n) ret[0][i]=a[i];
    rep(j,logK-1){
        rep(i,n){
            ret[j+1][i]=ret[j][ret[j][i]];
        }
    }
    for(int j=0;k>0;j++){
        if(k&1)st=ret[j][st];
        k=k>>1;
    }
    return st;
}
