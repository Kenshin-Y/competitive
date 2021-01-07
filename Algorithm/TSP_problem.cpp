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
#define rrep(i,n) for(int i=n-1;i>=0;i--)
#define fi first
#define se second
#define pb push_back
#define ppb pop_back()
#define ALL(a) (a).begin(),(a).end()
#define int long long
using namespace std;
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
typedef pair<int,int> P;
typedef pair<ll,ll> Pll;

//有向グラフ上巡回セールスマン問題
//verified
//どこから始めても一緒なので、今回は０から始める。
const ll INF=1e18;
signed main(){
    int n,m; cin >> n >> m;
    map<P,ll> mp;
    map<P,bool> ok;
    rep(i,m){
        int s,t; ll d;
        cin >> s >> t >> d;
        //from s to t
        mp[{s,t}]=d;
        ok[{s,t}]=1;
    }
    //dp[S][j]:=Sを通ってラストがjの時の、残りの経路の最短　ans:=dp[0][j] for j in [0,n)
    ll dp[1<<n][n];
    rep(i,1<<n){
        rep(j,n){
            dp[i][j]=INF;
        }
    }
    dp[(1<<n)-1][0]=0;
    rrep(i,(1<<n)){
        rep(j,n){
            rep(k,n){
                if(!ok[{j,k}]) continue;
                if(i&(1<<k)) continue;
                chmin(dp[i][j],dp[i|(1<<k)][k]+mp[{j,k}]);
            }
        }
    }
    ll res=INF;
    chmin(res,dp[0][0]);
    cout << (res==INF ? -1 : res) << endl;
}
//最短経路の数え上げ含む　双子コン#1
struct edge{
    int to;
    ll cost;
    ll time;
};
ll dp[1<<20][20];
ll memo[1<<20][20];
vector<edge> G[20];

const ll INF = 1e18;
signed main(){
    ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n,m; cin >> n >> m;
    rep(i,m){
        int s,t; ll d,ti;
        cin >> s >> t >> d  >> ti;
        s--; t--;
        G[s].pb({t,d,ti});
        G[t].pb({s,d,ti});
    }
    rep(i,1<<n)rep(j,n) dp[i][j]=INF;
    for(auto u:G[0]){
        if(u.cost<=u.time){
            dp[1<<u.to][u.to]=u.cost;
            memo[1<<u.to][u.to]=1;
        }
    }
    rep(i,1<<n){
        rep(j,n){
            if((i&(1<<j))==0) continue;
            for(auto u:G[j]){
                if(u.to==0&&(i|1)!=((1<<n)-1))  continue;
                if(i&(1<<u.to)||u.time<dp[i][j]+u.cost) continue;
                if(dp[i|(1<<u.to)][u.to]>dp[i][j]+u.cost){
                    dp[i|(1<<u.to)][u.to]=dp[i][j]+u.cost;
                    memo[i|(1<<u.to)][u.to]=memo[i][j];
                }else if(dp[i|(1<<u.to)][u.to]==dp[i][j]+u.cost){
                    memo[i|(1<<u.to)][u.to]+=memo[i][j];
                }
            }
        }
    }
    if(dp[(1<<n)-1][0]==INF){
        cout<<"IMPOSSIBLE"<<endl;
    }else{
        cout<<dp[(1<<n)-1][0]<<" "<< memo[(1<<n)-1][0] << endl;
    }
    
}
