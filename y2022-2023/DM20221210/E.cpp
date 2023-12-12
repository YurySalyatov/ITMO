#include "iostream"
#include "cmath"
#include "set"
#include "vector"
#include "map"
#include <algorithm>

using namespace std;


typedef unsigned long long ill;
ill n, m;
set<ill> has;
vector<pair<ill, ill>> w;
void del_cicles(ill k, int start) {
    for(int i = start; i < n; ++i) {
        ill j = (k | (1 << i));
        if(j != k && has.find(j) != has.end()) {
            has.erase(j);
            del_cicles(j, i);
        }
    }
}
ill find_max_base() {
    ill maxx = 0;
    ill a = 0;
    for (auto & i : w) {
        if (has.find(a | (1 << i.first)) != has.end()) {
            a |= (1 << i.first);
            maxx += i.second;
        }
    }
    return maxx;
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    freopen("cycles.in", "r", stdin);
    freopen("cycles.out", "w", stdout);
    cin >> n >> m;
    w.resize(n);
    ill a;
    for (ill i = 0; i < n; i++) {
        cin >> a;
        w[i] = make_pair(i, a);
    }
    for(ill i = 0; i < (1 << n); ++i) {
        has.insert(i);
    }
    for (ill i = 0; i < m; ++i) {
        ill count, k = 0;
        cin >> count;
        for (ill j = 0; j < count; ++j) {
            cin >> a;
            a--;
            k |= (1 << a);
        }
        has.erase(k);
        del_cicles(k, 0);
    }
    sort(w.begin(), w.end(), [](auto a, auto b) { return a.second > b.second; });
    cout << find_max_base();
    return 0;
}