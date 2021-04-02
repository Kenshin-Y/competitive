/*
    @created : 2021-3
    @verified : todo
    @description:
        * よく使うDPのよせあつめ (todo : ここ書く)
*/
#ifndef LIS_LDS_LCS_EDIT
#define LIS_LDS_LCS_EDIT
#include <bits/stdc++.h>
using namespace std;

//DPテーブルの挿入場所を二分探索

//LDS 最長減少部分列 O(N)
int LDS(vector<int> v)
{
    int sz = (int)v.size();
    deque<int> d;
    for(int i=0;i<sz;i++){
        int p=lower_bound(d.begin(), d.end(), v[i])-d.begin();
        if(p==0) d.push_front(v[i]);
        else d[p-1] = v[i];
    }
    return d.size();
}

//LIS 最長増加部分列 O(N)
int LIS(vector<int> v)
{
    int sz = (int)v.size();
    vector<int> d;
    for(int i=0;i<sz;i++){
        int p=lower_bound(d.begin(),d.end(),v[i])-d.begin();
        if(p==d.size()) d.push_back(v[i]);
        else d[p]=v[i];
    }
    return d.size();
}

//LCS 最長共通部分列 O(NM)
int LCS(string s,string t)
{
    int n=s.size();
    int m=t.size();
    int dp[n][m];
    memset(dp,0,sizeof(dp));

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(s[i]==t[j]){
                if(i>0&&j>0) dp[i][j]=dp[i-1][j-1]+1;
                else dp[i][j]=1;
            }
            else{
                if(i>0&&j>0) dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
                else if(i>0) dp[i][j]=dp[i-1][j];
                else if(j>0) dp[i][j]=dp[i][j-1];
            }
        }
    }
    return dp[n-1][m-1];
}

// 編集距離
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
int Edit_distance(string s,string t)
{
    int n=(int)s.size();
    int m=(int)t.size();
    int LP[n+1][m+1]; // 1-indexed
    for(int i=0;i<n+1;i++){
        for(int j=0;j<m+1;j++){
            if(i==0||j==0){
                LP[i][j]=i+j;
            }
            else LP[i][j]=1e9;
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
        {
            //delete or insert
            chmin(LP[i+1][j+1],LP[i][j+1]+1);
            chmin(LP[i+1][j+1],LP[i+1][j]+1);

            //replace
            chmin(LP[i+1][j+1],LP[i][j]+1);

            //same
            if(s[i]==t[j]) chmin(LP[i+1][j+1],LP[i][j]);
        }
    }
    return LP[n][m];
}

#endif // LIS_LDS_LCS_EDIT
