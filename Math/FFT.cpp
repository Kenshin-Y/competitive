/*
    @created:2020-9
    @verifyed:ATC001-C
    @description:
        多項式乗算について、
        f(x)=ΣA_i x^i, g(x)=ΣB_i x^i
        C_i=ΣA_j B_{i-j},  f(x)g(x)=ΣC_i x^i
        C_iが高速に計算できれば良い　多項式fとgの畳み込み　(数列{A_i},{B_i}についての畳み込み)
        愚直:O(N^2) を　O(NlogN)でやる
        vector<double> ans=FFT::multiply(f,g);
        f.size()<g.size()
 */
#ifndef FFT_CPP
#define FFT_CPP
#include <bits/stdc++.h>
using namespace std;

typedef complex<double> Complex;
const double PI = acos(-1);

struct FFT
{
private:
    static void dft(vector<Complex>& func,int inverse)
    {
        int sz=(int)func.size();
        if(sz==1) return;
        vector<Complex> f0,f1;
        for(int i=0;i<sz/2;i++){
            f0.push_back(func[2*i+0]);
            f1.push_back(func[2*i+1]);
        }
        dft(f0,inverse);
        dft(f1,inverse);
        Complex zeta = Complex(cos(2.0*PI/sz),sin(2.0*PI/sz)*inverse);
        Complex pow_zeta = 1;
        for(int i=0;i<sz;i++){
            func[i]=f0[i%(sz/2)]+pow_zeta*f1[i%(sz/2)];
            pow_zeta*=zeta;
        }
    }
public:
    template<typename T>
    static vector<double> multiply(vector<T> f,vector<T> g)
    {
        if(f.size()<g.size()) std::swap(f,g);
        int sz=1;
        vector<Complex> nf,ng;
        while(sz<(int)f.size()+(int)g.size()) sz*=2;
        nf.resize(sz);
        ng.resize(sz);
        for(int i=0;i<(int)f.size();i++){
            nf[i]=f[i];
            if(i<(int)g.size()) ng[i]=g[i];
        }
        dft(nf,1);
        dft(ng,1);
        for(int i=0;i<sz;i++) nf[i]*=ng[i];
        dft(nf,-1);
        vector<double> ret;
        for(int i=0;i<sz;i++) ret.push_back(nf[i].real()/sz);
        return ret;
    }
};
#endif // FFT_CPP