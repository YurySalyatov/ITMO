#include "iostream"
#include "string"
#include "vector"
#include "set"
int n;
using namespace std;

int main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  set<pair<int, int>> G;
  int matriix[n][n];
  int degv[n];
  for(int i = 0; i < n; i++) {
    degv[i] = 0;
  }
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    degv[a - 1]++;
    degv[b - 1]++;
    G.insert(pair<int, int>(a, b));
  }
  set<int> degv1;
  for(int i = 1; i <= n; i++) {
    if(degv[i - 1] == 1) {
      degv1.insert(i);
    }
  }
  int k = n;
  vector<int> P;
  while (k > 2) {
    int v, u;
    for(int i : degv1) {
      v = i;
      break;
    }
    for(pair<int,int>i : G) {
      if(i.first == v) {
        degv[i.second-1]--;
        if(degv[i.second - 1] == 1) {
          degv1.insert(i.second);
        }
        G.erase(i);
        u = i.second;
        break;
      }
      if(i.second == v) {
        degv[i.first-1]--;
        if(degv[i.first - 1] == 1) {
          degv1.insert(i.first);
        }
        G.erase(i);
        u = i.first;
        break;
      }
    }
    P.push_back(u);
    degv1.erase(v);
    k--;
  }
  for(int i : P) {
    cout << i << " ";
  }
  return 0;
}
