/*
    @ created: 2020-10
    @ updated: 2023-3
    @ verified: count1: Speed Run 001 J
                count2: ARC075-E Meaningful Mean
    @ description:
        * 
        * 
    @ usage:
        * O(NlogN)
        * count:  (i,j) s.t. a[i] > a[j] , i<j
        * count2: (i,j) s.t. a[i] >= a[j], i<j
        * 座圧してBIT
        * long long 渡す
*/
#include<bits/stdc++.h>
using namespace std;

struct InversionCount{

    struct BIT{
        vector<int> data;
        BIT(int sz){
            data.assign(sz+1,0);
        }
        /* from data[1] to data[x] */
        int sum(int x){
            int ret=0;
            while(x>0){
                ret+=data[x];
                x-=(x&-x);
            }
            return ret;
        }
        void add(int x,int val){
            while(x<=int(data.size())){
                data[x]+=val;
                x+=(x&-x);
            }
        }
    };

    // 座圧
    vector<int> shrink(vector<long long> a)
    {
        vector<long long> val=a;
        vector<int> ret(a.size());

        sort(val.begin(),val.end());
        val.erase(unique(val.begin(),val.end()),val.end());

        for(int i=0;i<int(a.size());i++){
            int idx=int(lower_bound(val.begin(), val.end(), a[i])-val.begin());
            ret[i]=idx+1;
        }

        return ret;
    }

    long long count(vector<long long> a)
    {
        long long ret = 0;
        vector<int> res = shrink(a);
        BIT bit(int(res.size()+1));

        for(int i=0;i<int(res.size());i++){
            ret += i-bit.sum(res[i]);
            bit.add(res[i],1);
        }
        return ret;
    }

    long long count2(vector<long long> a)
    {
        long long ret = count(a);
        sort(a.begin(),a.end());
        long long num = 0;

        for(int i=0;i<int(a.size()-1);i++){
            if(a[i] != a[i+1]){
                ret += num*(num+1LL)/2LL;
                num = 0;
            }else{
                num++;
            }
        }

        ret += num*(num+1LL)/2LL;
        return ret;
    }
};
