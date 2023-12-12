#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <ctime>

using namespace std;


typedef long long ll;
typedef unsigned long long ull;

ull lazy_leng = 10;
ll base_len = 5;
ll base;

void norm_vec(vector<ll> &a) {
    for (ull i = 0; i < a.size() - 1; i++) {
        if (a[i] < 0) {
            a[i] = base + a[i];
            a[i + 1] -= 1;
        }
        a[i + 1] += a[i] / base;
        a[i] %= base;
    }
    while (a[a.size() - 1] >= base) {
        a.push_back(a[a.size() - 1] / base);
        a[a.size() - 2] %= base;
    }
}

void print_number(vector<ll> &a) {
    for (ull i = 0; i < a.size(); i++) {
        if (i != 0) {
            ll num = a[a.size() - 1 - i];
            if (num == 0) {
                num += 1;
            }
            ll len_num = 0;
            while (num != 0) {
                len_num += 1;
                num /= 10;
            }
            for (ll j = 0; j < base_len - len_num; j++) {
                cout << '0';
            }
        }
        cout << a[a.size() - 1 - i];
    }
}

void print_part_res(vector<ll> &a, vector<ll> &b, char dig) {
    print_number(a);
    cout << " " << dig << " ";
    print_number(b);
    cout << endl;
}

void print_part_res_with_ans(vector<ll> &a, vector<ll> &b, vector<ll> &c, char dig) {
    print_number(a);
    cout << " " << dig << " ";
    print_number(b);
    cout << " = ";
    print_number(c);
    cout << endl;
}

vector<ll> min_nulls(vector<ll> &a) {
    ull k = 0;
    for (ull i = 0; i < a.size(); i++) {
        if (a[i] != 0) {
            k = i + 1;
        }
    }
    if (k == 0) {
        return vector<ll>{0};
    }
    if (k == a.size()) {
        return a;
    }
    vector<ll> b;
    for (ull i = 0; i < k; i++) {
        b.push_back(a[i]);
    }
    return b;
}

void add_nulls(vector<ll> &a, vector<ll> &b) {
    while (a.size() < b.size()) {
        a.push_back(0);
    }
    while (b.size() < a.size()) {
        b.push_back(0);
    }
}

vector<ll> sum_vec(vector<ll> &a, vector<ll> &b) {
    add_nulls(a, b);
    vector<ll> c(a.size());
    for (ull i = 0; i < b.size(); i++) {
        c[i] = a[i] + b[i];
    }
    norm_vec(c);
//    print_part_res_with_ans(a, b, c, '+');
    return c;
}


vector<ll> sub_vec(vector<ll> &a, vector<ll> &b) {
    add_nulls(a, b);
    vector<ll> c(a.size());
    for (ull i = 0; i < b.size(); i++) {
        c[i] = a[i] - b[i];
    }
    norm_vec(c);
//    print_part_res_with_ans(a, b, c, '-');
    return c;
}

vector<ll> mul_vec(vector<ll> &a, vector<ll> &b) {
    add_nulls(a, b);
    vector<ll> c(2 * a.size());
    if (b.size() < lazy_leng) {
        for (ull i = 0; i < a.size(); i++) {
            for (ull j = 0; j < b.size(); j++) {
                if(i + j > c.size()) {
                    cout << "f**k all" << endl;
                }
                c[i + j] += a[i] * b[j];
            }
        }

    } else {
        ull k = a.size() / 2;
        vector<ll> a1, a2, b1, b2;
        for (ull i = 0; i < k; i++) {
            a1.push_back(a[i]);
            b1.push_back(b[i]);
        }
        for (ull i = k; i < a.size(); i++) {
            a2.push_back(a[i]);
            b2.push_back(b[i]);
        }
        vector<ll> a1b1 = mul_vec(a1, b1);
        vector<ll> a2b2 = mul_vec(a2, b2);
        vector<ll> a1_a2 = sum_vec(a1, a2);
        vector<ll> b1_b2 = sum_vec(b1, b2);
        vector<ll> a1_a2b1_b2 = mul_vec(a1_a2, b1_b2);
        vector<ll> part_sub = sub_vec(a1_a2b1_b2, a1b1);
        vector<ll> a1b2_a2b1 = sub_vec(part_sub, a2b2);
        a1b1 = min_nulls(a1b1);
        a2b2 = min_nulls(a2b2);
        a1b2_a2b1 = min_nulls(a1b2_a2b1);
        for (ull i = 0; i < a1b1.size(); i++) {
            if(i > c.size()) {
                cout << "f**k you and me" << endl;
            }
            c[i] += a1b1[i];
        }
        for (ull i = 2 * k; i < 2 * k + a2b2.size(); i++) {
            if(i > c.size()) {
                cout << "f**k you" << endl;
            }
            c[i] += a2b2[i - 2 * k];
        }
        for (ull i = k; i < k + a1b2_a2b1.size(); i++) {
            if(i > c.size()) {
                cout << "f**k me" << endl;
            }
            c[i] += a1b2_a2b1[i - k];
        }
    }
    norm_vec(c);
//    print_part_res_with_ans(a, b, c, '*');
    return c;
}

string random_number(int min, int max) {
    ull len = min + rand() % (max - min);
    string s;
    for (ull i = 0; i < len; i++) {
        if (i == 0) {
            s += ((rand() % 9) + 1) + '0';
        } else {
            s += (rand() % 10) + '0';
        }
    }
    return s;
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    srand(time(nullptr));
    base = (ll) pow(10, base_len);
    string v1, v2;
    cin >> v1 >> v2;
    bool less_zero = false;
    if ((v1[0] == '-' && v2[0] != '-') || (v1[0] != '-' && v2[0] == '-')) {
        less_zero = true;
    }
    ull len1 = v1.size();
    if(v1[0] == '-') {
        len1--;
    }
    ull len2 = v2.size();
    if(v2[0] == '-') {
        len2--;
    }
    ull len = 250000 / base_len;
    vector<ll> val1(len), val2(len);
    ll k = 0;
    for (ll i = (ll) v1.size() - 1; i >= 0; i -= base_len) {
        ll a = 0;
        for (ll j = base_len - 1; j >= 0; j--) {
            if ((i - j >= 0) && (v1[i - j] != '-')) {
                a *= 10;
                a += v1[i - j] - '0';
            }
        }
        if(val1.size() == k) {
            cout << "f**k f**k" << endl;
        }
        val1[k] = a;
        k++;
    }
    k = 0;
    for (ll i = (ll) v2.size() - 1; i >= 0; i -= base_len) {
        ll a = 0;
        for (ll j = base_len - 1; j >= 0; j--) {
            if ((i - j >= 0) && (v2[i - j] != '-')) {
                a *= 10;
                a += v2[i - j] - '0';
            }
        }
        if(val2.size() == k) {
            cout << "f**k f**k" << endl;
        }
        val2[k] = a;
        k++;
    }
    vector<ll> ans = mul_vec(val1, val2);
    norm_vec(ans);
    ans = min_nulls(ans);
    if (ans.size() == 1 && ans[0] == 0) {
        less_zero = false;
    }
    if (less_zero) {
        cout << '-';
    }
    print_number(ans);
    cout << endl;
    return 0;
}