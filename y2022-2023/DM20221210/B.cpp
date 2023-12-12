#include <algorithm>
#include "iostream"
#include "vector"

using namespace std;


typedef int long long ill;
vector<ill> parent;

int parent_get (ill v) {
    return (parent[v] == v) ? v : (parent[v] = parent_get (parent[v]));
}

void unite_parents (ill a, ill b) {
    a = parent_get (a);
    b = parent_get (b);
    if (rand() & 1)
        swap (a, b);
    if (a != b)
        parent[a] = b;
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    freopen("destroy.in", "r", stdin);
    freopen("destroy.out", "w", stdout);

    ill n, m, s;
    cin >> n >> m >> s;
    cerr << n << " " << m << " " << s << "\n";
    vector<pair<ill, pair<ill, pair<ill, ill>>>> arr(m);
    parent.resize(n + 1);
    ill sum = 0;
    ill u, v, w;
    for (ill i = 0; i < m; i++) {
        cin >> u >> v >> w;
        arr[i] = make_pair(w, make_pair(i, make_pair(u, v)));
    }
    bool used[m];
    for (ill i = 1; i < n + 1; i++) {
        parent[i] = i;
    }
    for (ill i = 0; i < m; i++) {
        used[i] = false;
    }
    sort(arr.begin(), arr.end(), [](auto a, auto b) { return a.first > b.first || (a.first == b.first && a.second.first < b.second.first); });
    for (int i = 0; i < m; ++i) {
        ill a = arr[i].second.second.first, b = arr[i].second.second.second, ind = arr[i].second.first;
        if (parent_get(a) != parent_get(b)) {
            used[ind] = true;
            unite_parents(a, b);
        }
    }
    vector<ill> ans;
    for(ill i = m - 1; i >= 0; i--) {
        if(used[arr[i].second.first]) {
            continue;
        }
        if(sum + arr[i].first > s) {
            break;
        }
        sum += arr[i].first;
        ans.push_back(arr[i].second.first + 1);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for(ill i : ans) {
        cout << i << " ";
    }
    return 0;
}