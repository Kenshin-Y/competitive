/*
   @ created: 2023-3
   @ updated: 2023-3
   @ verified: ABC294-G (別解)
   @ see: https://codeforces.com/blog/entry/53170
   @ description:
       * HL分解．Heavy edge で繋がれた頂点（パス）を潰して，それらを Light edge で繋げる．
       * 分解後の木のパス長はO(logN)辿ればよい．ノードは配列なので，セグ木などでクエリ処理できる．
       * 構築 O(NlogN)，部分木クエリ O(logN)，パスクエリ O((logN)^2)．
       * :証明:
       * Lightで結ばれている子供の部分木のサイズ <= 親のサイズ/2 より，Lightを辿るとサイズが半分以下になる．
       * 半分以下になるのを足し上げればノード数 N になるので，深さは高々 O(logN)．
       * ：実装のお気持ち:
       * in[v]は頂点vにEulerTour上で何番目に訪れるか？ということ．以下 in[u]<in[v] とする．
       * lcaを考える．root[u]==root[v]なら(u,v)は同じパスにあって，in[u]の方が先に到達する（depthが小さい）ので lca=u．
       * そうでないとき，vをrootまで移してからさらに一つ上に移動させる(v=par[root[v]])ことで，vが違うパスに入る．
*/
#include <bits/stdc++.h>
using namespace std;


struct HL_decomposition{
    private:
        int n;
        vector<vector<int>> G;
        vector<int> sz, par;  // 部分木のサイズ，親頂点
        vector<int> root;     // 頂点が属するHeavy集合で，最も根に近い頂点
        vector<int> in, out;  // 頂点のEuler Tour上での始点/終点
        // 部分木のサイズを取得し，0番目の子へのパスがHeavyにする
        void dfs_size(int v, int pre){
            sz[v] = 1; par[v] = pre;
            for(auto &u:G[v]){
                if(u == pre) continue;
                dfs_size(u, v);
                sz[v] += sz[u];
                if(sz[u] > sz[G[v][0]]){
                    swap(u, G[v][0]);
                }
            }
        }
        // パスを構築
        void dfs_path(int v, int pre, int &num){
            in[v] = num; num++;
            for(auto u:G[v]){
                if(u == pre) continue;
                root[u] = (u==G[v][0] ? root[v] : u);
                dfs_path(u, v, num);
            }
            out[v] = num;
        }
    public:
        // 初期化
        HL_decomposition(vector<vector<int>> _G){
            G = _G;
            n = (int)G.size();
            sz.resize(n);  par.assign(n, -1);
            in.assign(n, -1);  out.assign(n, -1);  root.assign(n, -1);
            dfs_size(0, -1);
            root[0] = 0;
            int tmp = 0;
            dfs_path(0, -1, tmp);
        }

        inline int get_inpos(int v){ return in[v]; }
        inline int get_outpos(int v){ return out[v]; }
        inline int get_subtree_size(int v){ return sz[v]; }
        inline int get_par(int v){ return par[v]; }

        // 最近共通祖先を求める．圧縮後の高さは高々log(n)なので，同じ所に入るまで愚直に見ればよい．
        int lca(int u, int v){
            while(true){
                if(in[u]>in[v]) swap(u,v);
                if(root[u]==root[v]) return u;
                v = par[root[v]];
            }
        }

        // クエリ処理を行う．事前にサイズnのセグ木などを宣言する．
        // 例：hl.query(v, [&](int l, int r){ans+=seg.query(l,r);})

        // 頂点 v の部分木に対するクエリ処理．
        void query_subtree(int v, const function<void(int,int)> &func){
            func(in[v], out[v]);
        }
        // (u,v)パス上の**辺**に対するクエリを処理する．
        void query_edges_path(int u, int v, const function<void(int,int)> &func){
            while(true){
                if(in[u]>in[v]) swap(u,v);
                if(root[u]!=root[v]){  // パスが違う時は，vのパスを操作(func)して変更
                    func(in[root[v]], in[v]);
                    v = par[root[v]];
                }else{  // パスが同じ時は，内部の操作をして終了．
                    if(u!=v) func(in[u]+1, in[v]);
                    break;
                }
            }
        }
        // (u,v)パス上の**ノード**に対するクエリを処理する．
        void query_nodes_path(int u, int v, const function<void(int,int)> &func){
            while (true) {
                if(in[u]>in[v]) swap(u, v);
                func(max(in[root[v]], in[u]), in[v]);
                if(root[u]!=root[v]) v = par[root[v]];
                else break;
            }
        }
};