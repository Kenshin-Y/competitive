#include <bits/stdc++.h>
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define ll long long
#define ALL(a) (a).begin(),(a).end()
#define rep(i,n) for(int i=0;i<(n);i++)
#define rrep(i,n) for(int i=n-1;i>=0;i--)
#define Pii pair<int,int>
#define Pll pair<long long,long long
#define fout(num) cout << fixed << setprecision(20) << (num) << endl
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
//vector<vector<ll>> dp(n,vector<ll>(n))
//2-dim:vector<vector<Type>> vv(n, vector<Type>(m, d));
//3-dim:vector<vector<vector<Type>>> vvv(n, vector<vector<Type>>(m, vector<Type>(l, d)));

using namespace std;
constexpr int D = 365;
int score[D][26];
int penalty[26];

void input(){
    int d; cin >> d;
    rep(i,26) cin >> penalty[i];
    rep(i,d)rep(j,26) cin >> score[i][j];
}

/* スコア計算 */
ll calc_score(vector<int> s){
    int sz=(int)s.size();
    vector<int> lst(26,-1);
    ll ret=0;
    rep(i,sz){
        ret+=score[i][s[i]];
        lst[s[i]]=i;
        rep(j,26){
            ret-=(penalty[j]*(i-lst[j]));
        }
    }
    return max(0LL,ret+(ll)1e6);
}
/* 貪欲 */
vector<int> solve1(){
    vector<int> lst(26,-1);
    vector<int> ret;
    rep(i,D){
        int event=0;
        ll resmax=-1e9;
        rep(j,26){
            ll res=score[i][j];
            rep(k,26){
                if(j!=k) res-=penalty[k]*(i-lst[k]);
            }
            if(resmax<res){
                resmax=res;
                event=j;
            }
        }
        ret.push_back(event);
        lst[event]=i;
    }
    return ret;
}
/* 評価関数を作成した貪欲 */
/* X日後まで何も開催しなかった場合のスコアのうち最大 */
vector<int> solve2(int avarage_day){
    vector<int> lst(26,-1);
    vector<int> ret;
    rep(i,D){
        int event=0;
        ll resmax=-1e18;
        rep(j,26){
            ll res=score[i][j];
            int tmp=lst[j];
            lst[j]=i;
            rep(k,avarage_day){
                if(i+k>D) break;
                rep(l,26){
                    if(j!=l||k!=0)res-=penalty[l]*(i+k-lst[l]);
                }
            }
            lst[j]=tmp;
            if(resmax<res){
                resmax=res;
                event=j;
            }
        }
        ret.push_back(event);
        lst[event]=i;
    }
    return ret;
}
/* 局所探索 */
vector<int> LocalSearch(){
    vector<int> ret;
    return ret;
}

/* 焼きなまし法 */
vector<int> Annealing(){
    vector<int> ret;
    return ret;
}



signed main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    input();
    vector<int> ans(D);
    ll sum_score=0;
    for(int i=1;i<=26;i++){
        vector<int> v=solve2(i);
        if(sum_score < calc_score(v)){
            sum_score = calc_score(v);
            ans=v;
        }
    }
    for(auto u:ans) cout << u+1 << " ";
    cout << "\n";
    //cout << calc_score(ans) << endl;
    return 0;
}
// g++ main.cpp -o main.out && ./main.out
// g++ main.cpp -o main.out && ./main.out <sample2.in> output.txt