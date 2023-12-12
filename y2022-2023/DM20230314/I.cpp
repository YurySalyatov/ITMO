#include <iostream>
#include <bits/stdc++.h>
#include <string>

typedef long long ll;
using namespace std;
ll MOD = 104857601;

ll mod(ll i) {
    return ((i % MOD) + MOD) % MOD;
}

void print(ll* a, ll len) {
    for(ll i = 0; i < len; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

int main() {
    ll k, n;
    cin >> k >> n;
    ll a[2 * k], c[k + 1];
    for(ll i = 0; i < k; i++) {
        cin >> a[i];
    }
    for(ll i = 1; i < k + 1; i++) {
        cin >> c[i];
        c[i] = -c[i];
    }
    c[0] = 1;
    ll p[2 * k + 1];
    n--;
    while (n >= k) {
        for (ll i = k; i < 2 * k; i++) {
            ll sum = 0;
            for(ll j = 1; j < k + 1; j++) {
               sum = mod(sum + -c[j] * a[i - j]);
           }
            a[i] = sum;
        }
        print(a, 2 * k);
        fill_n(p, 2 * k + 1, 0);
        for (ll i = 0; i < k + 1; i++) {
            for(ll j = 0; j < k + 1; j++) {
                p[i + j] = mod(p[i + j] + c[i] * c[j] * (j % 2 == 0 ? 1 : -1));
            }
        }
        for(ll i = 0; i < k + 1; i++) {
            c[i] = p[2 * i];
        }
        print(p, 2 * k + 1);
        print(c, k + 1);
        for(ll i = 0; i < k; i++) {
            a[i] = a[2 * i + (n % 2)];
        }
        print(a, k);
        n /= 2;
    }
    cout << a[n] << endl;
    return 0;
}