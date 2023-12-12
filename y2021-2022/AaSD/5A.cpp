#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include <random>
using namespace std;
typedef long long int lli;
typedef unsigned long long int ulli;
vector<ulli> tree, height, iuler_ture, a;
vector<vector<ulli>> parents;
ulli d_size, sz;

ulli min_in_h(ulli u, ulli v) {
    if (height[v] < height[u]) {
        return v;
    }
    return u;
}

ulli mini(ulli x, ulli lx, ulli rx, ulli l, ulli r) {
    if(l <= lx && rx <= r) {
        return tree[x];
    }
    if(r <= lx || rx <= l) {
        return 0;
    }
    ulli mx = (lx + rx) / 2;
    ulli res1 = mini(2 * x + 1, lx, mx, l, r);
    ulli res2 = mini(2 * x + 2, mx, rx, l, r);
    return min_in_h(res1, res2);
}
void build_tree(ulli x, ulli l, ulli r) {
    if(r - l == 1) {
        if(l < d_size) {
            tree[x] = iuler_ture[l];
        }
        return;
    }
    ulli mx = (l + r) / 2;
    build_tree(2 * x + 1, l, mx);
    build_tree(2 * x + 2, mx, r);
    tree[x] = min_in_h(tree[2 * x + 1], tree[2 * x + 2]);
}

void dfs(ulli u, ulli hei = 1) {
    height[u] = hei;
    iuler_ture.push_back(u);
    for (ulli i = 0; i < parents[u].size(); i++) {
        dfs(parents[u][i], hei + 1);
        iuler_ture.push_back(u);
    }
}
ulli lca(ulli u, ulli v) {
    ulli t1 = a[u];
    ulli t2 = a[v];
    if(t2 < t1) {
        swap(t1, t2);
    }
    return mini(0, 0, sz, t1, t2 + 1);
}

int main() {
    ulli n;
    cin >> n;
    for(ulli i = 0; i < n + 1; i++) {
        auto *abc = new vector<ulli>;
        parents.push_back(*abc);
    }
    for(ulli i = 2; i < n + 1; i++) {
        ulli x;
        cin >> x;
        parents[x].push_back(i);
    }
    for (ulli i = 0; i <= n + 1; i++) {
        height.push_back(0);
        a.push_back(-1);
    }
    dfs(1);
    d_size = iuler_ture.size();
    for(ulli i = 0; i < d_size; i++) {
        if(a[iuler_ture[i]] == -1) {
            a[iuler_ture[i]] = i;
        }
    }
    height[0] = 1000000000;
    sz = 1;
    while (sz < d_size) {
        sz *= 2;
    }
    for(ulli i = 0; i < 2 * sz - 1; i++) {
        tree.push_back(0);
    }
    build_tree(0, 0, sz);
    ulli count;
    cin >> count;
    for(ulli i = 0; i < count; i++) {
        ulli u, v;
        cin >> u >> v;
        cout << lca(u, v) << "\n";
    }
}