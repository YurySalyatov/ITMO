#include "iostream"
#include "vector"
using namespace std;
typedef long long ll;
vector<ll> sqrT;

ll MOD = 1000000000 + 7;
void sqrt_numbers(ll m) {
    sqrT[0] = 0;
    sqrT[1] = 1;
    for(ll i = 2; i < m; i++) {
        sqrT[i] = sqrT[i - 1] * (1 - 2 * (i - 1)) * (-2) / i;
    }
}

int main() {
    ll k, m, get;
    cin >> k >> m;
    get = m;
    m++;
    m*=2;
    sqrT.resize(m);
    long long c[k];
    for (long long i = 0; i < k; i++) {
        cin >> c[i];
    }
    sqrt_numbers(m);
    for(auto i : sqrT) {
        cout << i << " ";
    }
    cout << endl;
    ll a[m];
    fill_n(a, m, 0);
    for(ll i = 0; i < k; i++) {
        if(c[i] < m) {
            a[c[i]] = 1;
        }
    }
    ll n_a[m];
    fill_n(n_a, m, 0);
    for(ll i = 0; i < m; i++) {
        for(ll j = 0; j < m; j++) {
            if(i + j < m) {
                n_a[i + j] += a[i] * a[j];
            }
        }
    }
    ll pre_ans[m];
    fill_n(pre_ans, m, 0);
    for(ll i = 0; i < m; i++) {
        for (ll j = 0; j < m; j++) {
            if(i + j < m){
                pre_ans[i + j] += sqrT[i] * n_a[j];
            }
        }
    }
    ll shift = 0;
    ll i = 0;
    while (a[i] == 0) {
        i++;
        shift = i;
    }
    ll dev[get + 1];
    for (long long i = shift; i < get + shift; i++) {
        dev[i - shift] = pre_ans[i];
        for(long long j = shift; j < i + shift; j++) {
            dev[i - shift] = ((dev[i - shift] - (i - j < m ? a[i - j] * dev[j - shift] : 0)) % MOD + MOD) % MOD;
        }
    }
    for(long long i : dev) {
        cout << ((i % MOD) + MOD) % MOD << " ";
    }
    cout << endl;
    return 0;
}