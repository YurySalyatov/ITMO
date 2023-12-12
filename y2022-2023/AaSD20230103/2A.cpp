#include <bits/stdc++.h>
#include "set"
using namespace std;

const int N = 1e6 + 1000;

int bor[N][40];
int pred[N];
int suf[N];
int used[N];
int par[N];
int m = 0;
set<int> p;
queue<int> q;

void build_koras(string s, int ind) {
    int v = 0;

    for (char i: s) {
        int c = i - 'a';
        if (!bor[v][c]) {
            bor[v][c] = ++m, pred[m] = v;
        }
        v = bor[v][c];
    }
    par[ind] = v;
}

int get_link(int v, int c) {
    int k = pred[v];
    k = suf[k];

    while (k != 0 && !bor[k][c]) {
        k = suf[k];
    }

    if (bor[k][c] == v) {
        return 0;
    } else {
        return bor[k][c];
    }
}

void rev_dfs() {
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        int cnt = used[x];
        if(p.find(x) == p.end()) {
            continue;
        }
        p.erase(x);
        while (suf[x]) {
            x = suf[x];
            used[x] += cnt;
            if (p.find(x) != p.end()) {
                break;
            }
        }
    }
}

void bfs() {
    q.push(0);

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        for (int i = 0; i < 30; i++) {
            int to = bor[x][i];
            if (to) {
                suf[to] = get_link(to, i), q.push(to);
            }
        }
    }

}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    int n;
    cin >> n;
    string s1;
    for (int i = 0; i < n; i++) {
        cin >> s1;
        build_koras(s1, i);
    }
    cin >> s;
    bfs();
    int v = 0;
    for (char i: s) {
        int c = i - 'a';
        if (bor[v][c]) {
            v = bor[v][c];
        } else {
            while (v && !bor[v][c]) {
                v = suf[v];
            }
            v = bor[v][c];
        }
        used[v]++;
        q.push(v);
        p.insert(v);
    }
    rev_dfs();

    for (int i = 0; i < n; i++) {
        cout << used[par[i]] << "\n";
    }
    return 0;
}