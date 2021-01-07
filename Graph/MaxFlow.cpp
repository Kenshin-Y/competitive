/*
    @created:2020-9
    @verified: AOJ GRL_6_A
    @description:
        * Dinic: O(EV^2)
        * Ford_fulkerson: O(FE)
        * add_edge(from,to,capacity)
        * get_edge(id) = from,to,cap,flow
 */
template<typename T>
struct Dinic{
    struct edge{
        int to,rev;
        T cap;
    };
    vector<vector<edge>> G;
    vector<pair<int, int>> pos;
    vector<int> level; //dist
    vector<int> iter; //visited
    const T INF;
    Dinic(int n):INF(numeric_limits<T>::max()){
        G.resize(n);
    }
    void add_edge(int from,int to, T cap){
        pos.push_back({from,G[from].size()});
        G[from].push_back(edge{to,int(G[to].size()),cap});
        G[to].push_back(edge{from,int(G[from].size()-1),0});
    }
    struct Edge{
        int to,rev;
        T cap,flow;
    };
    Edge get_edge(int x){
        auto _e = G[pos[x].first][pos[x].second];
        auto _re = G[_e.to][_e.rev];
        /* from,to,cap,flow */
        return (Edge){pos[x].first, _e.to, _e.cap + _re.cap, _re.cap};
    }
    bool bfs(int s,int t){
        level.assign(G.size(),-1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while(!que.empty()) {
          int fr = que.front();
          que.pop();
          for(auto &e : G[fr]) {
            if(e.cap > 0 && level[e.to] == -1) {
              level[e.to] = level[fr] + 1;
              que.push(e.to);
            }
          }
        }
        return (level[t] != -1);
    }
    T dfs(int idx,const int t,T flow){
        if(idx==t) return flow;
        for(int &i=iter[idx];i<G[idx].size();i++){
            edge &e=G[idx][i];
            if(e.cap>0 && level[idx]<level[e.to]){
                T resflow=dfs(e.to,t,min(flow,e.cap));
                if(resflow>0){
                    e.cap-=resflow;
                    G[e.to][e.rev].cap+=resflow;
                    return resflow;
                }
            }
        }
        return 0;
    }
    T max_flow(int s,int t,T lim){
        T retflow=0;
        while(retflow<lim&&bfs(s,t)){
            iter.assign(G.size(),0);
            if(level[t]<0) return retflow;
            T flow=0;
            while((flow=dfs(s,t,lim-flow))>0){
                retflow+=flow;
            }
        }
        return retflow;
    }
    T max_flow(int s,int t){ return max_flow(s,t,INF); }
};

template<typename T>
struct Ford_Fulkerson{
    struct edge{
        int to,rev;
        T cap;
    };
    vector<vector<edge>> G;
    vector<pair<int, int>> pos;
    vector<bool> used;
    //e=G[v][i]はi番目のedgeで、G[v][e.to]を繋いでおり、逆辺はG[v][rev]
    Ford_Fulkerson(int n){
        G.resize(n);
    }
    void add_edge(int from,int to,T cap){
        pos.push_back({from,G[from].size()});
        G[from].push_back((edge){to,(int)G[to].size(),cap});
        G[to].push_back((edge){from,(int)(G[from].size()-1),0});
    }
    struct Edge{
        int to,rev;
        T cap,flow;
    };
    Edge get_edge(int x){
        auto _e = G[pos[x].first][pos[x].second];
        auto _re = G[_e.to][_e.rev];
        /* from,to,cap,flow */
        return (Edge){pos[x].first, _e.to, _e.cap + _re.cap, _re.cap};
    }
    /* 増加パスの探索 from v to t */
    T dfs(int v,int t,T f){
        if(v==t) return f;
        used[v]=true;
        for(auto &e:G[v]){
            if(!used[e.to] && e.cap>0){ //通れる
                int d=dfs(e.to,t,min(e.cap,f));
                if(d>0){
                    e.cap-=d;
                    G[e.to][e.rev].cap+=d;
                    return d;
                }
            }
        }
        return 0;
    }
    T max_flow(int s,int t,T lim){
        T flow=0;
        while(flow<lim){
            used.assign(G.size(),false);
            T f=dfs(s,t,lim-flow);
            if(f==0) return flow;
            flow+=f;
        }
        return flow;
    }
    T max_flow(int s,int t){ return max_flow(s,t,numeric_limits<T>::max());  }
};
