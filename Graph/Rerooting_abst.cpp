/*
   @created: 2020-9
   @verified:https://atcoder.jp/contests/dp/tasks/dp_v (EDPC-V:Subtree)
   @see:https://null-mn.hatenablog.com/entry/2020/04/14/124151
   @description:
    * f,g:T×N->T
    * merge:T×T->T
    * dp_v = g(merge(f(dp_a,a),f(dp_b,b),...),v)
    * Rerooting<T> tree(n,f,merge,id,g)
    * auto f/g=[&](T a,int v){return...;};
    * auto merge=[&](T a,T b){return...;};
    * identity:merge
*/
template<typename T>
struct Rerooting{
    using F=function<T(T,int)>;
    using F2=function<T(T,T)>;
    using Graph=vector<vector<int>>;
    vector<vector<T>> dp;
    int V;
    Graph G;
    F f,g;
    F2 merge;
    T identity;
    Rerooting(int V_,F f_,F2 merge_,T identity_,F g_=[](T a,int b){return a;}) :V(V_),f(f_),g(g_),merge(merge_),identity(identity_){
        G.resize(V);
        dp.resize(V);
    }
    void add_edge(int a,int b){
        G[a].push_back(b);
        G[b].push_back(a);
    }
    void build(int root=0){
        for(int i_=0;i_<V;i_++) dp[i_].resize(G[i_].size());
        dfs1(-1,root);
        dfs2(-1,root,identity);
    }
    T dfs1(int par_,int v_){
        T dp_cum=identity;
        int sz_=(int)G[v_].size();
        for(int i_=0;i_<sz_;i_++){
            if(G[v_][i_]==par_) continue;
            dp[v_][i_]=dfs1(v_,G[v_][i_]);
            dp_cum=merge(dp_cum, f(dp[v_][i_],G[v_][i_]));
        }
        return g(dp_cum,v_);
    }
    void dfs2(int par_,int v_,T add_){
        int sz_=(int)G[v_].size();
        for(int i_=0;i_<sz_;i_++){
            if(G[v_][i_]==par_){
                dp[v_][i_]=add_;
                break;
            }
        }
        vector<T> dp_l(sz_+1,identity),dp_r(sz_+1,identity);
        for(int i_=0;i_<sz_;i_++){
            dp_l[i_+1]=merge(dp_l[i_], f(dp[v_][i_],G[v_][i_]));
        }
        for(int i_=sz_;i_>0;i_--){
            dp_r[i_-1]=merge(dp_r[i_], f(dp[v_][i_-1],G[v_][i_-1]));
        }
        for(int i_=0;i_<sz_;i_++){
            if(G[v_][i_]==par_) continue;
            T val_=merge(dp_l[i_],dp_r[i_+1]);
            dfs2(v_,G[v_][i_],g(val_,v_));
        }
    }
    T solve(int v_){
        T ans = identity;
        for(int i_=0;i_<G[v_].size();i_++) ans = merge(ans, f(dp[v_][i_], G[v_][i_]));
        return g(ans,v_);
    }
};
/*
 EDPC V 部分木の個数
 signed main(){
     int n; cin >> n;
     ll MOD; cin >> MOD;
     auto f=[&](ll a,int v){return (a+1)%MOD; };
     auto merge=[&](ll a,ll b){return (a*b)%MOD; };
     auto g=[&](ll a,int v){return a%MOD; };
     Rerooting<ll> tree(n,f,merge,1,g);
     rep(i,n-1){
         int x,y; cin >> x >> y;
         x--; y--;
         tree.add_edge(x,y);
     }
     tree.build();
     rep(i,n) cout << tree.solve(i) << endl;
 */

