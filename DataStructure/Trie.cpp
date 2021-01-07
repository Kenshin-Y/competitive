/*
   @created: 2020-10
   @verified: Atcoder Grand Contest 047
   @see: algo-logic
   @description:
       * (char_size,base)=(文字の種類、0番目に当たるもの) Trie<26,'a'>
       * next: 子の頂点番号
       * str_id: 末端がこの頂点である文字列のidx
       * c: baseからの間隔 base='a', d=3など
       * common: prefixの共有個数
       * insert(word,idx), search(s), start_with(s), count:number of words, size:prefix
*/
#include <bits/stdc++.h>
using namespace std;

template<int char_size,int base>
struct Trie{
    struct Node{
        vector<int> next;
        vector<int> str_id;
        vector<int> cnt;    //文字xを含む部分木の個数
        int c;
        int common;
        Node(int c_):c(c_),common(0){
            next.assign(char_size,-1);
            cnt.assign(char_size,0);
        }
    };
    vector<Node> nodes;
    int root;
    Trie():root(-1){
        nodes.push_back(Node(root));
    }
    void insert(const string &word,int word_id){
        int node_id=0;
        for(int i_=0;i_<(int)word.size();i_++){
            int c=(int)(word[i_]-base);
            int &next_id=nodes[node_id].next[c];
            if(next_id==-1){
                next_id=(int)nodes.size();
                nodes.push_back(Node(c));
            }
            ++nodes[node_id].common;
            node_id = next_id;
        }
        ++nodes[node_id].common;
        nodes[node_id].str_id.push_back(word_id);
    }
    void insert(const string &word){
        insert(word,nodes[0].common);
    }
    int search(const string &word){
        int node_id=0;
        for(int i_=0;i_<(int)word.size();i_++){
            int c=(int)(word[i_]-base);
            int &next_id=nodes[node_id].next[c];
            if(next_id==-1){
                return false;
            }
            return nodes[node_id].str_id.size() > 0;
        }
    }
    int find(const string &word){
        int pos=0;
        for(char x:word) {
            int c=(int)(x-base);
            pos = nodes[pos].next[c];
        }
        return pos;
    }
    bool start_with(const string &prefix) {
        return search(prefix,true);
    }
    int count()const{
        return (nodes[0].common);
    }
    int size()const{
        return ((int)nodes.size());
    }
    /* その他メソッド */
    void solve(){
        for(int pos=(int)nodes.size()-1;pos>=0;pos--){ //葉から見る
            auto &node=nodes[pos];
            for(int a=0;a<26;a++){
                int npos=node.next[a];
                if(npos==-1) continue;
                const auto& cnode = nodes[npos];
                for (int d=0; d<26; ++d) {
                    node.cnt[d]+=cnode.cnt[d];
                }
            }
            if(node.c!=-1) node.cnt[node.c] = node.common;
        }
    }
};
/* AGC047-B First Second 
signed main(){
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<string> vec(n);
    Trie<26,'a'> trie;
    rep(i,n){
        string s; cin >> s;
        reverse(ALL(s));
        vec[i]=s;
        trie.insert(s);
    }
    trie.solve();
    ll ans=0;
    for(auto s:vec){
        int last=int(s.back()-'a');
        s.pop_back();
        int pos=trie.find(s);
        for(int a=0;a<26;a++){
            int npos = trie.nodes[pos].next[a];
            if (npos == -1) continue;
            ans += trie.nodes[npos].cnt[last];
            if (a == last) --ans;
        }
    }
    cout<< ans << endl;
}
*/