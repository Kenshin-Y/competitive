/*
   @created:2020-9
   @verified: AOJ GRL_6_B,ALPC-E, ACL1-C
   @description:
        * O(FElogV)
        * add_edge(from,to,capacity,cost)
        * min_cost_flow(s,t,flow)
        * dijkstra内のPのboolianは直感と逆にしている(priority_queueのため)ので注意
        * 辺の情報:from iはfor(auto e:fl.G[i]){ e.to,e.cap,e.rev }
        * flow以下:s->t, cost:0 cap:inf
        * 負コスト渡してもOK
*/
template<typename Tflow,typename  Tcost>
struct PrimalDual{
    struct edge{
        int to,rev;
        Tflow cap;
        Tcost cost;
    };
    vector<vector<edge>> G;
    vector<Tcost> dist,potential;
    vector<int> prevV,prevE;
    /* 直前の頂点と辺　*/
    Tcost INF_cost;
    PrimalDual(int n):G(n),dist(n),potential(n),prevV(n),prevE(n),INF_cost(numeric_limits<Tcost>::max()){}
    
    void add_edge(int from,int to,Tflow cap,Tcost cost){
        G[from].push_back((edge){to,int(G[to].size()),cap,cost});
        G[to].push_back((edge){from,int(G[from].size()-1),0,-cost});
    }
    void dijkstra(int s){
        struct my_P{
            Tcost first;
            int second;
            my_P(Tcost first,int second):first(first),second(second){}
            bool operator<(const my_P &a)const{return a.first<first;}
        };
        priority_queue<my_P> que;
        fill(dist.begin(),dist.end(),INF_cost);
        dist[s]=0;
        que.push(my_P{dist[s],s});
        while(!que.empty()){
            my_P fr=que.top(); que.pop();
            int v=fr.second;
            if(dist[v]<fr.first) continue;
            for(int i=0;i<(int)G[v].size();i++){
                edge &e=G[v][i];
                if(e.cap==0) continue;
                if(dist[v]+e.cost+potential[v]-potential[e.to]<dist[e.to]){
                    dist[e.to]=dist[v]+e.cost+potential[v]-potential[e.to];
                    prevV[e.to]=v;
                    prevE[e.to]=i;
                    que.push((my_P){dist[e.to],e.to});
                }
            }
        }
    }
    Tcost min_cost(int s,int t,Tflow f){
        Tcost ret=0;
        fill(potential.begin(),potential.end(),0);
        while(f>0){
            dijkstra(s);
            if(dist[t]==INF_cost){
                return ret;
            }
            for(int v=0;v<(int)potential.size();v++){
                if(dist[v]<INF_cost) potential[v]+=dist[v];
            }
            Tflow d=f;
            for(int v=t;v!=s;v=prevV[v]){
                d=min(d,G[prevV[v]][prevE[v]].cap);
            }
            f-=d;
            ret+=potential[t]*d;
            for(int v=t;v!=s;v=prevV[v]){
                edge &e=G[prevV[v]][prevE[v]];
                e.cap-=d;
                G[v][e.rev].cap+=d;
            }
        }
        return ret;
    }
};
