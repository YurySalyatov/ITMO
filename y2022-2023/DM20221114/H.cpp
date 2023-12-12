#include "vector"
#include "iostream"
#include "string"
#include "set"
#include "iterator"
int n, m;
using namespace std;

int* subtract(int* a, const int* b) {

  for(int i = 0; i < n + 1; i++) {
    a[i]-= b[i];
  }
  return a;
}

int* Hrom(const set<pair<int, int>>&G, int k) {
  if(G.empty()) {
    int* a = (int*)calloc(sizeof (int), n + 1);
    for(int i = 0; i < n + 1; i++) {
      a[i] = 0;
    }
    a[k] = 1;
    return a;
  }
  set<pair<int, int>> G1 = G;
  pair<int, int> a;
  for(pair<int, int> i: G1) {
    a = i;
  }
  G1.erase(a);
  set<pair<int, int>> G2;
  for(pair<int, int> i : G1) {
    pair<int, int> b = i;
    if (b.first == a.second) {
      b.first = a.first;
    }
    if(b.second == a.second) {
      b.second = a.first;
    }
    if(b.second < b.first) {
      swap(b.first, b.second);
    }
    G2.insert(b);
  }
  return subtract(Hrom(G1, k), Hrom(G2, k - 1));
}

int main() {
  cin >> n >> m;

  int a, b;
  set<pair<int, int>>G;
  for(int i = 0; i < m; i++) {
    cin >> a >> b;
    if(a < b) {
      G.insert(pair<int, int>(a, b));
    } else {
      G.insert(pair<int, int>(b, a));
    }

  }
  int* c = Hrom(G, n);
  cout << n << "\n";
  for(int i = n; i >= 0; i--) {
    cout << c[i] << " ";
  }
  return 0;
}
