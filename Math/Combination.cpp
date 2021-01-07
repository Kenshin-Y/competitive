/*
    @created:2019-8
    @vefified: fin
    @description:
        * Fermatの小定理: a^(p-1)=1 mod p　なので、a^(p-2)=a^(-1) mod p　を利用し逆元計算する
        * a^(-1)= -(p%a)^(-1) * (p/a) mod p によりO(1)で計算可能 (p/a)は商なので注意
        * COMinit()
 */

const long long MOD = 1e9+7;
const int MAX = 1001001;
long long fac[MAX],finv[MAX],inv[MAX];
void COMinit(){
    fac[0]=fac[1]=1;
    finv[0]=finv[1]=1;
    inv[1]=1;
    for(int i=2;i<MAX;i++){
        fac[i]=fac[i-1]*i % MOD;
        inv[i]=MOD-inv[MOD%i]*(MOD/i) % MOD;
        finv[i]=finv[i-1]*inv[i] % MOD;
    }
}
long long COM(int n,int k){
    if(n<k) return 0;
    if(n<0 || k<0) return 0;
    return fac[n]*(finv[k]*finv[n-k] % MOD) % MOD;
}
