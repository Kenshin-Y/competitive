/*
    @ created: 2020-8
    @ updated: 2023-3
    @ verified: ABC167-D Teleporter
    @ description:
        * 全体の要素数が N 個あって，K ステップ先の要素が O(K) で求まるとき，
        * 前処理 O(NlogK)，クエリ O(logK) で処理できる．
        * 実装方針として，それぞれの要素について 1 個先の要素が何か記録
        * 前の結果を利用し，それぞれの要素について 2 個先の要素が何か記録
        * 前の結果を利用し，それぞれの要素について 4 個先の要素が何か記録
        * 前の結果を利用し，それぞれの要素について 8 個先の要素が何か記録 ...
*/

#include <bits/stdc++.h>
using namespace std;

// 町 i の転送先を a[i] として，k ステップ後の転送先を求める．
int main(){
    int n; long long K;
    cin >> n >> K;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        a[i]--;
    }
    int logK=1;
    while((1LL<<logK) <= K) logK++;

    // doubling[k][i] := i 番目から 2^k 進んだ町．
    // i 番目から 2^(k+1) ステップ進んだ先は，i 番目から 2^k ステップ進んだ先から 2^k ステップ進んだ場所．
    vector<vector<int>> doubling(logK, vector<int>(n));
    for(int i=0;i<n;i++) doubling[0][i] = a[i];  // 1ステップ先
    for(int k=0;k<logK-1;k++){  // logK ステップ先まで見る.
        for(int i=0;i<n;i++){
            doubling[k+1][i] = doubling[k][doubling[k][i]];
        }
    }

    // K ステップ先を見る．二進数展開．
    int now = 0;
    for (int bit=0;bit<logK;bit++){
        if((1LL<<bit)&K) now = doubling[bit][now];
    }
    cout << now + 1 << endl;
}

// 例えばK=19なら，logK=5，二進数表記で 10011 のため，1+2+16 ステップ進めばよいことがわかる．
// now = doubling[0][now] K=9
// now = doubling[1][now] K=4
// skip K=2
// skip K=1
// now = doubling[4][now] K=0