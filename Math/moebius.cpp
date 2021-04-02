/*
    @created: 2021-3
    @see: 蟻本 p265
    @verified: None
    @description:
        * メビウス関数 O(sqrt(n))
        * g(n) = Σ f(d) for d|n, f(n) = Σ μ(n/d)*g(d) for d|n なるμを返す
        * Args: long long : n
        * Return: map<long long, int> : map[nの約数] = val
*/
#ifndef MOEBIUS
#define MOEBIUS
#include <bits/stdc++.h>
using namespace std;

// todo: verify
map<long long, int> moebius(long long n)
{
    map<long long, int> ret;
    vector<long long> primes;
    for(long long i=2; i*i<=n; i++){
        if(n%i==0){
            primes.push_back(i);
            while(n%i==0) n /= i;
        }
    }
    if(n!=1) primes.push_back(n);

    int sz = (int)primes.size();
    for(int i=0; i<(1<<sz); i++){
        int mu = 1, d = 1;
        for(int j=0; j<sz; j++){
            if((1<<j)&i){
                mu *= -1;
                d *= primes[j];
            }
        }
        ret[d] = mu;
    }
    return ret;
}
#endif // MOEBIUS