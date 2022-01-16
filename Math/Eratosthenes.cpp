/*
    @created:2020-9
    @verified: ABC177-E Coprime
    @description:
        * 前処理:O(NloglogN) query:O(logN)
        * minFact[n]:nの最小の素因数　これで割って降りていく
        * preprocess() しなさい
        * 素因数分解のクエリが大量に来るときに使う
 */
#ifndef ERATOSTHENES
#define ERATOSTHENES
#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e7;
bool isPrime[MAX];
int minFact[MAX];

vector<int> preprocess(int n = MAX)
{
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
    return res;
}
// Return : nの素因数分解
vector<pair<int,int>> primeFactor(int n)
{
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

#endif // ERATOSTHENES