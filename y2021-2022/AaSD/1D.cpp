#include <iostream>
#include <cstring>
using namespace std;
typedef long long int lli;
class Node {
    lli add;
    lli set;
    lli mini;
    bool None;
    bool set_None;

public:
    Node() {
        add = 0;
        set = 0;
        mini = LONG_LONG_MAX;
        None = true;
        set_None = false;
    }
    Node(lli a, lli s, lli m) {
        add = a;
        set = s;
        mini = m;
        None = false;
        set_None = true;
    }
    lli get_add() const{
        return add;
    }
    lli get_set() const{
        return set;
    }
    lli get_mini() const{
        return mini;
    }
    bool get_None() const {
        return None;
    }
    void change_mini(lli v){
        mini = v;
    }
    void change_set(lli v){
        set = v;
    }
    void change_add(lli v){
        add = v;
    }
    void change_set_None(bool v) {
        set_None = v;
    }
   bool get_set_None() const {
       return set_None;
   }

};
void change_set(Node *segtree, lli x, lli v) {
        segtree[x].change_mini(v);
        segtree[x].change_set(v);
        segtree[x].change_add(0);
        segtree[x].change_set_None(true);
}

void change_add(Node *segtree, lli x, lli v){
        segtree[x].change_mini((segtree[x].get_mini() + v));
        segtree[x].change_add((segtree[x].get_add() + v));
}
void propogate(Node *segtree, lli x)
{
    if(segtree[x].get_set_None())
    {
        change_set(segtree, 2 * x, segtree[x].get_set());
        change_set(segtree, 2 * x + 1, segtree[x].get_set());
        segtree[x].change_set_None(false);
    }
    if(segtree[x].get_add())
    {
        change_add(segtree, 2 * x, segtree[x].get_add());
        change_add(segtree, 2 * x + 1, segtree[x].get_add());
        segtree[x].change_add(0);
    }
}
void make_set(Node *segtree, lli x, lli v, lli lx, lli rx, lli l, lli r)
{
    if (l <= lx && rx <= r)
    {
        change_set(segtree, x, v);
        return;
    }
    if (l >= rx || lx >= r)
    {
        return;
    }
    propogate(segtree, x);
    lli mx = (rx + lx) / 2;
    make_set(segtree, 2 * x, v, lx, mx, l, r);
    make_set(segtree, 2 * x + 1, v, mx, rx, l, r);
    segtree[x].change_mini(min(segtree[2 * x].get_mini(), segtree[2 * x + 1].get_mini()));
}
void make_add(Node *segtree, lli x, lli v, lli lx, lli rx, lli l, lli r){
    if (l <= lx && rx <= r)
    {
        change_add(segtree, x, v);
        return;
    }
    if (l >= rx || lx >= r)
    {
        return;
    }
    propogate(segtree, x);
    lli mx = (rx + lx) / 2;
    make_add(segtree, 2 * x, v, lx, mx, l, r);
    make_add(segtree, 2 * x + 1, v, mx, rx, l, r);
    segtree[x].change_mini(min(segtree[2 * x].get_mini(), segtree[2 * x + 1].get_mini()));
}

lli get_mini(Node *segtree, lli x, lli lx, lli rx, lli l, lli r) {
    if(l <= lx && rx <= r){
        return segtree[x].get_mini();
    }
    if(l >= rx || lx >= r)
    {
        return LONG_LONG_MAX;
    }
    propogate(segtree, x);
    lli mx = (rx + lx) / 2;
    lli y = 2 * x;
    lli z = y + 1;
    return min(get_mini(segtree, y, lx, mx, l, r), get_mini(segtree, z, mx, rx, l, r));
}

int main() {
    long long int n;
    cin >> n;
    lli sz = 1;
    while ( sz < n) {
        sz *= 2;
    }
    Node *segtree = (Node *) calloc(2 * sz, sizeof (Node));
    for (lli i = 0; i < 2 * sz; i++) {
        segtree[i] = Node();
    }
    lli a;

    for(lli i = 0; i < n; i++)
    {
        cin >> a;
        make_set(segtree, 1, a, 0, sz, i, i + 1);
    }
    string s;
    while (cin >> s) {
        lli l, r;
        cin >> l >> r;
        if(s == "min") {
            cout << get_mini(segtree, 1, 0, sz, l - 1, r) << "\n";
        }
        else {
            lli v;
            cin >> v;
            if (s == "add") {
                make_add(segtree, 1, v, 0, sz, l - 1, r);
            }
            if (s == "set") {
                make_set(segtree, 1, v, 0, sz, l - 1, r);
            }
        }
    }
    return 0;
}
