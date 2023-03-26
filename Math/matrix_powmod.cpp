/*
    @ created: 2023-3
    @ updated: 
    @ verified: ABC293-E
    @ description:
        * 行列累乗をmod付きで行う．
        * 行列累乗はO(N^3logK) A^=3，A^3
        * フィボナッチ数やグラフのパス数など
 */
#include<bits/stdc++.h>
using namespace std;

vector<vector<long long>> mat_mul(vector<vector<long long>> a, vector<vector<long long>> b, long long mod){
    int n = a.size();
    vector<vector<long long>> ret(n, vector<ll>(n, 0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                ret[i][j] += (a[i][k]*b[k][j])%mod;
                ret[i][j] %= mod;
            }
        }
    }
    return ret;
}

vector<vector<long long>> mat_pow(vector<vector<long long>> mat, long long k, long long mod){
    int n = mat.size();
    vector<vector<long long>> ret(n, vector<long long>(n, 0));
    for(int i=0;i<n;i++) ret[i][i] = 1;
    while(k>0){
        if(k&1) ret = mat_mul(ret, mat, mod);
        mat = mat_mul(mat, mat, mod);
        k >>= 1;
    }
    return ret;
}
