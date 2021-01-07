#include <bits/stdc++.h>
using namespace std;
//LDS 最長減少部分列
int LDS(vector<int> a){
    int n=a.size();
    deque<int> d;
    rep(i,n){
        int p=lower_bound(d.begin(), d.end(), a[i])-d.begin(); //同じやつダメ->lower_bound
        if(p==0) d.push_front(a[i]);
        else d[p-1]=a[i];
    }
    return d.size();
}
//LIS 最長増加部分列
//DPテーブルでやる 挿入場所は二分探索でやる
int LIS(vector<int> v){
    int n=v.size();
    vector<int> d;
    rep(i,n){
        int p=lower_bound(d.begin(),d.end(),v[i])-d.begin();
        if(p==d.size()) d.push_back(v[i]);
        else d[p]=v[i];
    }
    return d.size();
}

//LCS 最長共通部分列
int LCS(string s,string t){
    int n=s.size();
    int m=t.size();
    int dp[n][m];
    rep(i,n){
        rep(j,m){
            dp[i][j]=0;
        }
    }
    rep(i,n){
        rep(j,m){
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
int Edit_distance(string s,string t){
    int n=(int)s.size();
    int m=(int)t.size();
    int LP[n+1][m+1];
    rep(i,n+1){
        rep(j,m+1){
            if(i==0||j==0){
                LP[i][j]=i+j;
            }
            else LP[i][j]=1e9;
        }
    }
    rep(i,n){
        rep(j,m){
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


