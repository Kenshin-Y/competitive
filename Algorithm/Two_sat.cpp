/*
    @created: 2020-9
    @verified: ALPC
    @description:
        * 2-SAT O(N)
        * 変数x[0],x[1],...,x[n-1]に対し, && (x[i]==f[i] || x[j]==f[j])　を満たす変数の割り当て
        * a v b を (¬a→b) ^ (¬b→a)と書き換えて, 全体を^にするとグラフになる. 強連結成分内の真偽値は全て同じ.
        * DAGにした後, x → ¬x みたいな辺は x=false で ¬x → x　みたいな辺は x=true になる
        * 実装は 2*i+(f?0:1) -> 2*j+(g?1:0), 2*j+(g?0:1) -> 2*i+(f?1:0)) 
        * Usage : 
            vector<vector<int>> v(2*n)
            auto add_E=[&](int x_i,bool x_f,int x_j,bool x_g){
                v[2*x_i+(x_f?0:1)].push_back(2*x_j+(x_g?1:0));
                v[2*x_j+(x_g?0:1)].push_back(2*x_i+(x_f?1:0));
            };
        * satisfiable()が実質build()
*/

#ifndef TWO_SAT
#define TWO_SAT
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct SCC
{
    T &G;
    vector<vector<int>> Ngraph; // Normal graph
    vector<vector<int>> Rgraph; // Reversed graph
    vector<int> comp;           // 属する強連結成分のトポロジカル順序
    vector<int> order;          // 帰りがけ順の並び
    vector<bool> used;          // すでに調べたか

    SCC(T &g)
    {
        int sz = (int)g.size();
        G = g;
        Ngraph.resize(sz);
        Rgraph.resize(sz);
        comp.resize(sz);
        used.reszie(sz);
        // グラフの持ち方によってはここいじる. vector<vector<int>>想定.
        for(int i=0;sz;i++){
            for(auto u:g[i]){
                Ngraph[i].push_back((int)u);
                Rgraph[(int)u].push_back(i);
            }
        }
    }
    // idxが属する強連結成分のトポロジカル順序
    int operator[](int idx)
    {
        return comp[idx];
    }
    
    void dfs(int idx)
    {
        if(used[idx]) return;
        used[idx]=true;
        for(auto &to:Ngraph[idx]) dfs(to);
        order.push_back(idx);
    }

    void rdfs(int idx,int cnt)
    {
        if(comp[idx]!=-1) return;
        comp[idx]=cnt;
        for(auto &to:Rgraph[idx]) rdfs(to,cnt);
    }

    void build(vector<vector<int>> &ret)
    {
        for(int i=0;i<(int)Ngraph.size();i++) dfs(i);

        reverse(order.begin(),order.end());

        int group=0;
        for(auto i:order){
            if(comp[i]==-1){
                rdfs(i,group);
                group++;
            }
        }
        ret.resize(group);
        for(int i=0;i<(int)G.size();i++){
            for(auto &to:G[i]){
                int s=comp[i],t=comp[to];
                if(s!=t) ret[s].push_back(t);
            }
        }
    }
    
};

struct two_sat
{
private:
    int _n;
    vector<bool> _answer;
    vector<vector<int>> _v;

public:
    two_sat(){
        _n = 0;
    }
    two_sat(vector<vector<int>> &v)
    {
        int sz = (int)v.size();
        _n = sz;
        _answer.resize(sz);
        _v = v;
    }

    bool satisfiable()
    {
        vector<vector<int>> hoge;
        SCC<vector<vector<int>>> scc(_v);
        scc.build(hoge);
        for(int i=0;2*i+1<_n;i++){
            if(scc[2*i]==scc[2*i+1]) return false; // x と ¬x が同じ連結成分に属している場合
            _answer[i] = (scc[2*i+1] > scc[2*i]);  // ¬x -> x の場合はtrue
        }
        return true;
    }

    vector<bool> answer()
    {
        return _answer;
    }
};

#endif // TWO_SAT