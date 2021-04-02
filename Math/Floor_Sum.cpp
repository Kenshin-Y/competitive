/*
    @created:2020-9
    @verified: ACLC
    @description:
        * y=(ax+b)/M ,x=0,1,...,n-1 の格子点数え上げ
        * 自明を数え上げて、再帰関数にする
        * O(log(n+m+a+b))
        * これ何？
 */
#ifndef FLOOR_SUM
#define FLOOR_SUM
#include <bits/stdc++.h>
using namespace std;

long long floor_sum(long long n,long long m,long long a,long long b)
{
    long long ans = 0LL;
    if(a>=m){
        ans += n*(n-1LL)*(a/m)/2LL;
        a %= m;
    }
    if(b>=m){
        ans += n*(b/m);
        b %= m;
    }
    long long ym = (a*n+b)/m;
    long long xm =ym*m-b;
    if(ym==0) return ans;

    ans += (n-(xm+a-1LL)/a)*ym;
    ans += floor_sum(ym,a,m,(a-xm%a)%a);
    return ans;
}
#endif // FLOOR_SUM
