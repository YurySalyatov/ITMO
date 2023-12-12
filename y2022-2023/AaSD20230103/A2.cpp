#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;
typedef int long long ill;
vector<bool> used;
vector<bool> used2;
vector<ill>topsort;
vector<ill>comp;
vector<vector<ill>> edges;
vector<vector<ill>> r_edges;
ill n, m;

void dfs(ill x) {
    used[x] = true;
    for(ill i : edges[x]) {
        if(!used[i]) {
            dfs(i);
        }
    }
    topsort.push_back(x);
}

void kss(ill x, ill k) {
    comp[x] = k;
    for(ill i : r_edges[x]) {
        if(!comp[i]) {
            kss(i, k);
        }
    }
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    edges.resize(n);
    r_edges.resize(n);
    used.resize(n);
    comp.resize(n);
    std::fill(used.begin(), used.end(), false);
    std::fill(comp.begin(), comp.end(), 0);

    ill a, b;
    for (ill i = 0; i < m; i++) {
        cin >> a >> b;
        --a;
        --b;
        edges[a].push_back(b);
        r_edges[b].push_back(a);
    }
    for(ill i = 0; i < n; i++) {
        if(!used[i]) {
            dfs(i);
        }
    }
    reverse(topsort.begin(), topsort.end());
    ill k = 1;
    for(ill i : topsort) {
        if(!comp[i]) {
            kss(i, k);
            k++;
        }
    }
    k--;
    used2.resize(k);
    fill(used2.begin(), used2.end(), false);
    for(ill i = 0; i < n; i++) {
        for(ill j: edges[i]) {
            if(comp[i] != comp[j]) {
                used2[comp[i] - 1] = true;
            }
        }
    }
    vector<ill> ans;
    for(ill i = 0; i < n; i++) {
        if(!used2[comp[i] - 1]) {
            ans.push_back(i + 1);
            used2[comp[i] - 1] = true;
        }
    }
    cout << ans.size() << "\n";
    for (ill i : ans) {
        cout << i << " ";
    }
    return 0;
}

