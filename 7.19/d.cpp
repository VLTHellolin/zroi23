#define _EXT_CODECVT_SPECIALIZATIONS_H 0
#define _EXT_ENC_FILEBUF_H 0
#include <bits/extc++.h>

#ifndef HELLOLIN_FAST_IO_HPP
#define HELLOLIN_FAST_IO_HPP 1
#include <fstream>
#include <iostream>
#include <vector>

namespace hellolin {

constexpr static int FAST_IO_MAX_SIZE = (1 << 20) + 1;
constexpr static int FAST_O_STACK_SIZE = (1 << 8) + 1;

class fast_cin {
private:
    FILE *fi;
    size_t sz;
    bool fail;
    char buf[FAST_IO_MAX_SIZE], *buf_head, *buf_tail;

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
        for (T &i : x) {
            _read(i);
        }
    }

public:
    explicit fast_cin(FILE *_fi = stdin)
        : fi(_fi)
        , fail(0) {}
    explicit fast_cin(const char *_fi)
        : fail(0) {
        FILE *__fi = fopen(_fi, "r");
        fi = __fi;
    }
    void reopen(FILE *_fi = stdin) {
        fclose(fi);
        fi = _fi;
    }
    operator bool() { return !fail; }
    void flush() {
        if (buf_head == buf_tail) {
            buf_head = buf;
            buf_tail = buf + fread(buf, 1, FAST_IO_MAX_SIZE, fi);
        }
    }
    char get() {
        flush();
        char c = -1;
        if (buf_head == buf_tail) {
            fail = 1;
        } else {
            c = *buf_head++;
        }
        return c;
    }
    char peek() {
        flush();
        char c = -1;
        if (buf_head == buf_tail) {
            fail = 1;
        } else {
            c = *buf_head;
        }
        return c;
    }
    template <class T>
    fast_cin &operator>>(T &x) {
        _read(x);
        return *this;
    }
    template <class T>
    void operator()(T &x) {
        _read(x);
    }
    template <class T, class... Args>
    void operator()(T &x, Args &...args) {
        _read(x);
        operator()(args...);
    }
};

class fast_cout_end_line {
public:
    char c;
    bool f;
    fast_cout_end_line(char _c = '\n', bool _f = 1)
        : c(_c)
        , f(_f) {}
    ~fast_cout_end_line() {}
} hendl('\n', 0), hendlf('\n', 1);

class fast_cout {
private:
    FILE *fi;
    std::string buf;
    int cbuf[FAST_O_STACK_SIZE];
    int ctop = 0;
    int prec = 6;

    void _write(fast_cout_end_line x) {
        put(x.c);
        if (x.f) flush();
    }
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
        if (!ctop) {
            put('0');
        }
        while (ctop) {
            put(cbuf[ctop--] ^ '0');
        }
    }
    bool _round(int x) {
        return x > 4;
    }
    void _write(long double x) {
        ctop = 0;
        if (x < 0) {
            put('-');
            x = -x;
        }
        int t = x;
        x -= t;
        // _write(t);
        ctop = 0;
        // put('.');
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
        for (int i = 0; i < ctop; i++) {
            put(cbuf[i] ^ '0');
        }
        for (int i = ctop; i < prec; i++) {
            put('0');
        }
    }
    void _write(double x) {
        _write((long double) x);
    }
    void _write(float x) {
        _write((long double) x);
    }
    void _write(const char x) {
        put(x);
    }
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
    template <class T>
    void _write(std::vector<T> x) {
        for (T i : x)
            _write(i);
    }

public:
    explicit fast_cout(FILE *_fi = stdout)
        : fi(_fi) {}
    explicit fast_cout(const char *_fi) {
        FILE *__fi = fopen(_fi, "w");
        fi = __fi;
    }
    ~fast_cout() { flush(); }
    void reopen(FILE *_fi) {
        flush(1);
        fclose(fi);
        fi = _fi;
    }
    void precision(int x) {
        prec = x;
    }
    void flush(bool s = 0) {
        fwrite(buf.data(), 1, buf.size(), fi);
        buf.clear();
        if (s) fflush(fi);
    }
    void put(char x) {
        buf += x;
    }
    template <class T>
    fast_cout &operator<<(T x) {
        _write(x);
        return *this;
    }
    template <class T>
    void operator()(T x) {
        _write(x);
    }
    template <class T, class... Args>
    void operator()(T x, Args &...args) {
        _write(x);
        operator()(args...);
    }
};

fast_cin hin;
fast_cout hout;

} // namespace hellolin

#endif

