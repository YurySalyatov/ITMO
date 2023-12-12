#include <iostream>
#include <bits/stdc++.h>
#include <string>

typedef long long ll;
using namespace std;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

class Drob {
    ll x;
    ll y;
public:
    Drob(ll x, ll y) {
        this->x = x;
        this->y = y;
    }

    Drob(Drob const &that) {
        this->x = that.x;
        this->y = that.y;
    }

    Drob() {
        x = 0;
        y = 1;
    }

    Drob operator+(const Drob &that) const {
        ll g = gcd(y, that.y);
        ll m = y * (that.y / g);
        ll k = x * (that.y / g) + that.x * (y / g);
        g = gcd(abs(k), abs(m));
        return {k / g, m / g};
    }

    Drob operator-(const Drob &that) const {
        ll g = gcd(y, that.y);
        ll m = y * (that.y / g);
        ll k = x * (that.y / g) - that.x * (y / g);
        g = gcd(abs(m), abs(k));
        return {k / g, m / g};
    }

    Drob operator-() const {
        return {-x, y};
    }

    Drob operator*(const Drob &that) const {
        ll g_x1_y2 = gcd(abs(x),that.y);
        ll g_x2_y1 = gcd(abs(that.x), y);
        ll k = (x / g_x1_y2) * (that.x / g_x2_y1);
        ll m = (y / g_x2_y1) * (that.y / g_x1_y2);
        return {k, m};
    }

    Drob operator/(const Drob &that) const {
        if (that.x == 0) {
            throw std::exception();
        }
        ll g_x = gcd(abs(x), abs(that.x));
        ll g_y = gcd(y, that.y);
        ll m = (y / g_y) * (that.x / g_x);
        ll k = (x / g_x) * (that.y / g_y);
        k = m < 0 ? -k : k;
        return {k, abs(m)};
    }

    string to_string() const {
        return std::to_string((long long)x) + "/" + std::to_string((long long)y);
    }
};

vector<Drob> ans;

void div(ll r, ll k, ll deg, vector<Drob> &vec) {
    ans.resize(k);
    for (ll i = deg; i > 0; i--) {
        vector<Drob> n(vec.size() - 1);
        for (auto j = (ll) vec.size() - 1; j > 0; j--) {
            Drob coef = vec[j] / Drob(-r, 1);
            vec[j - 1] = vec[j - 1] - coef * Drob(1, 1);
            n[j - 1] = coef;
        }
        ans[k - 1] = vec[0];
        k--;
        vec = n;
    }
    ans[k - 1] = vec[0];
}


int main() {
    long long r, k, deg;
    cin >> r >> k;
    vector<Drob> p;
    for (ll i = 0; i < k + 1; i++) {
        long long l;
        cin >> l;
        if (l != 0) {
            deg = i;
        }
        p.emplace_back(l, 1);
    }
    k++;
    div(r, k, deg, p);
    vector<Drob> peresh(k);
    vector<Drob> res(k);
    peresh[0] = Drob(1, 1);
    for (ll i = 0; i < k; i++) {
        for (ll j = 0; j <= i; j++) {
            res[j] = res[j] + peresh[j] * ans[i];
        }
        if (i < k - 1) {
            for (ll j = i + 1; j > 0; j--) {
                peresh[j] = peresh[j] + peresh[j - 1] * Drob(1, i + 1);
            }
        }

    }
    for(auto &d : res) {
        cout << d.to_string() << " ";
    }
    cout << endl;
    return 0;
}