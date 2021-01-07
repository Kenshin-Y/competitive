vector<int> topological(vector<vector<int>> g){
    const int v = g.size();
    vector<int> indeg(v,0);
    stack<int> s;
    for(auto u:g){
        for(auto x:u){
            indeg[x]++;
        }
    }
    rep(i,v){
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
