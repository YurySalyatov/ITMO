#include "deque"
#include "iostream"
#include "string"
#include "vector"
using namespace std;

int main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  deque<int> path;
  int n;
  cin >> n;
  int matrix[n][n];
  for (int i = 1; i < n; i++) {
    string now;
    cin >> now;
    for (int j = 0; j < now.size(); j++) {
      matrix[i][j] = (int)(now[j] - '0');
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (i == j) {
        matrix[i][j] = 0;
      } else {
        matrix[i][j] = matrix[j][i];
      }
    }
  }

  for (int i = 0; i < n; i++) {
    path.push_back(i);
  }
  for (int i = 0; i <= n * (n - 1); i++) {
    if (!matrix[path.at(0)][path.at(1)]) {
      int cnt = 2;
      while (!matrix[path.at(0)][path.at(cnt)] ||
             !matrix[path.at(1)][path.at(cnt + 1)]) {
        cnt++;
      }
      for (int j = 1; j <= cnt - j + 1; j++) {
        swap(path.at(j), path.at(cnt - j + 1));
      }
    }
    path.push_back(path.front());
    path.erase(path.begin());
  }
  for (int i : path) {
    cout << i + 1 << " ";
  }
  return 0;
}