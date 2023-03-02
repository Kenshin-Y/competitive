/*
    @ created: 2020-10
    @ updated: 2023-3
    @ verified: Atcoder Grand Contest 047
    @ description:
        * 文字列の先頭部分を共通化して保存することで，文字列検索を簡単にする．
        * insert: 一文字ずつ頂点が存在するか確認し，なければ追加する．
        * 
    @ usage
        * Trie<char_size,base> trie;
        *   char_size: 文字の種類，base: 0番目． 例えば Trie<26, 'a'> trie;
        * trie.insert(word, word_id);
        *   
        * trie.search();
*/
#include <bits/stdc++.h>
using namespace std;

template<int char_size,int base>
struct Trie{
    struct Node{
        vector<int> next_id;        // 子の頂点番号．存在しなければ-1
        vector<int> word_id;        // 末端がこのノードである文字列のindex
        vector<int> cnt_subtree;    // このノードを含む部分木の個数
        int c;                      // ノードがもつ文字の base との間隔
        int common_word;            // 頂点を共有している文字列の個数
        Node(int c_){
            c = c_;
            common_word = 0;
            next.assign(char_size, -1);
            cnt.assign(char_size, 0);
        }
    };
    vector<Node> nodes;
    int root;
    Trie(){
        root = -1;
        nodes.push_back(Node(root));
    }
    void insert(const string &word, int word_id){
        int node_id = 0;
        for(int i=0;i<(int)word.size();i++){
            int c = (int)(word[i]-base);
            int &next_id = nodes[node_id].next[c];
            if(next_id == -1){ // 頂点が存在しない場合，追加する．
                next_id=(int)nodes.size();
                nodes.push_back(Node(c));
            }
            ++nodes[node_id].common;
            node_id = next_id;
        }
        ++nodes[node_id].common;
        nodes[node_id].str_id.push_back(word_id); // 単語の終点なので，word_id を追加する．
    }
    void insert(const string &word){
        insert(word,nodes[0].common);
    }
    int search(const string &word){
        int node_id = 0;
        for(int i=0;i<(int)word.size();i++){
            int c=(int)(word[i]-base);
            int &next_id=nodes[node_id].next[c];
            if(next_id == -1){
                return false;
            }
            return nodes[node_id].str_id.size() > 0;
        }
    }
    int find(const string &word){
        int pos = 0;
        for(char x:word) {
            int c = (int)(x-base);
            pos = nodes[pos].next[c];
        }
        return pos;
    }
    bool start_with(const string &prefix){
        return search(prefix, true);
    }
    int count()const{
        return (nodes[0].common);
    }
    int size()const{
        return ((int)nodes.size());
    }
};

#endif // TRIE

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