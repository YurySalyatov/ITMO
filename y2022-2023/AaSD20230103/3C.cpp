#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include "cmath"

using namespace std;

typedef long long ll;

vector<ll> first, second;

void srt(vector<ll> &second, vector<ll> &first) {
    ll n = second.size();
    vector<vector<ll> > v(n);

    for (ll i = 0; i < n; i++)
        v[first[second[i]]].push_back(second[i]);

    vector<ll> neww;

    for (ll i = 0; i < n; i++) {
        for (ll j: v[i]) {
            neww.push_back(j);
        }
    }
    second = neww;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    s += '$';

    ll n = s.size();

    second.resize(n);
    first.resize(n);

    vector<pair<char, ll> > v;
    for (ll i = 0; i < n; i++) {
        v.push_back(make_pair(s[i], i));
    }
    sort(v.begin(), v.end());
    first[0] = 0;
    second[0] = v[0].second;
    for (ll i = 1; i < n; i++) {
        second[i] = v[i].second;
        if (v[i].first == v[i - 1].first) {
            first[second[i]] = first[second[i - 1]];
        } else {
            first[second[i]] = first[second[i - 1]] + 1;
        }
    }


    for (ll k = 0; (1 << k) < n; k++) {
        for (ll i = 0; i < n; i++) {
            second[i] = (second[i] - (1 << k) + n) % n;
        }
        srt(second, first);
        vector<ll> neww(n);
        neww[0] = 0;
        pair<ll, ll> prev = make_pair(first[second[0]], first[(second[0] + (1 << k)) % n]);
        for (int i = 1; i < n; i++) {
            pair<ll, ll> now = make_pair(first[second[i]], first[(second[i] + (1 << k)) % n]);
            if (now == prev) {
                neww[second[i]] = neww[second[i - 1]];
            } else {
                neww[second[i]] = neww[second[i - 1]] + 1;
            }
            prev = now;
        }
        first = neww;
    }

    for (ll i = 1; i < n; i++)
        cout << second[i] + 1 << " ";
    cout << "\n";

    vector<ll> diff(n);
    ll k = 0;
    for (ll i = 0; i < n - 1; i++) {
        ll pi = first[i], j = second[pi - 1];
        while (s[i + k] == s[j + k])
            k++;
        diff[pi] = k;
        k = max((ll) 0, k - 1);
    }

    for (int i = 2; i < n; i++)
        cout << diff[i] << " ";
    return 0;
}