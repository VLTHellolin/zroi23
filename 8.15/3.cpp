// * HELLOLIN'S CP CODE TEMPLATE v2.4.1
#ifndef ONLINE_JUDGE
#pragma GCC optimize(2, "inline", "unroll-loops", "no-stack-protector", "-ffast-math")
#endif
#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>
#include <bits/stdc++.h> // * FIX GCC 5.0
#ifdef LOCAL
#include <windows.h>
#include <psapi.h>
#endif

#ifndef HELLOLIN_IO_HPP
#define HELLOLIN_IO_HPP 1
#include <fstream>
#include <iostream>
#include <vector>

namespace hellolin {

constexpr static size_t IO_MAX_SIZE = (1 << 20) + 1;
constexpr static size_t PRINTER_STACK_SIZE = (1 << 8) + 1;

class scanner {
private:
    std::streambuf *fi;
    size_t sz;
    bool fail;
    char *buf, *buf_head, *buf_tail;

    template <class T>
    void _read(T &x) {
        bool s = 0;
        char c = get();
        x = 0;
        while (!isdigit(c) && c) {
            s = c == '-';
            c = get();
        }
        while (isdigit(c)) {
            x = (x << 1) + (x << 3) + (c ^ '0');
            c = get();
        }
        if (s) x = ~x + 1;
    }
    void _read(long double &x) {
        bool s = false;
        char c = get();
        x = 0;
        while (!isdigit(c) && c) {
            s = c == '-';
            c = get();
        }
        while (isdigit(c)) {
            x = x * 10 + (c ^ '0');
            c = get();
        }
        if (c == '.') {
            c = get();
            long double t = 1;
            while (isdigit(c)) {
                t /= 10;
                x += t * (c ^ '0');
                c = get();
            }
        }
        if (s) x = -x;
    }
    void _read(double &x) {
        long double y;
        _read(y);
        x = y;
    }
    void _read(float &x) {
        long double y;
        _read(y);
        x = y;
    }
    void _read(char &x) {
        do {
            x = get();
        } while (isspace(x));
    }
    void _read(char *x) {
        char c = get();
        while (isspace(c)) {
            c = get();
        }
        while (!isspace(c) && c) {
            *x++ = c;
            c = get();
        }
        *x = '\0';
    }
    void _read(std::string &x) {
        char c = get();
        while (isspace(c)) {
            c = get();
        }
        while (!isspace(c) && c) {
            x += c;
            c = get();
        }
    }
    template <class T, class U>
    void _read(std::pair<T, U> &x) {
        T a;
        U b;
        _read(a);
        _read(b);
        x = {a, b};
    }
    template <class T>
    void _read(std::vector<T> &x) {
        for (T &i : x)
            _read(i);
    }

public:
    explicit scanner(std::streambuf *_fi = std::cin.rdbuf(), size_t _sz = IO_MAX_SIZE) { reopen(_fi, _sz); }
    explicit scanner(const char *_fi, size_t _sz = IO_MAX_SIZE) { reopen(_fi, _sz); }
    void reopen(std::streambuf *_fi, size_t _sz = IO_MAX_SIZE) {
        fail = 0;
        fi = _fi;
        sz = _sz;
        buf = buf_head = buf_tail = new char[sz];
    }
    void reopen(const char *_fi, size_t _sz = IO_MAX_SIZE) {
        fail = 0;
        static std::ifstream tp(_fi);
        fi = tp.rdbuf();
        sz = _sz;
        buf = buf_head = buf_tail = new char[sz];
    }
    std::streambuf *rdbuf() { return fi; }

    operator bool() { return !fail; }
    void flush() {
        if (buf_head == buf_tail) {
            buf_head = buf;
            buf_tail = buf + fi->sgetn(buf, sz);
        }
    }
    char get() {
        flush();
        char c = -1;
        if (buf_head == buf_tail)
            fail = 1;
        else
            c = *buf_head++;
        return c;
    }
    char peek() {
        flush();
        char c = -1;
        if (buf_head == buf_tail)
            fail = 1;
        else
            c = *buf_head;
        return c;
    }
    template <class T>
    scanner &operator>>(T &x) {
        _read(x);
        return *this;
    }
    template <class T>
    void operator()(T &x) { _read(x); }
    template <class T, class... Args>
    void operator()(T &x, Args &...args) {
        _read(x);
        operator()(args...);
    }
};

class printer {
private:
    std::streambuf *fi;
    std::string buf;
    int cbuf[PRINTER_STACK_SIZE];
    int ctop = 0;
    int prec = 6;

