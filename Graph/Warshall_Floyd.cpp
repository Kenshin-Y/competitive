#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define ll long long
#define rep(i,n) for(int i=0;i<(n);i++)

const int MAXV = 500;
int v;
//init d[i][j]=cost[i][j]
//O(v^3)で全点対の最短路が求まる
void warshall_floyd(){
    rep(k,v){
        rep(i,v){
            rep(j,v){
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
            }
        }
    }
}
