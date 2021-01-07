/*
    @created:2020-9
    @verifyed: ALPC-G
    @description:
        * O(V+E)
        * dfsでorderとって、枝を逆にしてorderの降順にrdfs : 小さいorderには行けて、逆辺貼ってもいけるやろの気持ち
        * scc[i]でiが含まれる成分番号 scc[i]の昇順に塊としてトポロジカルソートされている
        * vec(V),hoge  SCC scc(vec); scc.build(hoge);
 */

template<typename T>
struct SCC{
    T &G;
    vector<vector<int>> Ngraph,Rgraph;
    vector<int> comp,order;
    vector<bool> used;
    SCC(T &g):G(g),Ngraph((int)g.size()),Rgraph((int)g.size()),comp((int)g.size(),-1),used((int)g.size()){
        for(int i=0;i<(int)g.size();i++){
            for(auto to:g[i]){
                Ngraph[i].push_back((int)to);
                Rgraph[(int)to].push_back(i);
            }
        }
    }
    int operator[](int idx){
        //assert(0<=idx&&idx<comp.size());
        return comp[idx];
    }
    
    void dfs(int idx){
        if(used[idx]) return;
        used[idx]=true;
        for(auto &to:Ngraph[idx]) dfs(to);
        order.push_back(idx);
    }
    void rdfs(int idx,int cnt){
        if(comp[idx]!=-1) return;
        comp[idx]=cnt;
        for(auto &to:Rgraph[idx]) rdfs(to,cnt);
    }
    void build( vector<vector<int>> &ret){
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
/*
 ACLC-G
 
 signed main(){
     std::cin.tie(nullptr);
     std::ios_base::sync_with_stdio(false);
     int V,E; cin >> V >> E;
     vector<vector<int>> vec(V),ans;
     rep(i,E){
         int a,b; cin >> a >> b;
         vec[a].pb(b);
     }
     SCC<vector<vector<int>>> scc(vec);
     scc.build(ans);
     vector<vector<int>> res(V);
     vector<int> num(V,0);
     int K=0;
     rep(i,V){
         if(num[scc[i]]==0) K++;
         num[scc[i]]++;
         res[scc[i]].pb(i);
     }
     cout << K << endl;
     rep(i,V){
         if(num[i]==0) break;
         cout << num[i] << " ";
         for(auto u:res[i]) cout << u << " ";
         cout << "\n";
     }
 }

 */
