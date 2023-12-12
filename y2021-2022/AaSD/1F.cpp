#include <cmath>
#include <cstring>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
typedef long long int lli;

class Node {
public:
    lli set;
    lli add;
    lli maxx;
    Node() {
        add = 0;
        set = LONG_LONG_MAX;
        maxx = 0;
    }
};

Node *tree;

void addnew(lli v, lli l, lli r) {
    if (tree[v].set == LONG_LONG_MAX) {
        return;
    }
    tree[v].add = tree[v].set * (r - l + 1);
    tree[v].maxx = tree[v].add;
    if (l != r) {
        tree[2 * v].set = tree[v].set;
        tree[2 * v + 1].set = tree[v].set;
    }
    tree[v].set = LONG_LONG_MAX;
}

void sett(lli v, lli l, lli r, lli lx, lli rx, lli set) {
    if (l <= lx && rx <= r) {
        tree[v].set = set;
        addnew(v, lx, rx);
        return;
    }
    if (lx >= r || l >= rx) {
        return;
    }
    addnew(v, lx, rx);
    lli mx = lx + (rx - lx) / 2;

    sett(2 * v, l, r, lx, mx, set);
    sett(2 * v + 1, l, r, mx + 1, rx, set);

    tree[v].maxx = max(tree[2 * v].maxx, tree[2 * v + 1].maxx + tree[2 * v].add);
    tree[v].add = tree[2 * v].add + tree[2 * v + 1].add;
}

lli gett(lli v, lli l, lli r, lli h) {
    addnew(v, l, r);

    if (l == r) {
        return r;
    }

    lli m = l + (r - l) / 2;
    addnew(2 * v, l, m);

    if (tree[2 * v].maxx <= h) {
        addnew(2 * v + 1, m + 1, r);
        h -= tree[2 * v].add;
        return gett(2 * v + 1, m + 1, r, h);
    } else {
        return gett(2 * v, l, m, h);
    }
}

int main() {
    lli n;
    char ch;
    cin >> n;
    lli sz = 1;
    while (sz < n) {
        sz *= 2;
    }
    tree = (Node *) calloc(2 * sz, sizeof(Node));
    for (lli i = 0; i < 2 * sz; i++) {
        tree[i] = Node();
    }
    while (true) {
        cin >> ch;
        if (ch == 'E')
            break;
        if (ch == 'I') {
            lli a, b, settt;
            cin >> a >> b >> settt;
            sett(1, a - 1, b - 1, 0, sz, settt);
        }
        if (ch == 'Q') {
            lli h;
            cin >> h;
            cout << gett(1, 0, sz, h) << "\n";
        }
    }
    //    free(tree);
    return 0;
}