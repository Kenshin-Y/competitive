/*
    @created: 2020-9
    @verified: ALPC
    @description:
        * 変数x_0,x_1,...,x_n-1に対し、(x_i=f_i || x_j=f_j)　の集合を満たす変数割り当て
        * edge(2*i+(f?0:1),2*j+(g?1:0)) (2*j+(g?0:1),2*i+(f?1:0)) に辺をはってSCC
        /*
            vector<vector<int>> v(2*n)
            auto add_E=[&](int x_i,bool x_f,int x_j,bool x_g){
                v[2*x_i+(x_f?0:1)].push_back(2*x_j+(x_g?1:0));
                v[2*x_j+(x_g?0:1)].push_back(2*x_i+(x_f?1:0));
            };
        /*
        * satisfiable()が実質build()
 */

/*  scc.cppを貼る  */

struct two_sat{
private:
    int _n;
    vector<bool> _answer;
    vector<vector<int>> _v;
public:
    two_sat():_n(0){}
    two_sat(vector<vector<int>> &v):_n((int)v.size()),_answer((int)v.size()),_v(v){}
    bool satisfiable(){
        vector<vector<int>> hoge;
        SCC<vector<vector<int>>> scc(_v);
        scc.build(hoge);
        for(int i=0;2*i+1<_n;i++){
            //assert(2*i+1<scc.comp.size());
            if(scc[2*i]==scc[2*i+1]) return false;
            _answer[i] = scc[2*i] < scc[2*i+1];
        }
        return true;
    }
    vector<bool> answer(){
        return _answer;
    }
};

/*
 signed main(){
     std::cin.tie(nullptr);
     std::ios_base::sync_with_stdio(false);
     int n,d; cin >> n >> d;
     vector<int> x(n),y(n);
     rep(i,n) cin >> x[i] >> y[i];
     vector<vector<int>> v(2*n);
     auto add_E=[&](int x_i,bool x_f,int x_j,bool x_g){
         v[2*x_i+(x_f?0:1)].push_back(2*x_j+(x_g?1:0));
         v[2*x_j+(x_g?0:1)].push_back(2*x_i+(x_f?1:0));
     };
     rep(i,n){
         for(int j=i+1;j<n;j++){
             if (abs(x[i] - x[j]) < d) {
                 add_E(i,false,j,false);
             }
             if (abs(x[i] - y[j]) < d) {
                 add_E(i,false,j,true);
             }
             if (abs(y[i] - x[j]) < d) {
                 add_E(i,true,j,false);
             }
             if (abs(y[i] - y[j]) < d) {
                 add_E(i,true,j,true);
             }
         }
     }
     //rep(i,2*n) cout << v[i].size() << " ";
     two_sat ts(v);
     if(!ts.satisfiable()){
         cout << "No" << endl;
     }else{
         cout << "Yes" << endl;
         vector<bool> as=ts.answer();
         rep(i,n){
             cout << (as[i]?x[i]:y[i]) << "\n";
         }
     }
 }

 */