namespace hellolin {
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
using ll = long long;
using ull = unsigned long long;
using lll = __int128;
template <class T>
using min_pq = __gnu_pbds::priority_queue<T, greater<T>, pairing_heap_tag>;
template <class T>
using max_pq = __gnu_pbds::priority_queue<T, less<T>, pairing_heap_tag>;
template <class T>
using vec = vector<T>;
using vecll = vector<ll>;
template <class T>
using vvec = vec<vec<T>>;
using vvecll = vec<vec<ll>>;
constexpr static ull mod_1e97 = 1e9 + 7, mod_998 = 998244353, mod_1e18 = 1e18, inf = LONG_LONG_MAX;
#define _x first
#define _y second
#define allof(x) x.begin(), x.end()
#define alllof(x) x.begin() + 1, x.end()
#define pb emplace_back
#ifdef LOCAL
#define dbg(x) cerr << __LINE__ << ": " << #x << " = " << x << endl
#else
#define dbg(x) void(0)
#endif
template <class T>
T pow(T x, ll y, ull m) {
    T z = 1;
    while (y) {
        if (y & 1) z = (z * x) % m;
        x = (x * x) % m;
        y >>= 1;
    }
    return z;
}
template <class T>
void readarr(T st, T ed) {
    while (st != ed) {
        cin >> *st;
        ++st;
    }
}
template <class T>
void writearr(T st, T ed, char s = ' ', bool e = 1) {
    while (st != ed) {
        cout << *st << s;
        ++st;
    }
    if (e) cout << endl;
}
void solve();
} // namespace hellolin

#define FILEIO 0
#define FILENAME ""
#define FASTIO 1
#define MULTI 0

int main() {
#if FILEIO
    freopen(FILENAME ".in", "r", stdin), freopen(FILENAME ".out", "w", stdout);
#endif
#if FASTIO
    std::ios::sync_with_stdio(false), std::cin.tie(nullptr), std::cout.tie(nullptr);
#endif
#if MULTI
    long long Ts;
    std::cin >> Ts;
    while (Ts--)
        hellolin::solve();
#else
    hellolin::solve();
#endif

    return 0;
}

namespace hellolin {
constexpr static ll N = 1e5 + 114, Sn = 330;
class block {
public:
    ull ff, f, sum;
    explicit block(ull x = 0) {
        ff = f = sum = x;
    }
};
array<block, N> b;
array<ll, N> a, ls, rs;
array<ll, N> la, ra, roo;
array<array<ll, Sn>, N> s;
ll n, q, ret, len, op, l, r;

void modify(ll p, ull v) {
    ll vv = v - a[p];
    for (ll i = p; i <= rs[roo[p]]; i++)
        b[i].f += vv;
    for (ll i = roo[p]; i <= ret; i++)
        b[i].ff += vv;
    for (ll i = 1; i <= ret; i++)
        b[i].sum += s[p][i] * vv;
    a[p] = v;
}
ull query_base(ll l, ll r) {
    ll lf = roo[l], rf = roo[r], ans = b[r].f;

    if (lf != rf) {
        ans = b[rs[lf]].f - b[lf].ff;
        ans += b[r].f + b[rf - 1].ff;
    }

    if (l != ls[lf]) ans -= b[l - 1].f;
    return ans;
}
ull query(ll l, ll r) {
    ll lf = roo[l], rf = roo[r];
    ull ans = 0;
    if (lf == rf) {
        for (ll i = l; i <= r; i++)
            ans += query_base(la[i], ra[i]);
        return ans;
    }

    for (ll i = l; i <= rs[lf]; i++)
        ans += query_base(la[i], ra[i]);
    for (ll i = lf + 1; i < rf; i++)
        ans += b[i].sum;
    for (ll i = ls[rf]; i <= r; i++)
        ans += query_base(la[i], ra[i]);
    return ans;
}

void solve() {
    hin >> n;
    // len = ceil(sqrt(n));
    len = sqrt(n) + 1;
    for (ll i = 1; i <= n; i++) {
        hin >> a[i];
        b[i].f = a[i];
    }
    for (ret = 1; ret * len <= n; ret++) {
        ls[ret] = len * (ret - 1) + 1;
        rs[ret] = len * (ret);
    }
    --ret;
    if (rs[ret] < n) {
        ls[ret + 1] = rs[ret] + 1;
        rs[++ret] = n;
    }
    for (ll i = 1; i <= ret; i++) {
        roo[ls[i]] = i;
        for (ll j = ls[i] + 1; j <= rs[i]; j++) {
            roo[j] = i;
            b[j].f += b[j - 1].f;
        }
        b[i].ff += b[i - 1].ff;
        b[i].ff += b[rs[i]].f;
    }

    for (ll i = 1; i <= n; i++) {
        hin >> la[i] >> ra[i];
    }
    for (ll i = 1; i <= ret; i++) {
        for (ll j = ls[i]; j <= rs[i]; j++) { // /cf
            ++s[la[j]][i];
            --s[ra[j] + 1][i];
        }
        for (ll j = 1; j <= n; j++) {
            s[j][i] += s[j - 1][i];
            b[i].sum += a[j] * s[j][i];
        }
    }

    hin >> q;

    for (ll i = 1; i <= q; i++) {
        hin >> op >> l >> r;
        if (op == 1)
            modify(l, r);
        else
            hout << query(l, r) << hendl;
    }
}
} // namespace hellolin