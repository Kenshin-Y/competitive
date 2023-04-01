/*
    @ created: 2023-3
    @ verified: Library Checker
    @ description:
        * 最長増加部分列．増加部分列の index 配列を返す．O(NlogN)．
        * dp[i] := 増加部分列の長さが i のときの数列の最終要素の min
        * dpは増加列になるので，更新は二分探索でやる．挿入ソートっぽい？
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> LIS(vector<int> v){
    int sz = (int)v.size();
    vector<int> dp;
    vector<int> idx(sz,-1);
    for(int i=0;i<sz;i++){
        int p = int(lower_bound(dp.begin(),dp.end(), v[i]) - dp.begin());
        idx[i] = p;
        if(p == dp.size()){
            dp.push_back(v[i]);
        }else if(dp[p] > v[i]){
            dp[p] = v[i];
        }
    }
    vector<int> lis(dp.size());
    for(int i=sz-1,len=lis.size()-1;i>=0;i--){
        if(idx[i]==len){
            lis[len] = i;
            len--;
        }
    }
    return lis;
}

// 長さのみ返すLIS
int LIS(vector<int> v){
    int sz = (int)v.size();
    vector<int> dp;
    for(int i=0;i<sz;i++){
        int p = int(lower_bound(dp.begin(),dp.end(), v[i]) - dp.begin());
        if(p == dp.size()){
            dp.push_back(v[i]);
        }else if(dp[p] > v[i]){
            dp[p] = v[i];
        }
    }
    return (int)dp.size();
}
