/*
    @ created: 2020-8
    @ updated: 2023-3
    @ verified: AOJ DSL_4_A
    @ description:
        * 座標圧縮．要素の最大値を要素数で抑えることができる．
        * 配列 x をソートして重複を除いたものが val．
        * 元の配列 x には各要素が配列 val の何番目であるかのindexを入れる．
        * → x は圧縮後の配列．元の配列にアクセスしたいときは val[x[i]] でOK.．
        * 二次元imosへの応用
*/

#include<bits/stdc++.h>
using namespace std;

signed main()
{
    int n; // 要素数
    vector<long long> x(n);
    vector<long long> val;
    for(int i=0;i<n;i++){
        cin >> x[i];
        val.push_back(x[i]);
    }
    sort(val.begin(),val.end());
    val.erase(unique(val.begin(), val.end(), val.end()));
    for(int i=0;i<n;i++){
        x[i] = (int)(lower_bound(val.begin(), val.end(), x[i]) - x.begin());
    }
}
