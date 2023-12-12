#include <iostream>
#include <bits/stdc++.h>
#include <string>
using namespace std;
typedef long long ll;
int main() {
    long long r, d;
    cin >> r >> d;
    d++;
    ll f[d], a[d], q[d + 1], p[d];
    fill_n(p, d, 0);
    for(ll i = 0; i < d; i++) {
        cin >> f[i];
    }
    for(ll i = 0; i < d; i++) {
        a[i] = f[0];
        for(ll j = 1; j < d; j++) {
            a[i] += f[j] * (ll)pow(i, j);
        }
        a[i] *= (ll)pow(r, i);
    }
    q[0] = 1;
    q[1] = -r;
    for(ll i = 2; i < d + 1; i++) {
        q[i] = 0;
        for(ll j = i; j  > 0; j--) {
            q[j] += q[j - 1] * -r;
        }
    }

    for(ll i = 0; i < d; i++) {
        for(ll j = 0; j < d + 1; j++) {
            if(i + j < d) {
                p[i + j] += a[i] * q[j];
            }
        }
    }
    ll degp = 0;
    for(ll i = 0; i < d; i++) {
        if(p[i] != 0) {
            degp= i;
        }
    }
    cout << degp << endl;
    for(auto j : p) {
        cout << j << " ";
    }
    cout << endl << d << endl;
    for(auto j : q) {
        cout << j << " ";
    }
    cout << endl;
    return 0;
}