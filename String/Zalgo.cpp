/*
    @created: 2020-9
    @verified: yosupo judge
    @description:
        * Z-algorithm
            * O(N)
            * SとS[i:]のLCP配列
*/
#ifndef ZALGO
#define ZALGO
#include <bits/stdc++.h>
using namespace std;

vector<int> Zalgo(string v)
{
    int sz=(int)v.size();
    vector<int> ret(sz,0);
    int idx=0;
    for(int i=1;i<sz;i++){
        if(i+ret[i-idx]<idx+ret[idx]) ret[i]=ret[i-idx];
        else{
            int j=max(0,idx+ret[idx]-i);
            while(i+j<sz && v[j]==v[i+j]) j++;
            ret[i]=j;
            idx=i;
        }
    }
    ret[0]=sz;
    return ret;
}
#endif // ZALGO