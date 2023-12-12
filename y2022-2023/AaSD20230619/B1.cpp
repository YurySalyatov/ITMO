#include "iostream"
#include "vector"

using namespace std;


typedef int long long ll;
const ll max_size = 200;
ll n, m;
ll g[max_size][max_size], pre_g[max_size][max_size], gL[max_size][max_size], gR[max_size][max_size];
ll par_soch[max_size];
bool used[max_size], usedL[max_size], usedR[max_size], par_sochL[max_size];

void ecxeption() {
    cout << 2 << endl;
    cout << 1 << " " << 1 << endl;
    cout << 1 << endl;
    cout << 1 << endl;
    while (true);
}

bool get_par_soch(ll v) {
//    if(v >= used.size()) {
//        ecxeption();
//    }
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (ll i = 0; i < m; i++) {
        ll to = g[v][i];
        if(to == 0) {
            continue;
        }
        if (par_soch[i] == -1 || get_par_soch(par_soch[i])) {
            par_soch[i] = v;
            return true;
        }
    }
    return false;
}

void dfs(ll u, bool right) {
    if(right) {
        if(usedR[u]) {
            return;
        }
        usedR[u] = true;
        for(ll i = 0; i < n; i++) {
            if(gR[u][i] == 0) {
                continue;
            }
            dfs(i, !right);
        }
    } else {
        if(usedL[u]) {
            return;
        }
        usedL[u] = true;
        for(ll i = 0; i < m; i++){
            if(gL[u][i] == 0) {
                continue;
            }
            dfs(i, !right);
        }
    }
}


int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ll k;
    cin >> k;
    for(ll l = 0; l < k; l++) {
        cin >> n >> m;
        for(ll i = 0; i < n; i++) {
            for(ll j = 0; j < m; j++) {
                pre_g[i][j] = 0;
                g[i][j] = 0;
                gL[i][j] = 0;
                gR[j][i] = 0;
            }
        }
        for(ll i = 0; i < m; i++) {
            par_soch[i] = -1;
        }
        for(ll i = 0; i < n; i++) {
            used[i] = false;
            usedL[i] = false;
            par_sochL[i] = false;
        }
        for(ll i = 0 ; i < m; i++) {
            usedR[i] = false;
        }
        ll v;
        for (ll i = 0; i < n; i++) {
            cin >> v;
            while(v != 0) {
                v--;
                pre_g[i][v] = 1;
                cin >> v;
            }
        }
        for(ll i = 0; i < n; i++) {
            for(ll j = 0; j < m; j++) {
                if(pre_g[i][j] == 0) {
                    g[i][j] = 1;
                }
            }
        }
        for (ll i = 0; i < n; i++) {
            for(ll j = 0; j < n; j++) {
                used[j] = false;
            }
            get_par_soch(i);
        }
        for(ll i = 0; i < m; i++) {
            if(par_soch[i] != -1) {
                par_sochL[par_soch[i]] = true;
            }
        }
        for(ll i = 0; i < n; i++) {
            for(ll j = 0; j < m; j++) {
                ll to = g[i][j];
                if(to == 0) {
                    continue;
                }
                if(par_soch[j] == i) {
                    gR[j][i] = 1;
                } else {
                    gL[i][j] = 1;
                }
            }
        }

        for(ll i = 0; i < n; i++) {
            if(!par_sochL[i]) {
                dfs(i, false);
            }
        }
        ll L = 0, R = 0;
        for(ll i = 0; i < n; i++) {
            if(usedL[i]) {
                L++;
            }
        }
        for (int i = 0; i < m; i++) {
            if(!usedR[i]) {
                R++;
            }
        }
        cout << L + R << endl;
        cout << L << " " << R << endl;
        for(ll i = 0; i < n; i++) {
            if(usedL[i]) {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
        for(ll i = 0; i < m; i++) {
            if(!usedR[i]) {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
    }
    return 0;
}