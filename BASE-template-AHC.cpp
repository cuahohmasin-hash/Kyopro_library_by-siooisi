// Library
// https://github.com/cuahohmasin-hash/Kyopro_library_by-siooisi
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

static constexpr double TIME_LIMIT = 1.85;

struct Timer {
    chrono::steady_clock::time_point st = chrono::steady_clock::now();

    double elapsed() const {
        return chrono::duration<double>(chrono::steady_clock::now() - st).count();
    }

    bool time_up(double limit = TIME_LIMIT) const {
        return elapsed() >= limit;
    }
};

mt19937_64 rng(0);

struct Solver {
    Timer timer;
    ll score = 0;

    void input() {
        // TODO: 問題文に合わせて入力を読む。


    }

    void init() {
        // TODO: 前計算、初期解構築、パラメータ初期化。
    }

    void improve() {
        // TODO: 焼きなまし、ビームサーチ、局所改善など。
        // while (!timer.time_up()) { ... }

    }

    void output() const {
        // TODO: 問題文に合わせて解を出力する。

    }

    void solve() {
        input();
        init();
        improve();
        output();
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 再現性を優先する場合は固定 seed のままにする。
    // 提出時にランダム化したい場合だけ以下を有効化する。
    // rng.seed(chrono::steady_clock::now().time_since_epoch().count());

    Solver solver;
    solver.solve();

    // 公式スコアを実装した場合のみ Score = ... を出す。
    cerr << "InternalScore = " << solver.score << '\n';
    return 0;
}
