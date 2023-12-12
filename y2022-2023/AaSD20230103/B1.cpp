#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;
typedef int long long ill;
bool used[100001];
ill n, m, s, t;
vector<vector<pair<ill, ill>>> edges;
vector<ill> topsort;
vector<ill> passes;
ill MAX_LEN = INT32_MAX;

void dfs(ill v) {
//    cout << "come in " << v << "\n";
    used[v] = true;
    for(pair<ill, ill> edge : edges[v]) {
        if(!used[edge.first]) {
            dfs(edge.first);
        }
    }
    topsort.push_back(v);
//    cout << "push " << v << " " << topsort.top() << "\n";
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> s >> t;

    passes.resize(n + 1);
    fill(passes.begin(), passes.end(), MAX_LEN);
    edges.resize(n + 1);

    for (ill i = 0; i < n + 1; i++) {
        used[i] = false;
    }

    ill b, e, w;
    for (ill i = 0; i < m; i++) {
        cin >> b >> e >> w;
        edges[b].push_back(pair<ill, ill>(e, w));
    }
    dfs(s);
    reverse(topsort.begin(), topsort.end());
    passes[s] = 0;
//    cout << topsort.size() << "\n";

    if(!used[t]) {
        cout << "Unreachable";
    } else {
        for (ill from: topsort) {
            for (auto edge: edges[from]) {
                ill to = edge.first;
                ill w = edge.second;
                passes[to] = min(passes[from] + w, passes[to]);
            }
        }
        cout << passes[t];
    }
    return 0;
}