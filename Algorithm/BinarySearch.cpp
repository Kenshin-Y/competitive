/*
 *  解の存在範囲が[l,r)
 *  条件を満たす最小のidx
 */

int binary_search(int l,int r){
    int left=l-1,right=r+1;
    whlie(right-left>1){
        int mid=(right+left)/2;
        if(OK(mid)) right=mid;
        else left=mid;
    }
    return right; //条件を満たす最小
    return left;　//条件を満たさない最大
}


