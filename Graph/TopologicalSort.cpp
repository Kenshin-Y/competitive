/*
    @created : 2021-3
    @verifyed : todo
    @description:
        * todo
 */

#ifndef TOPOLOGICALSORT
#define TOPOLOGICALSORT
#include <bits/stdc++.h>
using namespace std;

vector<int> topological(vector<vector<int>> g)
{
    const int v = g.size();
    vector<int> indeg(v,0);
    stack<int> s;

    for(auto u:g){
        for(auto x:u){
            indeg[x]++;
        }
    }
    for(int i=0;i<v;i++){
        if(indeg[i]==0) s.push(i);
    }
    vector<int> ret;
    while(!s.empty()){
        int u=s.top(); s.pop();
        ret.emplace_back(u);
        for(auto x:g[u]){
            indeg[x]--;
            if(indeg[x]==0) s.push(x);
        }
    }
    return ret;
}
#endif // TOPOLOGICALSORT