#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define Pll pair<long long,long long>

#define INF 1e+9
struct edge{
    int to;
    ll cost;
};
int n;
ll d[1001001];
vector<edge> G[1001001];
void dijkstra(int s){
    fill(d,d+n,INF);
    priority_queue<Pll,vector<Pll>,greater<Pll>> pq; //{dist,v}
    d[s]=0;
    pq.push({0,s});
    while(!pq.empty()){
        Pll tp=pq.top(); pq.pop();
        int v=(int)tp.second;
        if(d[v]<tp.first) continue;
        for(auto u:G[v]){
            if(d[v]+u.cost<d[u.to]){
                d[u.to]=d[v]+u.cost;
                pq.push({d[u.to],u.to});
            }
        }
    }
}
/*
struct edge{
    int to,di,cost;
    bool operator<(const edge &a)const{return a.di<di;}
};
int n,m,L;
int dist[111][111]; //ver,cost mindist
vector<edge> G[111];
void dijkstra(int s){
    rep(i,n)rep(j,L+1)dist[i][j]=MAX;
    priority_queue<edge> pq;
    pq.push({s,0,0});
    dist[s][0]=0;
    while(!pq.empty()){
        auto tp=pq.top(); pq.pop();
        for(auto u:G[tp.to]){
            if(dist[tp.to][tp.cost]<tp.di) continue;
            if(u.cost+tp.cost<=L&&dist[tp.to][tp.cost]<dist[u.to][u.cost+tp.cost]){ //払う
                dist[u.to][u.cost+tp.cost]=dist[tp.to][tp.cost];
                pq.push({u.to,dist[u.to][u.cost+tp.cost],u.cost+tp.cost});
            }
            if(dist[tp.to][tp.cost]+u.di<dist[u.to][tp.cost]){ //払わない
                dist[u.to][tp.cost]=dist[tp.to][tp.cost]+u.di;
                pq.push({u.to,dist[u.to][tp.cost],tp.cost});
            }
        }
    }
}
*/