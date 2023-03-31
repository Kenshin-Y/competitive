/*
   @ created: 2021-3
   @ updated:  2023-3
   @ verified: todo
   
   @ description:
       * オイラーツアーを辿って，木の共通祖先(LCA)をO(logN)で求めることができる．
       * LCAを用いると木の2点間の距離がわかる．d(u)+d(v)-2*d(lca). 
       * 辺に重みを追加したいときは適宜関数を追加すること．
*/
#include <bits/stdc++.h>
using namespace std;


struct Range_min_tree{
    private:
        int n;
        vector<pair<int,int>> node;  // {depth,index}

    public:
        void init(vector<pair<int,int>> v){
            int sz = (int)v.size();
            n = 1;
            while(n<sz) n *= 2;
            node.resize(2*n-1);
            for(int i=0;i<sz;i++) node[n+i-1] = v[i];
            for(int i=n-2;i>=0;i--) node[i] = min(node[2*i+1],node[2*i+2]);
        }

        pair<int,int> query(int a,int b,int idx=0,int l=0,int r=-1){ // RMQ[a,b)
            if(r<0) r = n;
            if(r<=a || b<=l) return {INT_MAX,-1};
            if(a<=l && r<=b) return node[idx];
            pair<int,int> ql = query(a,b,2*idx+1,l,(l+r)/2);
            pair<int,int> qr = query(a,b,2*idx+2,(l+r)/2,r);
            return min(ql,qr);
        }
};

// 木に関するライブラリ．
// 無向グラフ vector<vector<int>> を渡せばOK．distとかは適宜なおせ．
struct Tree_dist{

    private:
        int size;
        vector<int> euler_tour, idx, depth;
        vector<vector<int>> tree;
        Range_min_tree rm_tree;

        void dfs(int v, int pre, int dep){
            idx[v] = (int)euler_tour.size(); // 最後に訪れた場所
            euler_tour.push_back(v);
            depth[v] = dep;
            for(int u:tree[v]){
                if(u != pre){
                    dfs(u, v, dep+1);
                    euler_tour.push_back(v); // return
                }
            }
        }

    public:
        Tree_dist(vector<vector<int>> tree){
            size = (int)tree.size();
            idx.resize(2*size-2);
            depth.resize(2*size-2);
            euler_tour.reserve(2*size-2);
            fill(idx.begin(),idx.end(),-1);
            vector<pair<int,int>> v(2*size-2);
            for(int i=0;i<size;i++){
                if(idx[i]<0){
                    dfs(i,-1,0);
                }
            }
            for(int i=0;i<2*size-2;i++){
                v[i] = {depth[euler_tour[i]],i};
            }
            rm_tree.init(v);
        }
        // lca
        int lca(int u, int v){
            return euler_tour[rm_tree.query(min(idx[u],idx[v]), max(idx[u],idx[v]+1)).second];
        }
        // dist
        int dist(int u, int v){
            int lc = lca(u,v);
            return depth[u]+depth[v]-2*depth[lc];
        }
};
