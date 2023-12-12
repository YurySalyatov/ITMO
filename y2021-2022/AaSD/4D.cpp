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
    bool reverse;
    lli size;
    Node(lli a, lli rand) {
        l = nullptr;
        r = nullptr;
        x = a;
        reverse = false;
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
    friend void change(Node *node){
        if(!node) {
            return;
        }
        node->reverse = !node->reverse;
    }
    friend void push(Node *node) {
        if(!node) {
            return;
        }
        if(node->reverse){
            change(node->l);
            change(node->r);
            swap(node->l, node->r);
            node->reverse = false;
        }

    }
    friend void out(Node *tree) {
        if (tree == nullptr) {
            return;
        }
        push(tree);
        out(tree->l);
        cout << tree->x << " ";
        out(tree->r);
    }
    friend pair<Node *, Node *> split(Node *tree, lli val) {
        if (!tree) {
            pair<Node *, Node *>p1(nullptr, nullptr);
            return p1;
        }
        push(tree);
        if (get_size(tree->l) >= val) {
            pair<Node *, Node *> p1 = split(tree->l, val);
            tree->l = p1.second;
            resize(tree);
            return pair<Node *, Node *>{p1.first, tree};
        } else {
            pair<Node *, Node *> p1 = split(tree->r, val - 1 - get_size(tree->l));
            tree->r = p1.first;
            resize(tree);
            return pair<Node *, Node *>{tree, p1.second};
        }
    }
    friend lli get(Node *tree, lli val) {
        if(get_size(tree) - get_size(tree->r) == val) {
            return tree->x;
        } else if (val < (get_size(tree) - get_size(tree->r))) {
            return get(tree->l, val);
        } else {
            return get(tree->r, val - 1 - get_size(tree->l));
        }
    }
    friend Node *merge(Node *tree1, Node *tree2)
    {
        push(tree1);
        push(tree2);
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
    friend bool find(Node *tree, lli val) {
        if(!tree) {
            return false;
        }
        if(tree->x == val) {
            return true;
        } else if (tree->x > val) {
            return find(tree->l, val);
        } else {
            return find(tree->r, val);
        }
    }
    friend Node *insert(Node *tree, Node *node, lli val) {
        pair<Node *, Node *>p1 = split(tree, val);
        p1.first = merge(p1.first, node);
        return merge(p1.first, p1.second);
    }
    friend Node *rev(Node *tree, lli l, lli r) {
        pair<Node *, Node *>p1 = split(tree, l - 1);
        pair<Node *, Node *>p2 = split(p1.second, r - l + 1);
        change(p2.first);
        tree = merge(p1.first, p2.first);
        tree = merge(tree, p2.second);
        return tree;
    }

};

int main() {
    Node *tree = nullptr;
    lli n, m;
    cin >> n >> m;
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<lli> dist(1, 1 << 30);
    for(lli i = 1; i < n + 1; i++) {
        Node *a = new Node(i, dist(mt));
        tree = insert(tree, a, get_size(tree));
    }
    for(lli i = 0; i < m; i++) {
        lli l, r;
        cin >> l >> r;
        tree = rev(tree, l, r);
    }
    out(tree);
    return 0;
}