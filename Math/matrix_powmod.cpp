#include <bits/stdc++.h>
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define ll long long
#define ALL(a) (a).begin(),(a).end()
#define rep(i,n) for(int i=0;i<(n);i++)
#define rrep(i,n) for(int i=n-1;i>=0;i--)
#define fi first
#define se second
#define pb push_back
#define Pii pair<int,int>
#define Pll pair<long long,long long>
#define fout(num) cout << fixed << setprecision(20) << (num) << endl
template<typename T1,typename T2> inline void chmin(T1 &a,T2 b){if(a>b) a=b;}
template<typename T1,typename T2> inline void chmax(T1 &a,T2 b){if(a<b) a=b;}
//vector<vector<ll>> dp(n,vector<ll>(n))
//2-dim:vector<vector<Type>> vv(n, vector<Type>(m, d));
//3-dim:vector<vector<vector<Type>>> vvv(n, vector<vector<Type>>(m, vector<Type>(l, d)));

using namespace std;
const long long MOD = 1e9+7;
template<typename T>
struct Matrix
{
    vector<vector<T> > A;
    Matrix(int n, int m)
    {
        A(n, vector<T>(m, 0));
    }
    Matrix(vector<vector<T> > v)
    {
        A = v;
    }
    int height()const{ return A.size(); }
    int width()const{ return A[0].size(); }

    Matrix I(int n){
        Matrix mat(n, n);
        for(int i=0;i<n;i++) mat[i][i] = 1;
        return mat;
    }

    Matrix &operator*=(const Matrix &B)
    {
        vector<vector<T> > C(height(), vector<T>(weight(),0));
        for(int i=0; i<height(); i++){
            for(int j=0; j<B.width(); j++){
                for(int k=0; k<width(); k++){
                    C[i][j] = ((*this)[i][k] * B[k][j] % MOD);
                }
            }
        }
        A.swap(C);
        return (*this);
    }
    Matrix &operator*(const Matrix &B)
    {
        return (Matrix((*this) *= B));
    }
    Matrix powmod(long long N)  // return A^N
    {
        Matrix ret = I(A.size());
        while(N){
            if(N & 1){
                ret *= (*this);
                N -= 1;
            }else{
                (*this) *= (*this);
                N >>= 1;
            }
        }
        return ret;
    }
}

void solve()
{
    vector<vector<int> > A = {{1,1},{1,0}};
    Matrix<int> M = A;
    for(int i=1;i<10;i++){
        Matrix m = M.powmod(i);
        cout << m[0][0] << endl;
    }
}
signed main()
{
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    solve();
    return 0;
}
// g++ main.cpp -o a.out && ./a.out


const long long MOD = 1e9+7;
vector<vector<int> > mat_mul(vector<vector<int> > A, vector<vector<int> > B)
{
    vector<vector<int> > C(A.size(), vector<int>(B[0].size()));
    for(int i=0; i<A.size(); i++){
        for(int j=0; j<B[0].size(); j++){
            for(int k=0; k<A[0].size(); k++){
                C[i][j] += (A[i][k] * B[k][j] % MOD);
            }
        }
    }
    return C;
}

vector<vector<int> > mat_pow(vector<vector<int> > A, long long n)
{
    int sz = A.size();
    vector<vector<int> > ret(sz, vector<int>(sz));
    rep(i,sz) ret[i][i] = 1;
    while(n){
        if(n&1){
            ret = mat_mul(ret, A);
            n -= 1;
        }else{
            A = mat_mul(A, A);
            n >>= 1;
        }
    }
    return ret;
}