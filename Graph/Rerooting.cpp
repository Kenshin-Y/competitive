/*
   @created: 2020-8
   @verified:https://atcoder.jp/contests/dp/tasks/dp_v (EDPC-V:Subtree)
   @see:algo-logic.info/tree-dp
   @description:
    * 書き換えについて
    * identity:mergeに関する単位元
    * merge: dp_cumは累積　dは部分木
    * add_root: mergeしたものを利用してdp[v]を計算　端はadd_root(identity)
*/

// 例:部分木の個数dp[i][j]

#ifndef REROOTING
#define REROOTING
#include <bits/stdc++.h>
using namespace std;

struct Rerooting
{
    /*  begin here  */
    struct DP
    {
        long long dp;
        int num;
        DP(long long dp_,int num_):dp(dp_),num(num_){}
    };

    const DP identity=DP(0,0);

    function<DP(DP,DP)> merge = [](DP dp_cum,DP d) -> DP
    {
        return DP(dp_cum.dp+d.dp+d.num, dp_cum.num+d.num);
    };

    function<DP(DP)> add_root = [](DP d) -> DP
    {
        return DP(d.dp,d.num+1);
    };
    /*  end here   */
    
    struct Edge{
        int to;
    };
    using Graph=vector<vector<Edge>>;
    vector<vector<DP>> dp; //dp[i][j]:=from i number j path
    vector<DP> ans;
    Graph G;

    Rerooting(int N)
    {
        G.resize(N);
        dp.resize(N);
        ans.assign(N,identity);
    }

    void add_edge(int a,int b)
    {
        G[a].push_back({b});
    }

    void build()
    {
        dfs(0);
        dfs2(0,identity);
    }

    DP dfs(int _v,int _par=-1)
    {
        DP dp_cum=identity; //累積をとる
        int _sz=(int)G[_v].size();
        dp[_v]=vector<DP>(_sz,identity);
        for(int _i=0;_i<_sz;_i++){
            int _u=G[_v][_i].to;
            if(_u==_par) continue;
            dp[_v][_i]=dfs(_u,_v);
            dp_cum=merge(dp_cum,dp[_v][_i]);
        }
        return add_root(dp_cum);
    }

    void dfs2(int _v,const DP& dp_p,int _par=-1)
    {
        int _sz=(int)G[_v].size();
        for(int _i=0;_i<_sz;_i++){
            if(G[_v][_i].to==_par) dp[_v][_i]=dp_p;
        }
        vector<DP> dp_l(_sz+1,identity),dp_r(_sz+1,identity);
        for(int _i=0;_i<_sz;_i++){
            dp_l[_i+1]=merge(dp_l[_i],dp[_v][_i]);
        }
        for(int _i=_sz-1;_i>=0;_i--){
            dp_r[_i]=merge(dp_r[_i+1],dp[_v][_i]);
        }
        ans[_v]=add_root(dp_l[_sz]);
        for(int _i=0;_i<_sz;_i++){
            int _u=G[_v][_i].to;
            if(_u==_par) continue;
            dfs2(_u,add_root(merge(dp_l[_i],dp_r[_i+1])),_v);
        }
    }
    /*   Begin here   */
    long long solve(int v)
    {
        long long res=0;
        for(int j=0;j<dp[v].size();j++){
            res += pow(2,dp[v][j].dp);
            res %= 998244353;
        }
        return res;
    }
    /*   End here   */
};
#endif //REROOTING


