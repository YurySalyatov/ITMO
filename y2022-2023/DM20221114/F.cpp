#include "iostream"
#include "string"
#include "vector"
#include "set"
#include "deque"
int n, m;
using namespace std;

int main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  deque<int> P;
  int degv[n];
  for(int i = 0; i < n; i++) {
    degv[i] = 0;
  }
  set <int>degv0;
  for (int i = 0; i < n - 2; i++) {
    int b;
    cin >> b;
    degv[b - 1]++;
    P.push_back(b);
  }
  for(int i = 1; i <= n; i++) {
    if(degv[i - 1] == 0) {
      degv0.insert(i);
    }
  }
  set<pair<int, int>> G;
  while (!P.empty()) {
    int u = P.at(0);
    int v;
    for(int i : degv0) {
      v = i;
      break;
    }
    G.insert(pair<int, int>(u, v));
    P.erase(P.begin());
    degv0.erase(v);
    degv[u - 1]--;
    if(degv[u - 1] == 0) {
      degv0.insert(u);
    }
  }
  int v0, v1;
  for(int i : degv0) {
    v0 = i;
    break;
  }
  degv0.erase(v0);
  for(int i : degv0) {
    v1 = i;
    break;
  }
  G.insert(pair<int, int>(v0, v1));
  for(pair<int, int>i : G) {
    cout << i.first << " " << i.second << "\n";
  }
  return 0;
}
