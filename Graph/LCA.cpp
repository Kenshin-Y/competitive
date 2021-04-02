/*
   @created: 2021-3
   @verified: todo
   
   @description:
       * todo
*/
#ifndef LCA_CPP
#define LCA_CPP
#include <bits/stdc++.h>
using namespace std;

struct RMQ
{
private:
    int n;
    vector<pair<int,int>> node; // {depth,index}

public:
    void init(vector<pair<int,int>> v)
    {
        int sz = (int)v.size();
        n = 1;
        while(n<sz) n *= 2;
        node.resize( 2*n-1 );
        for(int i=0;i<sz;i++) node[n+i-1] = v[i];
        for(int i=n-2;i>=0;i--) node[i] = min(node[2*i+1],node[2*i+2]);
    }

    pair<int,int> query(int a,int b,int idx=0,int l=0,int r=-1) // RMQ[a,b)
    {
        if(r<0) r = n;
        if(r<=a || b<=l) return {INT_MAX,-1};
        if(a<=l && r<=b) return node[idx];
        pair<int,int> ql = query(a,b,2*idx+1,l,(l+r)/2);
        pair<int,int> qr = query(a,b,2*idx+2,(l+r)/2,r);
        return min(ql,qr);
    }

};

struct LCA
{
private:
    int n;
    vector<int> EulerTour,idx,depth;
    vector<vector<int>> _G;
    RMQ Rmq;

    void dfs(int v,int pre,int dep) // Euler Tour を取る
    {
        idx[v] = (int)EulerTour.size(); // 最後に訪れた場所
        EulerTour.push_back(v);
        depth[v] = dep;
        for(int u:_G[v]){
            if(u != pre){
                dfs(u,v,dep+1);
                EulerTour.push_back(v); // return
            }
        }
    }

public:
    LCA(vector<vector<int>> G):_G(G)
    {
        n = (int)G.size();
        idx.resize(2*n-2);
        depth.resize(2*n-2);
        EulerTour.reserve(2*n-2);
        fill(idx.begin(),idx.end(),-1);
        vector<pair<int,int>> v(2*n-2);
        for(int i=0;i<n;i++){
            if(idx[i]<0){
                dfs(i,-1,0);
            }
        }
        for(int i=0;i<2*n-2;i++){
            v[i] = {depth[EulerTour[i]],i};
        }
        Rmq.init(v);
    }

    int lca(int u,int v)
    {
        return EulerTour[Rmq.query(min(idx[u],idx[v]),max(idx[u],idx[v])+1).second];
    }

    int dist(int u,int v)
    {
        int lc=lca(u,v);
        return depth[u]+depth[v]-2*depth[lc];
    }

};
#endif // LCA_CPP