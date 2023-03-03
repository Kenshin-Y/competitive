/*
    @ created: 2023-3
    @ verified: AOJ DPL-1-E
    @ description:
        * 文字列 s, t の編集距離を求める．
        * 文字の置換・挿入・削除回数の最小値．
        * dp[i+1][j+1] := s[i], t[j] の編集距離．
        * 
*/

template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}

// from here

int edit_distance(string s, string t){
    int n = (int)s.size();
    int m = (int)t.size();

    vector<vector<int>> dp(n+1, vector<int>(m+1, 1e9));
    // 初期化
    for(int i=0;i<=n;i++) dp[i][0] = i;
    for(int j=0;j<=m;j++) dp[0][j] = j;

    // 更新
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            // 削除 or 挿入
            chmin(dp[i+1][j+1], dp[i][j+1] + 1);
            chmin(dp[i+1][j+1], dp[i+1][j] + 1);

            // 置換
            chmin(dp[i+1][j+1], dp[i][j] + 1);

            // 一致する場合
            if(s[i]==t[j]) chmin(dp[i+1][j+1], dp[i][j]);
        }
    }
    return dp[n][m];
}
