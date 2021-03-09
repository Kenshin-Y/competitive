/*
    @created: 2020-8
    @verified: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_4_A
    @description:
        * 元の座標に紐付けする(id,val)の組を持っておく. sort -> earse -> lower_bound で実現可能.
        * 二次元imosとかで色々応用できる.
 */

/*   Sample Code  DSL   */

#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    vector<long long> x,y;
    vector<long long> x1in(n),y1in(n),x2in(n),y2in(n);
    for(int i=0;i<n;i++){
        cin >> x1in[i] >> y1in[i] >> x2in[i] >> y2in[i];
        x.push_back(x1in[i]); x.push_back(x2in[i]);
        y.push_back(y1in[i]); y.push_back(y2in[i]);
    }
    sort(x.begin(),x.end());
    sort(y.begin(),y.end());
    x.erase(unique(x.begin(),x.end()),x.end());
    y.erase(unique(y.begin(),y.end()),y.end());
    for(int i=0;i<n;i++){
        x1in[i]=(int)(lower_bound(x.begin(),x.end(),x1in[i])-x.begin());
        x2in[i]=(int)(lower_bound(x.begin(),x.end(),x2in[i])-x.begin());
        y1in[i]=(int)(lower_bound(y.begin(),y.end(),y1in[i])-y.begin());
        y2in[i]=(int)(lower_bound(y.begin(),y.end(),y2in[i])-y.begin());
    }
}