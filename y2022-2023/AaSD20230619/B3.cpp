#include <iostream>
#include <vector>

typedef long long ll;

using namespace std;
ll n;
const ll max_size = 400;
ll g[max_size][max_size];
ll find_in[max_size], ans[max_size], u[max_size], add_weight[max_size], point[max_size], way[max_size];
bool used[max_size];
const ll INF = LONG_LONG_MAX;

void solve() {
    for (int i = 1; i <= n; i++) {
        point[0] = i;
        ll j0 = 0;
        for (ll j = 0; j < n + 1; j++) {
            find_in[j] = INF;
            used[j] = false;
        }
        used[j0] = true;
        ll i0 = point[j0];
        ll delta = INF;
        ll j1;
        while (point[j0] != 0) {
            for (ll j = 1; j <= n; j++)
                if (!used[j]) {
                    ll cur = g[i0][j] - u[i0] - add_weight[j];
                    if (cur < find_in[j]) {
                        find_in[j] = cur, way[j] = j0;
                    }
                    if (find_in[j] < delta) {
                        delta = find_in[j];
                        j1 = j;
                    }
                }
            for (ll j = 0; j <= n; ++j) {
                if (used[j]) {
                    u[point[j]] += delta;
                    add_weight[j] -= delta;
                } else {
                    find_in[j] -= delta;
                }
            }
            j0 = j1;
            used[j0] = true;
            i0 = point[j0];
            delta = INF;
        }
        j1 = way[j0];
        point[j0] = point[j1];
        j0 = j1;
        while (j0) {
            j1 = way[j0];
            point[j0] = point[j1];
            j0 = j1;
        }
    }
}

int main() {
    cin >> n;
    for (ll i = 0; i < n + 1; i++) {
        u[i] = 0;
        way[i] = 0;
        point[i] = 0;
        add_weight[i] = 0;
        ans[i] = 0;
    }
    g[0][0] = 0;
    for (ll i = 1; i < n + 1; i++) {
        g[0][i] = 0;
        g[i][0] = 0;
        for (ll j = 1; j < n + 1; j++) {
            cin >> g[i][j];
        }
    }
    for(ll i = 0; i < n + 1; i++) {
        for(ll j = 0; j < n + 1; j++) {
            cout << g[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    solve();
    for(ll i = 1; i < n + 1; i++) {
        ans[point[i]] = i;
    }
    ll cost = -add_weight[0];
    cout << cost << endl;
    for(ll i = 1; i < n + 1; i++) {
        cout << i << " " << ans[i] << endl;
    }
    return 0;
}