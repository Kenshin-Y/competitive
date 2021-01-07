/*
    @created:2020-9
    @verified: ABC177-E Coprime
    @description:
        * 通常盤:O(√N) 枝刈りもできる lcmもできる
        * Eratosthenes の篩:前処理:O(N) query:O(logN)
            * primeFact[n]:nの最小の素因数を格納　これで割って降りていく
            * preprocess() しなさい
 */
#include <bits/stdc++.h>
using namespace std;

signed main(){
    /*  通常　*/
    long long a;
    int N;
    vector<int> v(N,0);
    for(long long x=2;x*x<=a;x++){
        int cnt=0;
        while(a%x==0){
            a/=x;
            cnt++;
        }
        v[x]=max(v[x],cnt);
    }
    if(a!=1) v[a]=max(v[a],1);
}


/* Eratosthenes の篩 */
const int MAX = 10001000;
bool isPrime[MAX];
int minFact[MAX];
vector<int> preprocess(int n=MAX){
    vector<int> res;
    for(int i=0;i<n;i++){
        isPrime[i]=true;
        minFact[i]=-1;
    }
    isPrime[0]=false; minFact[0]=0;
    isPrime[1]=false; minFact[1]=1;
    for(int i=2;i<n;i++){
        if(isPrime[i]){
            minFact[i]=i;
            res.push_back(i);
            for(int j=i*2;j<n;j+=i){
                isPrime[j]=false;
                if(minFact[j]==-1) minFact[j]=i;
            }
        }
    }
    return  res;
}
vector<pair<int,int>> primeFactor(int n){
    vector<pair<int,int>> res;
    while(n!=1){
        int prime=minFact[n];
        int cnt=0;
        while(minFact[n]==prime){
            n/=prime;
            cnt++;
        }
        res.push_back({prime,cnt});
    }
    return res;
}
