/*
    @ created:2020-9
    @ updated:2023-3
    @ description:
        * gcd: O(logN)
        * lcm: O(logN)
        * powmod: O(logN)
        * my_pow: O(logN) modなし
        * extgcd: O(logN) 参照渡しすることで，ax+by=gcd(a,b) なる (x,y) が格納される．
*/
#include <bits/stdc++.h>
using namespace std;

long long gcd(long long a, long long b){
    if(b == 0) return a;
    return gcd(b, a%b);
}

long long lcm(long long a, long long b){
    return a/gcd(a,b)*b;
}

long long powmod(long long x, long long n, long long MOD){
    long long ret = 1;
    while(n > 0){
        if(n&1){
            ret *= x;
            ret %= MOD;
            n -= 1;
        }else{
            x *= x;
            x %= MOD;
            n >>= 1;
        }
    }
    return ret;
}

long long my_pow(long long x, long long n){
    long long ret=1;
    while(n > 0){
        if(n&1){
            ret *= x;
            n -= 1;
        }else{
            x *= x;
            n >>= 1;
        }
    }
    return ret;
}

int extgcd(int a, int b, int &x, int &y){
    int d = a;
    if(b != 0){
        d = extgcd(b, a%b, y, x);
        y -= (a/b)*x;
    }else{
        x = 1;
        y = 0;
    }
    return d;
}
