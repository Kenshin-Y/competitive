/*
    @ created: 2023-3
    @ verified: EDPC-F
    @ description:
        * 文字列 s, t の最長共通部分列を求める．
        * dp[i][j] := s[i], t[j] までのLCSの長さ．
        * 長さのみ返す実装，復元文字列を返す実装
*/

// 長さのみ返す
int LCS(string s, string t){
    int n = s.size();
    int m = t.size();
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(s[i]==t[j]){
                if(i>0 && j>0) dp[i][j] = dp[i-1][j-1] + 1;
                else dp[i][j] = 1;
            }else{
                if(i>0 && j>0) dp[i][j] = max(dp[i][j-1],dp[i-1][j]);
                else if(i>0) dp[i][j] = dp[i-1][j];
                else if(j>0) dp[i][j] = dp[i][j-1];
            }
        }
    }
    return dp[n-1][m-1];
}

// dpの復元
string LCS(string s, string t){
    int n = s.size();
    int m = t.size();
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(s[i]==t[j]){
                if(i>0 && j>0) dp[i][j] = dp[i-1][j-1] + 1;
                else dp[i][j] = 1;
            }else{
                if(i>0 && j>0) dp[i][j] = max(dp[i][j-1],dp[i-1][j]);
                else if(i>0) dp[i][j] = dp[i-1][j];
                else if(j>0) dp[i][j] = dp[i][j-1];
            }
        }
    }
    string ans = "";
    for(int i=n-1,j=m-1;ans.size()!=dp[n-1][m-1];){
        if(s[i]==t[j]){
            ans += s[i];
            i--;
            j--;
        }else if(i>0 && dp[i][j]==dp[i-1][j]){
            i--;
        }else if(j>0 && dp[i][j]==dp[i][j-1]){
            j--;
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
