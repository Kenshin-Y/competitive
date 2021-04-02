/*
    @created : 2021-3
    @verifyed : Dwango 4 qual C
    @description:
        * 分割数 O(NM)
        * PARTinit()する. part(n,k) : n個の区別できないものを,0個を許してkグループに分割する場合の数
 */
#ifndef PARTITION
#define PARTITION
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9+7;
const int MAX = 3000;
vector<vector<long long>> part(MAX, vector<long long>(MAX,0));
void PARTinit(){
    part[0][0]=1;
    for(int i=0;i<MAX;i++){
        for(int j=1;j<MAX;j++){
            if(i-j>=0){
                // 0個を含まない(初めからj個を引いてjグループに分ける) + 0個を含む(j-1グループと同じ)
                part[i][j] = part[i-j][j]+part[i][j-1];
                part[i][j] %= MOD;
            }else{
                part[i][j] = part[i][j-1];
                part[i][j] %= MOD;
            }
        }
    }
}
long long PART(int n,int k){
    if(k==0) return 1;
    return part[n][k];
}

#endif // PARTITION