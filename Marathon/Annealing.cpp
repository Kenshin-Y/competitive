/*
あらかじめ、計算する時間をTを決める。
以下のスコープ内のコードを時間T経過するまで繰り返す。
{
    適当に、次の状態（近傍）を選ぶ。
    (1) 次の状態のスコアが、今の状態のスコアより良くなった場合は、常に、状態を次の状態にする（遷移）。
    (2) 次の状態のスコアが、今の状態のスコアより悪くなった場合でも、ある確率で、状態を次の状態にする。
        確率は以下のように決める。
       (2.A) 序盤(時刻t=0に近いとき)ほど高確率で、終盤(t=Tに近いとき)ほど低確率。
       (2.B) スコアが悪くなった量が大きければ大きいほど、低確率。
}
最後に、今まで一番スコアのよかった状態を選ぶ。
*/
#include <bits/stdc++.h>

// 0以上UINT_MAX未満(0xffffffff)をとる乱数
static uint32_t randXor()
{
    static uint32_t x = 123456789;
    static uint32_t y = 362436069;
    static uint32_t z = 521288629;
    static uint32_t w = 88675123;
    uint32_t t;
    t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}

// 正規化
static double rand01()
{
    return (randXor() + 0.5) * (1.0 / UINT_MAX);
}

// 全体スコア
static int getFullScore();

// スコア増分
static int getContestScore();

//入力
void input();

//　Main
int main()
{
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    auto startClock = std::chrono::system_clock::now();

    input();
    
    int score = getFullScore();   // 現在のスコア
    int bestScore = INT_MIN;    // 最高スコア
    vector<int> bestT;         // 最高スコアを出したときの配列

    const static double START_TEMP = 1500;
    const static double END_TEMP = 100;
    const static double END_TIME = 1.8; // 終了時刻(s)

    long long steps;
    for(steps = 0; ; steps++)
    {
        if(steps%100==0)
        { //温度更新の頻度
            const double time = std::chrono::duration_cast<microseconds>(system_clock::now() - startClock).count() * 1e-6;   // 経過時間（秒）
            if(time > END_TIME){
                break;
            }
            const double progressRatio = time / END_TIME;   // 進捗。開始時が0.0、終了時が1.0
            temp = START_TEMP + (END_TEMP - START_TEMP) * progressRatio;
        }
        int deltaScore = getContestScore();
        if (exp(deltaScore / temp) > rand01())
        {
            // 確率exp(Δ/temp)で採用
            // deltaScoer > 0 なら 必ず採用される
        }else
        {
            //採用しない処理があるなら書く
        }
    }
    
}