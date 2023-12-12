#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include <random>
using namespace std;
typedef long long int lli;

class Node {
public:
    Node *l;
    Node *r;
    lli x;
    lli y;
    lli size;
    Node(lli a, lli rand) {
        l = nullptr;
        r = nullptr;
        x = a;
        y = rand;
        size = 1;
    }
    friend lli get_size(Node *node) {
        if (!node) {
            return 0;
        }
        return node->size;
    }
    friend void resize(Node *node) {
        if (!node) {
            return;
        }
        node->size = get_size(node->l) + get_size(node->r) + 1;
    }
    friend pair<Node *, Node *> split(Node *tree, lli val) {
        if (!tree) {
            pair<Node *, Node *>p1(nullptr, nullptr);
            return p1;
        }
        if (tree->x >= val) {
            pair<Node *, Node *> p1 = split(tree->l, val);
            tree->l = p1.second;
            resize(tree);
            return pair<Node *, Node *>{p1.first, tree};
        } else {
            pair<Node *, Node *> p1 = split(tree->r, val);
            tree->r = p1.first;
            resize(tree);
            return pair<Node *, Node *>{tree, p1.second};
        }
    }
    friend lli get(Node *tree, lli val) {
        if(get_size(tree) - get_size(tree->l) == val) {
            return tree->x;
        } else if (val < get_size(tree) - get_size(tree->l)) {
            return get(tree->r, val);
        } else {
            return get(tree->l, val - get_size(tree->r) - 1);
        }
    }
    friend Node *merge(Node *tree1, Node *tree2)
    {
        if(!tree1) {
            return tree2;
        }
        if(!tree2) {
            return tree1;
        }
        if(tree1->y > tree2->y) {
            tree1->r = merge(tree1->r, tree2);
            resize(tree1);
            return tree1;
        }
        else {
            tree2->l = merge(tree1, tree2->l);
            resize(tree2);
            return tree2;
        }
    }
    friend Node *insert(Node *tree, Node *node) {
        if(!tree) {
            return node;
        }
        if(tree->y < node->y) {
            pair<Node *, Node *>p1 = split(tree, node->x);
            node->l = p1.first;
            node->r = p1.second;
            resize(node);
            return node;
        }
        if(node->x < tree-> x)
        {
            tree->l = insert(tree->l, node);
            resize(tree->l);
        }
        else
        {
            tree->r = insert(tree->r, node);
            resize(tree->r);
        }
        resize(tree);
        return tree;
    }
    friend Node *remove(Node *tree,  lli key) {
        if(tree->x == key) {
            tree = merge(tree->l, tree->r);
        } else if (key > tree->x) {
            tree->r = remove(tree->r, key);
        } else {
            tree->l = remove(tree->l, key);
        }
        resize(tree);
        return tree;
    }
};

int main() {
    Node *tree = nullptr;
    lli n;
    cin >> n;
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<lli> dist(1, 1 << 30);
    for(lli i = 0; i < n; i++) {
        lli l, r;
        cin >> l >> r;
        if(l == 1) {
            Node *a = new Node(r, dist(mt));
            tree = insert(tree, a);
        } else if (l == 0) {
            cout << get(tree, r) << "\n";
        } else {
            tree = remove(tree, r);
        }
    }
    return 0;
}