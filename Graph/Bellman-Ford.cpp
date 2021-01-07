#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <queue>
#include <stack>
#include <tuple>
#include <cmath>
#include <iomanip>
#include <map>
#include <cstring> //memset(dp,0,sizeof(dp))
#include <functional>
#define ll long long
#define rep(i,n) for(int i=0;i<(n);i++)
#define repp(i,n) for(int i=n-1;i>=0;i--)
#define fi first
#define se second
#define pb push_back
#define ppb pop_back()
#define ALL(a) (a).begin(),(a).end()

using namespace std;
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
typedef pair<int,int> P;
typedef pair<ll,ll> Pll;

//負の辺が存在する場合
// O(E*V)
//負閉路がスコアに寄与しないパターンを考えよう
struct edge{
    int from;
    int to;
    ll cost;
};

const int MAX_V=2525;
vector<int> to[MAX_V],from[MAX_V];
bool toN[MAX_V];
bool from1[MAX_V];
bool ok1N[MAX_V];
void dfs(int v){
    if(from1[v]) return;
    from1[v]=1;
    for(int u:to[v]){
        dfs(u);
    }
}
void rdfs(int v){
    if(toN[v]) return;
    toN[v]=1;
    for(int u:from[v]){
        rdfs(u);
    }
}

signed main(){
    int n,m;
    ll p;
    cin >> n >> m >> p;
    vector<edge> v;
    rep(i,m){
        int a,b; ll c;
        cin >> a >> b >> c;
        a--; b--;
        to[a].pb(b);
        from[b].pb(a);
        c-=p;
        edge e={a,b,-c};
        v.pb(e);
    }
    dfs(0);
    rdfs(n-1);
    rep(i,n){
        ok1N[i]=toN[i]*from1[i];
    }
    ll d[n];
    rep(i,n) d[i] = 1e18;
    d[0]=0;
    //for(auto e:v) cout << e.from <<" "<<e.to<<" "<<e.cost<<endl;
    bool ng=0;
    rep(i,n){
        rep(j,v.size()){
            edge e = v[j];
            if(!ok1N[e.to]||!ok1N[e.from]) continue;
            if(d[e.to] > d[e.from]+e.cost){
                d[e.to] = d[e.from] + e.cost;
                if(i==n-1){
                    cout << -1 << endl;
                    return 0;
                }
            }
        }
    }
    cout << max(0LL,-d[n-1]) << endl;
}
