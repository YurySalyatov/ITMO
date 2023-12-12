#include "iostream"

using namespace std;

long long MOD = 998244353;

int main() {
    long long n, m;
    cin >> n >> m;
    n++;
    m++;
    long long p[n], q[m];
    fill_n(p, n, 0);
    fill_n(q, m, 0);
    for (long long i = 0; i < n; i++) {
        cin >> p[i];
    }
    for (long long i = 0; i < m; i++) {
        cin >> q[i];
    }
    long long dev[1000];
    fill_n(dev, 1000, 0);
    cout << max(n, m) - 1 << endl;
    for (long long i = 0; i < max(n, m); i++) {
        long long ans = 0;
        if (i < n) {
            ans += ((p[i] % MOD) + MOD) % MOD;
        }
        if (i < m) {
            ans += ((q[i]% MOD) + MOD) % MOD;
        }
        cout << ((ans % MOD) + MOD) % MOD;
        if (i < max(n, m) - 1) {
            cout << " ";
        }
    }
    cout << endl;
    cout << m + n - 2 << endl;
    for (long long i = 0; i < n + m - 1; i++) {
        long long ans = 0;
        for (long long j = 0; j <= i; j++) {
            if(j < n && i - j < m) {
                ans += ((p[j] * q[i - j] % MOD) + MOD) % MOD;
            }
        }
        cout << ((ans % MOD) + MOD) % MOD;
        if (i < n + m - 1) {
            cout << " ";
        }
    }
    cout << endl;
    for (long long i = 0; i < 1000; i++) {
        dev[i] = i < n ? ((p[i] % MOD) + MOD) % MOD : 0;
        for(long long j = 0; j < i; j++) {
            dev[i] = ((dev[i] - (i - j < m ? q[i - j] * dev[j] : 0)) % MOD + MOD) % MOD;
        }
    }
    for(long long i : dev) {
        cout << ((i % MOD) + MOD) % MOD << " ";
    }
    cout << endl;
    return 0;
}

