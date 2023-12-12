#include <iostream>
#include <vector>
#include <ostream>
#include <bits\stdc++.h>
using namespace std;


typedef int long long ll;
const ll max_size = 200;
ll n, m;
ll g[max_size][max_size], gL[max_size][max_size], gR[max_size][max_size];
ll par_soch[max_size];
bool used[max_size], usedL[max_size], usedR[max_size], par_sochL[max_size];

bool get_par_soch(ll v) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (ll i = 0; i < n; i++) {
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
        for(ll i = 0; i < n; i++){
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
    ifstream fin("hobbits.in");
    ofstream fout("hobbits.out");
    fin >> n;
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            fin >> g[i][j];
        }
    }
    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < n; j++) {
            gL[i][j] = 0;
            gR[i][j] = 0;
        }
    }
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            for (ll k = 0; k < n; k++) {
                if (g[i][k] && g[k][j]) {
                    g[i][j] = 1;
                }
            }
        }
    }
    for(ll i = 0; i < n; i++) {
        par_soch[i] = -1;
        par_sochL[i] = false;
        usedR[i] = false;
        usedL[i] = false;
    }
    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < n; j++) {
            used[j] = false;
        }
        get_par_soch(i);
    }
//    for(ll i = 0; i < n; i++) {
//        cout << i + 1 << " " << par_soch[i] + 1 << endl;
//    }
//    cout << endl;
    for(ll i = 0; i < n; i++) {
        for(ll j = 0; j < n; j++) {
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
        if(par_soch[i] != -1) {
            par_sochL[par_soch[i]] = true;
        }
    }
    for(ll i = 0; i < n; i++) {
        if(!par_sochL[i]) {
            dfs(i, false);
        }
    }
    ll count = 0;
    for(ll i = 0; i < n; i++) {
        if(usedL[i] && !usedR[i]) {
            count++;
        }
    }
    fout << count << endl;
    for(ll i = 0; i < n; i++) {
        if(usedL[i] && !usedR[i]) {
            fout << i + 1 << " ";
        }
    }
    fout << endl;
    fin.close();
    fout.close();
    return 0;
}