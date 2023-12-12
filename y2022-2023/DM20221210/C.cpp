#include <algorithm>
#include "iostream"
#include "vector"

using namespace std;


typedef int long long ill;
ill n;
vector<pair<ill, ill>> w;
vector<vector<ill>> g;
vector<ill> par_soch;
vector<bool> used;

bool get_par_soch(ill v) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (ill i = 0; i < g[v].size(); i++) {
        ill to = g[v][i];
        if (par_soch[to] == -1 || get_par_soch(par_soch[to])) {
            par_soch[to] = v;
            return true;
        }
    }
    return false;
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
    cin >> n;
    w.resize(n);
    g.resize(n);
    par_soch.resize(n);
    par_soch.assign(n, -1);
    used.resize(n);
    ill wo;
    for (ill i = 0; i < n; i++) {
        cin >> wo;
        w[i] = make_pair(i, wo);
    }

    ill col, v;
    for (ill i = 0; i < n; i++) {
        cin >> col;
        for (ill j = 0; j < col; j++) {
            cin >> v;
            g[i].push_back(v - 1);
        }
    }
    sort(w.begin(), w.end(), [](auto a, auto b) { return a.second >= b.second; });
//    for (auto k: w) {
//        cerr << k.first << " " << k.second << "\n";
//    }
//    for(const auto& j : g) {
//        for(auto k : j) {
//            cerr << k << " ";
//        }
//        cerr << "\n";
//    }
    for (ill i = 0; i < n; i++) {
        used.assign(n, false);
        v = w[i].first;
        get_par_soch(v);
    }
    vector<ill> ans(n);
    ans.assign(n, 0);
    for (ill i = 0; i < n; i++) {
        if (par_soch[i] != -1) {
            ans[par_soch[i]] = i + 1;
        }
    }
    for(ill i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}