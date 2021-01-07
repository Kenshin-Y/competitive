/*
    @ created : 2020-21
    @ verified : ARC-042 D あまり
    @ description:
        * X^k = Y mod P なるkを求める
        * p = sqrt(P)としX^{p-1}まで求めておく
        * R = X^{-p}を計算し、a=0からY*R^a = X^b modPなるbが見つかるまで計算する
        * O(sqrt(P)logP)
 */
#include <bits/stdc++.h>
using namespace std;

long long modlog(long long x,long long y,long long MOD){
    x %= MOD;
    y %= MOD;

    long long H = sqrt(MOD);

    vector<pair<long long,long long>> baby(H);
    // Baby-step
    long long Z = y;
    for(long long a=0;a<H;a++){ //yx^(H-1)
        baby[a] = make_pair(Z,a);
        Z = (Z*x) % MOD;
    }
    sort(baby.begin(),baby.end());

    // Giant step
    long long xH=1;
    for(int i=0;i<H;i++) xH = (xH*x) % MOD;

    long long xaH = 1;
    for(int a=1;a<=(MOD/H)+1;a++){
        xaH = (xaH*xH) % MOD;
        auto itr = lower_bound(baby.begin(),baby.end(),make_pair(xaH+1,0LL));
        if(itr->second==H) continue;
        itr--;
        if(itr->first==xaH) return a*H - itr->second;
    }
    return -1;
}
