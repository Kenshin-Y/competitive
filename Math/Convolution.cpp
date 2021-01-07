/*
    @created:2020-9
    @verifyed:
    @description:
        O(NlogN)
        A = {a_0,a_1,...,a_n}, B = {b_0,b_1,...,b_n}
        C_k = Σ(i+j=k mod n) a_i * b_j
 */
template<typename T>
T mypow(T a, ll b) {
    T res(1);
    while(b){
        if(b&1)res*=a;
        a*=a;
        b>>=1;
    }
    return res;
}
class ModInt {
    ll value;
public:
    static const unsigned int modulo;
    ModInt() : value(0) {}
    template<typename T>
    ModInt(T value = 0) : value(value) {
        if (value < 0)value = -(ll)(-value % modulo) + modulo;
        this->value = value % modulo;
    }
    inline ModInt inv()const{return mypow(*this,modulo-2);}
    inline operator int()const { return value; }
    inline ModInt& operator+=(const ModInt& x) {
        value += x.value;
        if (value >= modulo)value -= modulo;
        return *this;
    }
    inline ModInt& operator++() {
        if (value == modulo - 1)value = 0;
        else value++;
        return *this;
    }
    inline ModInt operator-()const {
        return ModInt(0) -= *this;
    }
    inline ModInt& operator-=(const ModInt& x) {
        value -= x.value;
        if (value < 0)value += modulo;
        return *this;
    }
    inline ModInt& operator--() {
        if (value == 0)value = modulo - 1;
        else value--;
        return *this;
    }
    inline ModInt& operator*=(const ModInt& x) {
        value = value * x.value % modulo;
        return *this;
    }
    inline ModInt& operator/=(const ModInt& rhs) {
        return *this*=rhs.inv();
    }
    template<typename T> ModInt operator+(const T& rhs)const { return ModInt(*this) += rhs; }
    template<typename T> ModInt& operator+=(const T& rhs) { return operator+=(ModInt(rhs)); }
    template<typename T> ModInt operator-(const T& rhs)const { return ModInt(*this) -= rhs; }
    template<typename T> ModInt& operator-=(const T& rhs) { return operator-=(ModInt(rhs)); }
    template<typename T> ModInt operator*(const T& rhs)const { return ModInt(*this) *= rhs; }
    template<typename T> ModInt& operator*=(const T& rhs) { return operator*=(ModInt(rhs)); }
    template<typename T> ModInt operator/(const T& rhs)const { return ModInt(*this) /= rhs; }
    template<typename T> ModInt& operator/=(const T& rhs) { return operator/=(ModInt(rhs)); }
};
const unsigned int ModInt::modulo=998244353;
class NTT{
private:
    static void dft(vector<ModInt>& a,bool rev){
        int sz=(int)a.size();
        if(sz==1) return;
        ModInt zeta;
        if(rev)zeta=mypow(ModInt(3),ModInt::modulo-1-(ModInt::modulo-1)/sz);
        else zeta=mypow(ModInt(3),(ModInt::modulo-1)/sz);
        vector<ModInt> b(sz),roots((sz>>1)+1,1);
        for(int i=0;i<(sz>>1);i++) roots[i+1]=roots[i]*zeta;
        for(int i=sz>>1,w=1;w<sz;i>>=1,w<<=1){
            for(int j=0;j<i;j++){
                for(int k=0;k<w;k++){
                    b[k+((w*j)<<1)]=a[k+w*j]+a[k+w*j+(sz>>1)];
                    b[k+((w*j)<<1)+w]=roots[w*j]*(a[k+w*j]-a[k+w*j+(sz>>1)]);
                }
            }
            std::swap(a,b);
        }
    }
public:
    template<typename T>
    static vector<ModInt> multiply(vector<T> &f,vector<T> &g){
        if(f.size()<g.size())std::swap(f,g);
        vector<ModInt> nf,ng;
        int sz=1;
        while(sz<(int)f.size()+(int)g.size()) sz<<=1;
        nf.resize(sz); ng.resize(sz);
        for(int i=0;i<(int)f.size();i++){
            nf[i]=f[i];
            if(i<(int)g.size()) ng[i]=g[i];
        }
        dft(nf,false);
        dft(ng,false);
        for(int i=0;i<sz;i++) nf[i]*=ng[i];
        dft(nf,true);
        ModInt szinv=ModInt(sz).inv();
        for(int i=0;i<sz;i++) nf[i]*=szinv;
        nf.resize(int(f.size()+g.size()+1));
        return nf;
    }
};

signed main(){
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int n,m; cin >> n >> m;
    vector<int> a(n),b(m);
    rep(i,n) cin >> a[i];
    rep(i,m) cin >> b[i];
    vector<ModInt> ans=NTT::multiply(a,b);
    rep(i,n+m){
        cout << ans[i];
        if(i!=n+m-1) cout << " ";
    }
    cout << endl;
}
