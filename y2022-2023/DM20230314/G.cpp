#include <iostream>
#include <bits/stdc++.h>
#include <string>
using namespace std;
typedef long long ll;
string for_parse;
ll now = 0;
ll* parse() {
    if(for_parse[now] == 'B') {
        ++now;
        ll* p = new ll[7];
        fill_n(p, 7, 0);
        p[1] = 1;
        return p;
    } else if(for_parse[now] == 'P') {
        ++now;
        ++now;
        ll* p1 = parse();
        ++now;
        ll* p2 = parse();
        ++now;
        ll* ans = new ll[7];
        fill_n(ans, 7, 0);
        for(ll i = 0; i < 7; i++) {
            for(ll j = 0; j < 7; j++) {
                if(i + j < 7) {
                    ans[i + j] += p1[i] * p2[j];
                }
            }
        }
        return ans;
    } else if(for_parse[now] == 'L') {
        ++now;
        ++now;
        ll* p = parse();
        ++now;
        ll* ans = new ll[7];
        fill_n(ans, 7, 0);
        for(ll i = 0; i < 7; i++) {
            ans[i] = (i == 0 ? 1 : 0);
            for(ll j = 0; j < i; j++) {
                ans[i] += p[i - j] * ans[j];
            }
        }
        return ans;
    } else if(for_parse[now] == 'S') {
        ++now;
        ++now;
        ll* p = parse();
        ++now;
        ll* ans = new ll[7];
        fill_n(ans, 7, 0);
        ll* q = new ll[7];
        q[0] = 1;
        q[1] = -p[1];
        q[2] = (p[1] * (p[1] - 1)) / 2 - p[2];
        q[3] = p[1] * p[2] - p[3] - (p[1] * (p[1] - 1) * (p[1] - 2)) / (2 * 3);
        q[4] = (p[2] * (p[2] - 1)) / 2 - p[4] + p[1] * p[3] - p[2] * (p[1] * (p[1] - 1)) / 2 +
                (p[1] * (p[1] - 1) * (p[1] - 2) * (p[1] - 3)) / (2 * 3 * 4);
        q[5] = p[2] * p[3] - p[5] + p[4] * p[1] - (p[2] * (p[2] - 1)) / 2 * p[1] - (p[1] * (p[1] - 1)) / 2 * p[3] +
                (p[1] * (p[1] - 1) * (p[1] - 2)) / (2 * 3) * p[2] - (p[1] * (p[1] - 1) * (p[1] - 2) * (p[1] - 3) * (p[1] - 4)) / (2 * 3 * 4 * 5);
        q[6] = p[5] * p[1] - p[1] * p[2] * p[3] + (p[1] * (p[1] - 1)) / 2 * (p[2] * (p[2] - 1)) / 2 - (p[1] * (p[1] - 1)) / 2 * p[4] +
                (p[1] * (p[1] - 1) * (p[1] - 2)) / (2 * 3) * p[3] - (p[1] * (p[1] - 1) * (p[1] - 2) * (p[1] - 3)) / (2 * 3 * 4) * p[2] +
                (p[1] * (p[1] - 1) * (p[1] - 2) * (p[1] - 3) * (p[1] - 4) * (p[1] - 5)) / (2 * 3 * 4 * 5 * 6) + (p[3] * (p[3] - 1)) / 2 -
                p[6] - (p[2] * (p[2] - 1) * (p[2] - 2)) / (2 * 3) + p[2] * p[4];
        for(ll i = 0; i < 7; i++) {
            ans[i] = (i == 0 ? 1 : 0);
            for(ll j = 0; j < i; j++) {
                ans[i] -= q[i - j] * ans[j];
            }
        }
        return ans;
    }
    ll* ret = new ll[7];
    fill_n(ret, 7, 0);
    return ret;
}

int main() {
    cin >> for_parse;
    ll* ans = parse();
    for(ll i = 0; i < 7; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}