// Library
// https://github.com/cuahohmasin-hash/Kyopro_library_by-siooisi
#ifdef LOCAL
#define _GLIBCXX_DEBUG
#endif
#include <bits/stdc++.h>
#include <atcoder/all>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
using namespace atcoder;
using ll = long long;
using ull = unsigned long long;

struct custom_hash {
    static ull splitmix64(ull x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    static ull hash_any(ull x) {
        static const ull FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    size_t operator()(ull x) const {
        return hash_any(x);
    }

    size_t operator()(const string& s) const {
        return hash_any(std::hash<string>{}(s));
    }

    template<class T, class U>
    size_t operator()(const pair<T, U>& p) const {
        ull h1 = (*this)(p.first);
        ull h2 = (*this)(p.second);
        return splitmix64(h1 ^ (h2 + 0x9e3779b97f4a7c15 + (h1 << 6) + (h1 >> 2)));
    }
};
template<class K, class V> 
struct safe_map : gp_hash_table<K, V, custom_hash> {
    bool count(const K& k) const { return this->find(k) != this->end(); }
};
template<class K> 
struct safe_set : gp_hash_table<K, null_type, custom_hash> {
    bool count(const K& k) const { return this->find(k) != this->end(); }
};
template<class K, class V> using umap = unordered_map<K, V, custom_hash>;
template<class K> using uset = unordered_set<K, custom_hash>;
// --- PBDS ---
// 直感的に使える ordered_set (重複を許さない単一要素版) のラッパー
template<class T>
struct OrderedSet {
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update> st;

    // 要素 x を追加 (既に存在する場合は何もしない)
    void insert(T x) {
        st.insert(x);
    }

    // 要素 x を削除 (存在する場合のみ)
    void erase(T x) {
        st.erase(x);
    }

    // 小さい方から k 番目 (0-indexed) の値を取得
    T get_kth(int k) {
        return *st.find_by_order(k);
    }

    // x より小さい要素の個数を取得
    int count_less(T x) {
        return st.order_of_key(x);
    }

    // 要素 x が存在するかどうかを判定
    bool contains(T x) {
        return st.find(x) != st.end();
    }

    int size() { return st.size(); }
    bool empty() { return st.empty(); }
    void clear() { st.clear(); }
};
// 直感的に使える ordered_multiset のラッパー
template<class T>
struct OrderedMultiset {
    int id_counter = 0;
    tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, tree_order_statistics_node_update> st;

    // 要素 x を追加
    void insert(T x) {
        st.insert({x, id_counter++});
    }

    // 要素 x を 1 つ削除 (存在する場合のみ)
    void erase(T x) {
        auto it = st.lower_bound({x, -1});
        if (it != st.end() && it->first == x) st.erase(it);
    }

    // 小さい方から k 番目 (0-indexed) の値を取得
    T get_kth(int k) {
        return st.find_by_order(k)->first;
    }

    // x より小さい要素の個数を取得
    int count_less(T x) {
        return st.order_of_key({x, -1});
    }

    // x 以下の要素の個数を取得
    int count_less_equal(T x) {
        return st.order_of_key({x, 2000000000}); // IDとして十分に大きな値を使用
    }

    int size() { return st.size(); }
    bool empty() { return st.empty(); }
    void clear() { st.clear(); id_counter = 0; }
};
// -----------
constexpr int MOD = 1000000007;
constexpr int MOD998 = 998244353;
using mint = atcoder::static_modint<MOD>;
using mint998 = atcoder::static_modint<MOD998>;
using dmint = atcoder::modint;
inline void set_mod(long long p) { dmint::set_mod(p); }
using int128 = __int128_t;
using uint128 = __uint128_t;

constexpr uint128 INT128_ABS_MIN = uint128{1} << 127;
constexpr int128 INT128_MAX_VALUE = static_cast<int128>(INT128_ABS_MIN - 1);
constexpr int128 INT128_MIN_VALUE = -INT128_MAX_VALUE - 1;

std::istream& operator>>(std::istream& is, __int128_t& v) {
    std::string s;
    if (!(is >> s)) return is;

    size_t pos = 0;
    bool negative = false;
    if (s[pos] == '+' || s[pos] == '-') {
        negative = (s[pos] == '-');
        pos++;
    }
    if (pos == s.size()) {
        is.setstate(std::ios::failbit);
        return is;
    }

    const uint128 limit = negative ? INT128_ABS_MIN : static_cast<uint128>(INT128_MAX_VALUE);
    uint128 value = 0;
    for (; pos < s.size(); pos++) {
        const char c = s[pos];
        if (c < '0' || c > '9') {
            is.setstate(std::ios::failbit);
            return is;
        }
        const uint128 digit = static_cast<unsigned>(c - '0');
        if (value > (limit - digit) / 10) {
            is.setstate(std::ios::failbit);
            return is;
        }
        value = value * 10 + digit;
    }

    if (negative) {
        v = (value == INT128_ABS_MIN) ? INT128_MIN_VALUE : -static_cast<int128>(value);
    } else {
        v = static_cast<int128>(value);
    }
    return is;
}
std::ostream& operator<<(std::ostream& os, __int128_t v) {
    if (v == 0) return os << '0';

    uint128 value;
    if (v < 0) {
        os << '-';
        value = static_cast<uint128>(-(v + 1)) + 1;
    } else {
        value = static_cast<uint128>(v);
    }

    char digits[40];
    int len = 0;
    while (value > 0) {
        digits[len++] = static_cast<char>('0' + value % 10);
        value /= 10;
    }
    while (len > 0) os << digits[--len];
    return os;
}

template <int m> istream& operator>>(istream& is, atcoder::static_modint<m>& v) { long long x; is >> x; v = x; return is; }
template <int m> ostream& operator<<(ostream& os, const atcoder::static_modint<m>& v) { return os << v.val(); }
template <int id> istream& operator>>(istream& is, atcoder::dynamic_modint<id>& v) { long long x; is >> x; v = x; return is; }
template <int id> ostream& operator<<(ostream& os, const atcoder::dynamic_modint<id>& v) { return os << v.val(); }

#define rep(i, x, limit) for (ll i = (ll)x; i < (ll)limit; i++)
#define rrep(i, x, limit) for (ll i = (ll)x; i >= (ll)limit; i--)
#define reps(i, a, b, s) for (long long i = (a); i < (b); i += (s))
#define rreps(i, a, b, s) for (long long i = (a); i >= (b); i -= (s))
#define rep2(i, start_i, limit_i, j, start_j, limit_j) for (ll i = (ll)(start_i); i < (ll)(limit_i); i++) for (ll j = (ll)(start_j); j < (ll)(limit_j); j++)
constexpr int inf = 1073741823;
constexpr ll infl = 1LL << 60;
// 右、下、左、上の順
constexpr int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
// 右、右下、下、左下、左、左上、上、右上の順
constexpr int dx8[8] = {1, 1, 0, -1, -1, -1, 0, 1}, dy8[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const long double PI = 3.1415926535897932384626433832795028841971;
constexpr array<int128, 21> make_p10() {
    array<int128, 21> p{};
    p[0] = 1;
    for (int i = 1; i < (int)p.size(); i++) p[i] = p[i - 1] * 10;
    return p;
}
constexpr auto P10 = make_p10();
inline constexpr long long pow2(int i) { return 1LL << i; }
inline int bitcount(long long x) {
    return __builtin_popcountll(x);
}
// pair: first昇順, second降順
struct AD {
    template<class T, class U>
    bool operator()(const pair<T,U>& a, const pair<T,U>& b) const {
        return a.first != b.first ? a.first < b.first : a.second > b.second;
    }
};

// pair: first降順, second昇順
struct DA {
    template<class T, class U>
    bool operator()(const pair<T,U>& a, const pair<T,U>& b) const {
        return a.first != b.first ? a.first > b.first : a.second < b.second;
    }
};

#define alp "abcdefghijklmnopqrstuvwxyz"
#define ALP "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define nall(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend() 
#define pb push_back
#define pob pop_back
#define eb emplace_back
#define Yes cout << "Yes" << endl
#define No cout << "No" << endl
#define YES cout << "YES" << endl
#define NO cout << "NO" << endl
void YN(bool cond) { cout << (cond ? "Yes" : "No") << "\n"; }
#define endl "\n"
#define syousu cout<<fixed<<setprecision(15) 

template<typename T1, typename T2> istream& operator>>(istream& is, pair<T1, T2>& p) { is >> p.first >> p.second; return is; }
template<typename T> istream& operator>>(istream& is, vector<T>& v) { for (auto& e : v) is >> e; return is; }

// 出力ヘルパー（複数の値は空白区切り、末尾は改行）
inline void p0() { cout << '\n'; }

template<class... Args>
void print_line(const Args&... args) {
    size_t i = 0;
    ((cout << (i++ == 0 ? "" : " ") << args), ...);
    cout << '\n';
}

template<class T1> void p1(const T1& a) { print_line(a); }
template<class T1, class T2> void p2(const T1& a, const T2& b) { print_line(a, b); }
template<class T1, class T2, class T3> void p3(const T1& a, const T2& b, const T3& c) { print_line(a, b, c); }
template<class T1, class T2, class T3, class T4>
void p4(const T1& a, const T2& b, const T3& c, const T4& d) { print_line(a, b, c, d); }
template<class T1, class T2, class T3, class T4, class T5>
void p5(const T1& a, const T2& b, const T3& c, const T4& d, const T5& e) { print_line(a, b, c, d, e); }

template<class Container>
void print_range(const Container& values, string_view separator = " ") {
    bool first = true;
    for (const auto& value : values) {
        if (!first) cout << separator;
        first = false;
        cout << value;
    }
    cout << '\n';
}

template<typename T> void print(const vector<T>& v) { print_range(v); }
template<typename T> void print(const vector<vector<T>>& v) { for (const auto& row : v) print_range(row); }

#define VEC(type, name, size) vector<type> name(size)
#define VECI(type, name, size, init) vector<type> name(size, init)
#define VVEC(type, name, h, w) vector<vector<type>> name(h, vector<type>(w))
#define VVECI(type, name, h, w, init) vector<vector<type>> name(h, vector<type>(w, init))
#define VVVEC(type, name, d, h, w) vector<vector<vector<type>>> name(d, vector<vector<type>>(h, vector<type>(w)))
#define VVVECI(type, name, d, h, w, init) vector<vector<vector<type>>> name(d, vector<vector<type>>(h, vector<type>(w, init)))
#define VVVVEC(type, name, d1, d2, d3, d4) vector<vector<vector<vector<type>>>> name(d1, vector<vector<vector<type>>>(d2, vector<vector<type>>(d3, vector<type>(d4))))
#define VVVVECI(type, name, d1, d2, d3, d4, init) vector<vector<vector<vector<type>>>> name(d1, vector<vector<vector<type>>>(d2, vector<vector<type>>(d3, vector<type>(d4, init))))
#define VECP(type1, type2, name, size) vector<pair<type1, type2>> name(size)
#define VECPI(type1, type2, name, size, init) vector<pair<type1, type2>> name(size, init)
#define VP(type1, type2) vector<pair<type1, type2>>
#define VVECP(type1, type2, name, h, w) vector<vector<pair<type1, type2>>> name(h, vector<pair<type1, type2>>(w))
#define VVECPI(type1, type2, name, h, w, init) vector<vector<pair<type1, type2>>> name(h, vector<pair<type1, type2>>(w, init))
#define VVP(type1, type2) vector<vector<pair<type1, type2>>>
#define VECT(type1, type2, type3, name, size) vector<tuple<type1, type2, type3>> name(size)
#define VECTI(type1, type2, type3, name, size, init) vector<tuple<type1, type2, type3>> name(size, init)
#define VT(type1, type2, type3) vector<tuple<type1, type2, type3>>

template<typename T> T SUM(const vector<T>& v) { return accumulate(v.begin(), v.end(), (T)0); }
template<typename T> T MAX(const vector<T>& v) { return *max_element(v.begin(), v.end()); }
template<typename T> T MIN(const vector<T>& v) { return *min_element(v.begin(), v.end()); }
template<class T> using min_pq = priority_queue<T, vector<T>, greater<T>>;
template<class T> using max_pq = priority_queue<T>;
template<class T> bool chmax(T& a, const T& b) { if (a < b) { a = b; return 1; } return 0; }
template<class T> bool chmin(T& a, const T& b) { if (a > b) { a = b; return 1; } return 0; }
template<typename T> void uniq(vector<T>& v) { sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); }
template <typename T> void dec(vector<T>& a) { for (auto& x : a) x--; }
bool in_range(int x, int y, int h, int w) { return x >= 0 && x < h && y >= 0 && y < w; }

ll ceil_div(ll n, ll d) {
    assert(d != 0);
    assert(!(n == LLONG_MIN && d == -1));
    ll q = n / d, r = n % d;
    if (r != 0 && ((r > 0) == (d > 0))) q++;
    return q;
}
ll floor_div(ll n, ll d) {
    assert(d != 0);
    assert(!(n == LLONG_MIN && d == -1));
    ll q = n / d, r = n % d;
    if (r != 0 && ((r > 0) != (d > 0))) q--;
    return q;
}
// 精度ほぼ無限の平方根
long long integer_sqrt(long long N) {
    if (N <= 0) return 0;
    long long x = sqrt((long double)N);
    while ((__int128)(x + 1) * (x + 1) <= N) x++;
    while ((__int128)x * x > N) x--;
    return x;
}
// 文字列 s の idx 番目の文字を1つ削除した新しい文字列を返す
// 使い方: S = erase_char(S, 3);
string erase_char(string s, int idx) {
    if (idx < 0 || idx >= (int)s.length()) return s; // 範囲外アクセスの防止
    s.erase(s.begin() + idx);
    return s;
}

// 文字列 s の idx 番目に文字 c を挿入した新しい文字列を返す
// 使い方: S = insert_char(S, 3, 'a');
string insert_char(string s, int idx, char c) {
    if (idx < 0) idx = 0;
    if (idx > (int)s.length()) idx = s.length();
    s.insert(s.begin() + idx, c);
    return s;
}
// アルファベットの大文字・小文字を反転させる関数
inline char flip_char(char c) {
    if (islower(c)) return toupper(c);
    if (isupper(c)) return tolower(c);
    return c; // アルファベット以外が来た場合はそのまま返す
}
long long count_digit_numbers(long long N, int d) {
    __int128 L = P10[d - 1];
    __int128 R = P10[d] - 1;

    if ((__int128)N < L) return 0;

    __int128 upper = min((__int128)N, R);
    return (long long)(upper - L + 1);
}
// 中心 (sr, sc) からマンハッタン距離 dist にある、
// 行 i 上の列 j を最大2個返す。
// 存在しない候補は -1。
//
// 戻り値:
//   res[0] = 左側の候補
//   res[1] = 右側の候補
//
// 左右が同じ点になる場合は res[1] = -1 とする。
array<int, 2> manhattan_columns(
    int W,
    int sr,
    int sc,
    int dist,
    int i
) {
    int remain = dist - abs(i - sr);
    // この行には距離 dist の点が存在しない
    if (remain < 0) {
        return {-1, -1};
    }
    int left  = sc - remain;
    int right = sc + remain;
    if (left < 0 || left >= W) {
        left = -1;
    }
    if (right < 0 || right >= W) {
        right = -1;
    }
    // remain == 0 のとき左右は同じ点
    if (left == right) {
        right = -1;
    }
    return {left, right};
}

template<typename T> T GCD(const vector<T>& v) { T res = 0; for (T x : v) res = std::gcd(res, x); return res; }
template<typename T> T LCM(const vector<T>& v) { T res = 1; for (T x : v) res = std::lcm(res, x); return res; }
template<typename T> void extend(vector<T>& a, const vector<T>& b) { a.insert(a.end(), b.begin(), b.end()); }
template<typename T> void double_vec(vector<T>& a) { int n = a.size(); a.reserve(n * 2); for(int i = 0; i < n; i++) a.push_back(a[i]); }
template<class T> ll len(const T& x) { return (ll)x.size(); }
long long nC2(long long n) { return n < 2 ? 0 : (ll)((int128)n * (n - 1) / 2); }
long long nC3(long long n) { return n < 3 ? 0 : (ll)((int128)n * (n - 1) * (n - 2) / 6); }

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...) 42
#endif


using m1 = atcoder::static_modint<1>;






int main() {
//※※積の問題の0除算　文字列ですべて同じ文字パターン　オーバーフロー
//※※ifの配列外参照を対策するなら初めに書かないとダメ 対角線は両方チェック
//※※bit演算は比較演算子より後に計算されるから同時に使うときは()つける
//※※ループの中で配列を宣言しない(外で宣言して使いまわす)
//※※範囲for文で文字列、配列を受け取るときfor (auto& row : grid)のように&つけて参照渡し
//※※2^63→ほぼ10^19(他は2^10を10^3とすると楽),log2は10^xのxを10/3する(10^18→60)
//※※int:~10^9 ll:~10^18 int128:~10^38
//※※DFSはバックトラックが遅い！戻らなければO(N+M)。(BFSも同じ)
//※※辞書順は貪欲法！絶対後戻りしないようにする
//※※整数の平方根を使うならinteger_sqrtを使う！
//※※制約最大が小さい2次元DP/累積和は static int A[505][505] など固定長配列が速いことがある
//※※値はintで足りるか確認し、答えだけllにする。大きい配列はグローバル/staticに置く
//※※内側ループは固定できる差分をB配列などに前計算して、配列アクセスと計算を減らす

//ショートカットは次の動作。
//- `Ctrl+Alt+Enter`: 現在のC++ファイルを保存し、全テスト後に提出する。
//- `Ctrl+Alt+S`: 開いている全ファイルを保存してから、現在の `A.cpp`〜`G.cpp` のStressを開始する。
//- `Ctrl+Alt+X`: 現在の `A.cpp`〜`G.cpp` のStressを停止する。タスク出力へフォーカス中でも使用できる。
//- `Ctrl+Alt+G`: Generatorサーバーを起動または再利用し、ブラウザで開く。
std::ios_base::sync_with_stdio(false);
std::cin.tie(NULL);
cout<<setprecision(20);


auto start_time = chrono::steady_clock::now();






auto end_time = chrono::steady_clock::now();
auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
cerr << "Execution Time: " << duration.count() << " ms" << endl;
return 0;
}
/*



*/
