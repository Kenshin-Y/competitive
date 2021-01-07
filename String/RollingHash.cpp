/*
    @created: 2020-8
    @verified: ABC141-e
    @description
        * 部分文字列の一致判定の高速化
        * 構築にO(len)
        * query(l,r)=hash[l,r)
        * lcp(rhT,a,b)=Longest Common Prefix of S[a:] and T[b:] O(log(len))
        
 */
#include <bits/stdc++.h>
using namespace std;

struct RollingHash{
    static const long long base1=1007LL,base2=2009LL;
    static const long long MOD1=1000000007LL,MOD2=1000000009LL;
    vector<long long> hash1,hash2,pow1,pow2;
    RollingHash(const string &s /* ここを変える */){
        int sz=(int)s.size();
        hash1.assign(sz+1,0); hash2.assign(sz+1,0);
        pow1.assign(sz+1,1); pow2.assign(sz+1,1);
        for(int i=0;i<sz;i++){
            hash1[i+1]=(hash1[i]*base1+s[i]) % MOD1;
            hash2[i+1]=(hash2[i]*base2+s[i]) % MOD2;
            pow1[i+1]=(pow1[i]*base1) % MOD1;
            pow2[i+1]=(pow2[i]*base2) % MOD2;
        }
    }
    inline pair<long long,long long> query(int l,int r)const{
        if(l<0||r>=hash1.size()||r-l<0) return {0,0};
        long long ret1=hash1[r]-hash1[l]*pow1[r-l]%MOD1;
        ret1=(ret1+MOD1)%MOD1;
        long long ret2=hash2[r]-hash2[l]*pow2[r-l]%MOD2;
        ret2=(ret2+MOD2)%MOD2;
        return {ret1,ret2};
    }
    inline int lcp(const RollingHash &t,int a,int b)const{
        int len=min((int)hash1.size()-a,(int)hash2.size()-b);
        int ok=0,ng=len;
        while(ng-ok>1){
            int mid=(ng+ok)>>1;
            if(query(a,a+mid)==t.query(b,b+mid)) ok=mid;
            else ng=mid;
        }
        return ok;
    }
};