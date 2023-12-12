#include "iostream"
#include "vector"
using namespace std;

long long MOD = 998244353;

vector<long long> sqrT;
vector<long long> exP;
vector<long long> ln;
vector<long long> one_pow_p;
long long mod(long long a) {
    return ((a % MOD) + MOD) % MOD;
}

long long find_reverse_number(long long m) {
    m = mod(m);
    long long i = MOD - 2;
    long long ans = 1;
    while (i) {
        if (i & 1) {
            ans = (ans * m) % MOD;
        }
        i >>= 1;
        m = (m * m) % MOD;
    }
    return ans;
}

void pow_p_next_test(long long m, long long n, long long i, const long long *p) {
    vector<long long> next(m); // m
    next.assign(m, 0);
    for(long long k = 0; k < m; k++) {
        for (long long j = 0; j < m; j++) {
            if(k + j < m && j < n + 1) {
                next[k + j] = mod(next[k + j] + mod(one_pow_p[k] * p[j]));
            }
        }
    }
    one_pow_p = next;
}

void pow_p_next(long long n, long long i, const long long *p) {
    vector<long long> next(n * i + 1); // m
    next.assign(n * i + 1, 0);
    for(long long k = 0; k <= n * (i - 1); k++) {
        for (long long j = 0; j <= n; j++) {
            next[k + j] = mod(next[k + j] + mod(one_pow_p[k] * p[j]));
        }
    }
    one_pow_p = next;
}

void sqrt_numbers(long long m) {
    long long cnst = find_reverse_number(2);
    sqrT[0] = 1;
    sqrT[1] = cnst;
    for(long long i = 2; i < m; i++) {
        sqrT[i] = mod(mod(mod(sqrT[i - 1] * (MOD - 1)) * (2 * (i - 1) - 1)) *
                      mod(cnst * find_reverse_number(i)));
    }
}

void exP_numbers(long long m) {
    exP[0] = 1;
    long long k = 1;
    for(long long i = 1; i < m; i++) {
        k = (k * i) % MOD;
        exP[i] = find_reverse_number(k);
    }
}

void ln_numbers(long long m) {
    ln[0] = 0;
    for(long long i = 1; i < m; i++) {
        ln[i] = i % 2 == 1 ? find_reverse_number(i) : find_reverse_number(-i);
    }
}

int main() {
    long long n, m;
    cin >> n >> m;
    sqrT.resize(m);
    exP.resize(m);
    ln.resize(m);
    long long p[n + 1];
    for(long long i = 0; i < n + 1; i++) {
        long long k;
        cin >> p[i];
    }
    exP_numbers(m);
    ln_numbers(m);
    sqrt_numbers(m);
    one_pow_p.resize(m);
    for(long long i = 0; i < min(m, n + 1); i++) {
        one_pow_p[i] = p[i];
    }
    long long ansS[m], ansE[m], ansL[m];
    fill_n(ansS, m, 0);
    fill_n(ansE, m, 0);
    fill_n(ansL, m, 0);
    ansS[0] = sqrT[0];
    ansE[0] = exP[0];
    ansL[0] = ln[0];
    // for sqrT exp and ln
    for (long long i = 1; i < m; i++) {
        for(long long j = i; j <= n * i; j++) {
            if(j < m) {
                ansS[j] = (ansS[j] + mod(sqrT[i] * one_pow_p[j])) % MOD;
                ansE[j] = (ansE[j] + mod(exP[i] * one_pow_p[j])) % MOD;
                ansL[j] = (ansL[j] + mod(ln[i] * one_pow_p[j])) % MOD;
            }
        }
        pow_p_next_test(m, n, i + 1, p);
    }
    for(auto i : ansS) {
        cout << i << " ";
    }
    cout << "\n";
    for(auto i : ansE) {
        cout << i << " ";
    }
    cout << "\n";
    for(auto i : ansL) {
        cout << i << " ";
    }
    cout << "\n";
    return 0;
}

