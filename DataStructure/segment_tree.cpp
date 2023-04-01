/*
    @ created: 2020-8
    @ updated: 2023-3
    @ verified: Library checker, Point Add Range Sum
    @ description:
        * 一点更新区間取得 (Segment Tree)
        * データ型 (int, long long) と 演算の単位元を渡す．(gcd(a,b)ならidentity=0)
        * **merge の式を適宜書き換えるのを忘れない．**
        * クエリは**片開区間なので注意**
    @ usage
        * 宣言: int n; vector<int> v(n); SegmentTree<int> seg(v, id);
        * 更新：seg.update(i, val)
        * 区間 [a,b] クエリ：seg.query(a, b+1)
*/
#include<bits/stdc++.h>
using namespace std;

// code from here
template<typename T>
struct SegmentTree{
    private:
        int n;
        vector<T> node;
        T identity;
    public:
        T merge(T x, T y){
            // 操作
            return max(x,y);
        }
        SegmentTree(vector<T> v, T id){
            // initialization. n: 2べき.
            int sz = (int)v.size();
            n = 1;
            while(n < sz) n *= 2;
            identity = id;
            node.resize(2*n-1, id);
            // 最下層を埋める．
            for(int i=0;i<sz;i++){
                node[i+n-1] = v[i];
            }
            for(int i=n-2;i>=0;i--){
                node[i] = merge(node[2*i+1], node[2*i+2]);
            }
        }
        void update(int x, T val){
            // 配列 v[x] を val に置き換える.
            x += (n-1);
            node[x] = val;
            while(x > 0){
                x = (x-1)/2;
                node[x] = merge(node[2*x+1],node[2*x+2]);
            }
        }
        T query(int a, int b, int idx=0, int l=0, int r=-1){
            // 区間 [a,b) のクエリに答える． 
            if(r < 0) r = n;
            if(r <= a || b <= l) return identity;
            if(a <= l && r <= b) return node[idx];
            T ans_left = query(a, b, 2*idx+1, l, (l+r)/2);
            T ans_right = query(a, b, 2*idx+2, (l+r)/2, r);
            return merge(ans_left, ans_right);
        }
        T operator[](int k){
            return node[k+n-1];
        }
};
