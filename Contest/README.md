 - search_nCr.cpp
ABC328-E. nCrの全列挙（全域木の全探索）がしたい. n個のうちr個のビットが立っているvectorを作る．
```
basic_string<bool> use_edges(m, false);
ranges::fill(use_edges | views::take(n - 1), true);
ranges::reverse(use_edges);
do{ //処理 } while (ranges::next_permutation(use_edges).found);
```

 - 