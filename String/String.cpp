/*
    @created: 2020-9
    @verified: yosupo judge
    @description:
        * Suffix Array + Longest Common Prefix
            * O(N)
            * SA<string> sa(s,SA_IS(s));
            * sa.sa[i]:=i番目のsuffixのid : sa.sa[0]='$'なので実装に気を付ける sa.sa[1]からとる
            * sa.lcp[i]:=lcp(s[sa[i]:],s[sa[i+1]:]) こっちは0-indexed
        * Z-algorithm
            * O(N)
            * SとS[i:]のLCP配列

 */

/* Suffix Array */
template<typename T>
struct SA{
    T s;
    vector<int> sa,rsa,lcp;
    SA(){}
    SA(T _s,vector<int> _sa):s(_s),sa(_sa){
        int sz=(int)s.size();
        rsa=vector<int>(sz+1);
        for(int i=0;i<=sz;i++) rsa[sa[i]]=i;
        lcp=vector<int>(sz);
        int h=0;
        for(int i=0;i<sz;i++){
            int j=sa[rsa[i]-1];
            if(h>0) h--;
            for(;j+h<sz&&i+h<sz;h++){
                if(s[j+h]!=s[i+h]) break;
            }
            lcp[rsa[i]-1]=h;
        }
    }
};
template<typename T>
vector<int> SA_IS(T s,int upper=200){
    int sz=(int)s.size();
    vector<int> sa(sz+1);
    if(sz==0) return sa;
    for(int i=0;i<sz;i++) s[i]++;
    s.push_back(0);
    upper++;
    vector<bool> ls(sz+1);
    ls[sz]=true;
    for(int i=sz-1;i>=0;i--){
        ls[i]=(s[i]==s[i+1])?ls[i+1]:(s[i]<s[i+1]);
    }
    vector<int> sum_l(upper+1),sum_s(upper+1);
    for(int i=0;i<=sz;i++){
        if (!ls[i]) sum_s[s[i]]++;
        else sum_l[s[i]+1]++;
    }
    for(int i=0;i<upper;i++){
        sum_l[i+1] += sum_s[i];
        sum_s[i+1] += sum_l[i+1];
    }
    auto induce=[&](const vector<int> &lms){
        fill(begin(sa),end(sa),-1);
        auto buf0=sum_s;
        for (auto d:lms) sa[buf0[s[d]]++] = d;
        auto buf1=sum_l;
        for(int i=0;i<=sz;i++){
            int v=sa[i];
            if(v>=1 && !ls[v-1]) sa[buf1[s[v-1]]++]=v-1;
        }
        auto buf2=sum_l;
        for(int i=sz;i>=0;i--){
            int v=sa[i];
            if(v>=1 && ls[v-1]) sa[--buf2[s[v-1]+1]] = v-1;
        }
    };
    vector<int> lms,lms_map(sz+1,-1);
    for(int i=1;i<=sz;i++){
        if(!ls[i-1] && ls[i]){
            lms_map[i]=(int)lms.size();
            lms.push_back(i);
        }
    }
    induce(lms);
    if (lms.size()>=2) {
        int m=(int)lms.size()-1;
        vector<int> lms2;
        for (int v:sa) {
            if(lms_map[v]!=-1) lms2.push_back(v);
        }
        int rec_n=1;
        vector<int> rec_s(m);
        rec_s[lms_map[lms2[1]]] = 1;
        for(int i=2;i<=m;i++){
            int l=lms2[i-1],r=lms2[i];
            int nl=lms[lms_map[l]+1], nr=lms[lms_map[r]+1];
            if (nl-l!=nr-r) rec_n++;
            else{
                while(l<=nl){
                    if(s[l]!=s[r]){
                        rec_n++;
                        break;
                    }
                    l++; r++;
                }
            }
            rec_s[lms_map[lms2[i]]] = rec_n;
        }
        vector<int> nx_lms;
        auto ch_sa = SA_IS(rec_s,rec_n);
        for(int d:ch_sa) nx_lms.push_back(lms[d]);
        induce(nx_lms);
    }
    return sa;
};
/* Z-algorithm */
vector<int> Zalgo(string v){
    int sz=(int)v.size();
    vector<int> ret(sz,0);
    int idx=0;
    for(int i=1;i<sz;i++){
        if(i+ret[i-idx]<idx+ret[idx]) ret[i]=ret[i-idx];
        else{
            int j=max(0,idx+ret[idx]-i);
            while(i+j<sz && v[j]==v[i+j]) j++;
            ret[i]=j;
            idx=i;
        }
    }
    ret[0]=sz;
    return ret;
}
