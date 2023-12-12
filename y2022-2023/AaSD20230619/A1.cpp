#include "iostream"
#include "vector"

using namespace std;


typedef int long long ill;
ill n, m;
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

    cin >> n >> m;
    g.resize(n);
    par_soch.resize(m);
    par_soch.assign(m, -1);
    used.resize(n);

    ill v;
    for (ill i = 0; i < n; i++) {
        cin >> v;
        while (v != 0) {
            g[i].push_back(v - 1);
            cin >> v;
        }
    }
    for (ill i = 0; i < n; i++) {
        used.assign(n, false);
        get_par_soch(i);
    }
    ill count = 0;
    for (int i = 0; i < m; i++) {
        if (par_soch[i] != -1) {
            count++;
        }
    }
    cout << count << endl;
    for (ill i = 0; i < m; i++) {
        if (par_soch[i] != -1) {
            cout << par_soch[i] + 1 << " " << i + 1 << endl;
        }
    }
    return 0;
}