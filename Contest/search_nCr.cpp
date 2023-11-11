#include <bits/stdc++.h>
#include <ranges>
#define ll long long
#define ALL(a) (a).begin(),(a).end()
#define rep(i,n) for(int i=0;i<(n);i++)
#define rrep(i,n) for(int i=n-1;i>=0;i--)
#define fi first
#define se second
#define pb push_back
#define pii pair<int,int>
#define pll pair<long long,long long>
#define prec_out(num) cout << fixed << setprecision(20) << (num) << endl
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
using namespace std;

struct Unionfind{
    vector<int> data;
    Unionfind(int size){
        data.resize(size, -1);
    }
    bool unite(int x, int y){
        x = root(x);
        y = root(y);
        if(x != y){
            if(data[y] < data[x]) swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
        return x != y;
    }
    bool same(int x, int y){
        return root(x) == root(y);
    }
    int root(int x){
        return (data[x] < 0) ? x : data[x]=root(data[x]);
    }
    int size(int x){
        return -data[root(x)];
    }
};

int main(){
    int n,m; ll k;
    cin >> n >> m >> k;
    vector<int> v(m), u(m);
    vector<ll> c(m);
    rep(i,m) cin >> v[i] >> u[i] >> c[i];
    rep(i,m) v[i]--, u[i]--;

    // mCnの組み合わせを全探索する
    basic_string<bool> use_edges(m, false);
    ranges::fill(use_edges | views::take(n - 1), true);
    ranges::reverse(use_edges);
    ll ans = 1e18;

    do {
        // ここに処理を書く
        // use_edges[i]がtrueならば、辺iを使うということ
        ll res = 0;
        Unionfind uf(n);
        rep(i,m) {
            if (use_edges[i]) {
                uf.unite(v[i], u[i]);
                res += c[i];
                res %= k;
            }
        }
        if(uf.size(0) == n) chmin(ans, res);
    } while (ranges::next_permutation(use_edges).found);

    cout << ans << endl;
    return 0;   
}   