    template <class T>
    void _write(T x) {
        ctop = 0;
        if (x < 0) {
            put('-');
            x = ~x + 1;
        }
        while (x) {
            cbuf[++ctop] = x % 10;
            x /= 10;
        }
        if (!ctop)
            put('0');
        while (ctop)
            put(cbuf[ctop--] ^ '0');
    }
    bool _round(int x) { return x > 4; }
    void _write(long double x) {
        ctop = 0;
        if (x < 0) {
            put('-');
            x = -x;
        }
        int t = x;
        x -= t;
        ctop = 0;
        if (x) {
            do {
                cbuf[ctop++] = x * 10;
                x = x * 10 - cbuf[ctop - 1];
            } while (ctop < prec - 1);
            cbuf[ctop++] = (int) (x * 10 + _round((int) ((x * 10 - ((int) (x * 10))) * 10)));
            if (cbuf[ctop - 1] == 10) {
                int nt = ctop - 1;
                while (cbuf[nt] == 10 && nt) {
                    cbuf[nt] = 0;
                    cbuf[--nt] += 1;
                }
                if (!nt && cbuf[nt] == 10) {
                    cbuf[nt] = 0;
                    t += 1;
                }
            }
        }
        _write(t);
        put('.');
        for (int i = 0; i < ctop; i++)
            put(cbuf[i] ^ '0');
        for (int i = ctop; i < prec; i++)
            put('0');
    }
    void _write(double x) { _write((long double) x); }
    void _write(float x) { _write((long double) x); }
    void _write(const char x) { put(x); }
    void _write(char *x) {
        while (*x != '\0')
            put(*x++);
    }
    void _write(const char *x) {
        while (*x != '\0')
            put(*x++);
    }
    void _write(std::string x) {
        for (char i : x)
            put(i);
    }
    void _write(bool x) {
        if (x)
            _write(1);
        else
            _write(0);
    }
    template <class T>
    void _write(std::vector<T> x) {
        for (T i : x)
            _write(i);
    }

public:
    explicit printer(std::streambuf *_fi = std::cout.rdbuf(), size_t _sz = IO_MAX_SIZE) { reopen(_fi, _sz); }
    explicit printer(const char *_fi, size_t _sz = IO_MAX_SIZE) { reopen(_fi, _sz); }
    void reopen(std::streambuf *_fi, size_t _sz = IO_MAX_SIZE) {
        fi = _fi;
        buf.reserve(_sz);
    }
    void reopen(const char *_fi, size_t _sz = IO_MAX_SIZE) {
        static std::ofstream tp(_fi);
        fi = tp.rdbuf();
        buf.reserve(_sz);
    }
    std::streambuf *rdbuf() { return fi; }

    ~printer() { flush(); }
    void flush() {
        fi->sputn(buf.c_str(), buf.size());
        buf.clear();
    }
    void put(char x) { buf += x; }
    template <class T>
    printer &operator<<(T x) {
        _write(x);
        return *this;
    }
    template <class T>
    void operator()(T x) { _write(x); }
    template <class T, class... Args>
    void operator()(T x, Args &...args) {
        _write(x);
        operator()(args...);
    }
};

} // namespace hellolin

#endif

namespace hellolin {
namespace lib {
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
using ulll = __uint128_t;
const static std::string yesno_str[2][3] = {{"no", "No", "NO"}, {"yes", "Yes", "YES"}};
inline std::string yesno(bool x, int y) { return yesno_str[x][y] + '\n'; }
template <class T> inline T fpow(T x, ull y, T mod) { T res = 1; for(; y; y >>= 1, x = x * x % mod) if(y & 1) res = res * x % mod; return res; }
template <class T, class U> inline bool chmax(T &x, U y) { return y > x ? (x = y, 1) : 0; }
template <class T, class U> inline bool chmin(T &x, U y) { return y < x ? (x = y, 1) : 0; }
#define rep(l, x, a, b) for (l x = a, x##END = b; x <= x##END; ++x)
#define per(l, x, a, b) for (l x = a, x##END = b; x >= x##END; --x)
#define fi first
#define se second
#define allof(x) x.begin(), x.end()
#define alof(x) x.begin() + 1, x.end()
#define allnof(x, n) x.begin(), x.begin() + n + 1
#define alnof(x, n) x.begin() + 1, x.begin() + n + 2
#define lowbit(x) (x & -x)
#define mp make_pair
#define pb emplace_back
#define nl '\n'
} // namespace lib
using namespace lib;

// * CORE CODE BEGIN * //
constexpr static int N = 1e5 + 11;
constexpr static ll Mod = 998244353;
scanner scan;
printer print;
int n;
lll a[N], lim, tp, ans;
std::vector<lll> v;
void solve() {
    scan >> n;
    if(n==1) {
        scan >> a[1];
        print << a[1] * a[1] % Mod << nl;
        return;
    }
    lim = 1;
    rep(int, i, 1, n) {
        scan >> a[i];
        lim *= a[i];
    }
    rep(int, i, 1, n) {
        tp = a[i];
        while(tp <= lim) {
            v.pb(tp);
            if(tp == lim) break;
            tp += a[i];
        }
    }
    std::sort(allof(v));
    tp = 0;
    for(auto i : v) {
        ans = (ans + ((i - tp) * (i - tp) % Mod)) % Mod;
        tp = i;
    }
    print << ans << nl;

}
// * CORE CODE END * //

} // namespace hellolin

int main() {
    // freopen(".in", "r", stdin);
    // freopen(".out", "w", stdout);
    // freopen(".dbg", "w", stderr);
#ifdef LOCAL
    clock_t st = clock(), ed;
#endif
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(nullptr), std::cout.tie(nullptr);
    // std::cout << std::fixed << std::setprecision(6);
    std::cerr << std::fixed << std::setprecision(6);
    hellolin::solve();
#ifdef LOCAL
    ed = clock();
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    std::cerr << "---------- DEBUG INFO ----------\n";
    std::cerr << "Time: " << (long double)(ed - st) / CLOCKS_PER_SEC << "s.\n";
    std::cerr << "Memory: " << pmc.WorkingSetSize / 1000000 << "MB.\n";
#endif
    return 0;
}