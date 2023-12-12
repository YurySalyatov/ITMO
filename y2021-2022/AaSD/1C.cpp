#include <cstring>
#include <iostream>

using namespace std;
typedef long long int lli;
class Node {
public:
    lli l;
    lli r;
    lli sum;
    lli color;
    lli flag;
    bool neew;
    Node() {
        l = 0;
        r = 0;
        sum = 0;
        sum = 0;
        color = 0;
        flag = -1;
        neew = true;
    }
};
void addnew(Node *segtree, lli v) {
    if(segtree[v].neew) {
        segtree[v] = Node();
        segtree[v].neew = false;
    }
}
void propogate(Node *segtree, lli v) {
    segtree[v].sum = segtree[2 * v + 1].sum + segtree[2 * v + 2].sum;
    segtree[v].color = segtree[2 * v + 1].color + segtree[2 * v + 2].color;
    segtree[v].l = segtree[2 * v + 1].l;
    segtree[v].r = segtree[2 * v + 2].r;
    if (segtree[2 * v + 1].r == segtree[2 * v + 2].l && segtree[2 * v + 2].l == 1) {
        segtree[v].color--;
    }
}
void change_value(Node *segtree, lli v, lli vl, lli vr, lli color) {
    segtree[v].l = segtree[v].r = segtree[v].color = segtree[v].flag = color;
    segtree[v].sum = (vr - vl) * color;
}
void push(Node *segtree, lli v, lli vl, lli vr) {
    lli vm = (vr + vl) / 2;
    addnew(segtree, 2 * v + 1);
    addnew(segtree, 2 * v + 2);
    if (segtree[v].flag != -1) {
        change_value(segtree, 2 * v + 1, vl, vm, segtree[v].color);
        change_value(segtree, 2 * v + 2, vm, vr, segtree[v].color);
        segtree[v].flag = -1;
    }
}
void set_color(Node *segtree, lli v, lli color, lli vl, lli vr, lli l, lli r) {
    if (l <= vl && vr <= r) {
        change_value(segtree, v, vl, vr, color);
        return;
    }
    if (l >= vr || vl >= r) {
        return;
    }
    push(segtree, v, vl, vr);
    lli vm = (vr + vl) / 2;
    set_color(segtree, 2 * v + 1, color, vl, vm, l, r);
    set_color(segtree, 2 * v + 2, color, vm, vr, l, r);
    propogate(segtree, v);
}
int main() {
    lli n;
    cin >> n;

    string clr;
    lli l, r;
    Node *segtree = (Node *) calloc(5000000, sizeof(Node));
    for (lli i = 0; i < 5000000; i++) {
        segtree[i] = Node();
    }
    for (lli i = 0; i < n; i++) {
        cin >> clr;
        cin >> l;
        cin >> r;
        r += l;
        lli color = 1;
        if (clr == "W")
            color = 0;
        set_color(segtree, 0, color, -500000, 500001, l, r);
        cout << segtree[0].color << " " << segtree[0].sum << "\n";
    }
    return 0;
}