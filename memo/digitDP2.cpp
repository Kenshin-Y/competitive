#include <bits/stdc++.h>
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define ll long long
#define ALL(a) (a).begin(),(a).end()
#define rep(i,n) for(int i=0;i<(n);i++)
#define rrep(i,n) for(int i=n-1;i>=0;i--)
#define Pii pair<int,int>
#define Pll pair<long long,long long>
#define fout(num) cout << fixed << setprecision(20) << (num) << endl
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
//vector<vector<ll>> dp(n,vector<ll>(n))
//2-dim:vector<vector<Type>> vv(n, vector<Type>(m, d));
//3-dim:vector<vector<vector<Type> > > vvv(n, vector<vector<Type> >(m, vector<Type>(l, d)));

// https://atcoder.jp/contests/tdpc/submissions/18036834 を写経させていただきました。
using namespace std;
const long long MOD = 1e9+7;

ll solve(int D,string N){

    //  左から見て、そこまでの数字をMAXとして
    //  dp_0[d] := [0,MAX]のうちあまりdなものを作る操作の数え上げ
    //  dp_1[d] := [0,MAX)のうちあまりdなものを作る操作の数え上げ
    //
    //  操作は前のものから1の位をたすことなので、1の位だけ見る
    //  例えば上のdpをF0(N,d)として
    //  F0(255,6)=F0(25,6-0)+F0(25,6-1)+F0(25,6-2)+F0(25,6-3)+...
    //           +F0(24,6-7)+F0(24,6-8)+F0(24,6-9)　
    //
    //  F1(255,6)=F0(25,6-0)+...+F0(25,6-4)
    //           +F0(24,6-6)+f0(24,6-7)+...
    //  
    //  で、F0(24,x)=F1(25,x) なので,[0,N]と[0,N) 2つを持っておけばOK
    // 
    //  この25とか255はdpの添字にする必要はない　

    vector<ll> dp_0(D,0);
    vector<ll> dp_1(D,0);
    dp_0[0]=1;
    for(int i=0;i<N.size();i++){
        int a=int(N[i]-'0');
        vector<ll> newdp_0(D,0);
        vector<ll> newdp_1(D,0);
        for(int d=0;d<D;d++){
            for(int x=0;x<10;x++){
                int to = (d+x)%D;
                if(x<=a){
                    newdp_0[to] += dp_0[d];
                    newdp_0[to] %= MOD;
                }else{
                    newdp_0[to] += dp_1[d];
                    newdp_0[to] %= MOD;
                }

                if(x<a){
                    newdp_1[to] += dp_0[d];
                    newdp_1[to] %=  MOD;
                }else{
                    newdp_1[to] += dp_1[d];
                    newdp_1[to] %= MOD;
                }
            }
        }
        dp_0 = newdp_0;
        dp_1 = newdp_1;
    }
    return (dp_0[0]-1+MOD)%MOD;
}

signed main(){
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int D; cin >> D;
    string N; cin >> N;
    cout << solve(D,N) << endl;
    return 0;
}
// g++ main.cpp -o main.out && ./main.out
// ./main.out
