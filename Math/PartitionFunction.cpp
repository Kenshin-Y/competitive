#include <bits/stdc++.h>c
using namespace std;

const long long MOD = 1e9+7;
const int MAX = 3000;
vector<vector<long long> > part(MAX, vector<long long>(MAX,0));
void PARTinit(){
    part[0][0]=1;
    for(int i=0;i<MAX;i++){
        for(int j=1;j<MAX;j++){
            if(i-j>=0){
                part[i][j] = part[i-j][j]+part[i][j-1];
                part[i][j] %= MOD;
            }else{
                part[i][j] = part[i][j-1];
                part[i][j] %= MOD;
            }
        }
    }
}
long long PART(int n,int k){
    if(k==0) return 1;
    return part[n][k];
}

/* 
//Dwango 4 qual - C : Kill/Death
signed main(){
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    PARTinit();
    int n,m; cin >> n >> m;
    vector<int> v,w;
    vector<int> a(n),b(m);
    int suma = 0,sumb = 0;
    rep(i,n){
        cin >> a[i];
        suma += a[i];
    }
    rep(i,m){
        cin >> b[i];
        sumb += b[i];
    }
    // a
    int pre = -1;
    int cnt=1;
    rep(i,n){
        if(pre!=a[i]){
            if(pre != -1) v.push_back(cnt);
            pre = a[i];
            cnt = 1;
        }else{
            cnt++;
        }
    }
    v.push_back(cnt);
    //for(auto u:v) cout << u << " "; cout << endl;
    int sz = v.size();
    vector<vector<long long > > dp1(sz+1, vector<long long>(sumb+1, 0));
    dp1[0][0]=1;
    for(int i=1;i<=sz;i++){
        for(int j=0;j<=sumb;j++){
            dp1[i][j]=0;
            for(int k=0;k<=j;k++){
                dp1[i][j] += dp1[i-1][j-k] * PART(k,v[i-1]);
                dp1[i][j] %= MOD;
            }
        }
    }
    // b
    pre = -1;
    cnt=1;
    rep(i,m){
        if(pre!=b[i]){
            if(pre != -1) w.push_back(cnt);
            pre = b[i];
            cnt = 1;
        }else{
            cnt++;
        }
    }
    w.push_back(cnt);
    sz = w.size();
    vector<vector<long long > > dp2(sz+1, vector<long long>(suma+1,0));
    dp2[0][0]=1;
    for(int i=1;i<=sz;i++){
        for(int j=0;j<=suma;j++){
            dp2[i][j]=0;
            for(int k=0;k<=j;k++){
                dp2[i][j] += dp2[i-1][j-k] * PART(k,w[i-1]);
                dp2[i][j] %= MOD;
            }
        }
    }

    ll ans = (dp1[v.size()][sumb]*dp2[w.size()][suma]) % MOD;
    cout << ans << endl;

    return 0;
}
// g++ main.cpp -o main.out && ./main.out
*/