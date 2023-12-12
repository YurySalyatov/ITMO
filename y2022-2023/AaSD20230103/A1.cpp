#include "iostream"
#include "string"


using namespace std;
typedef int long long ill;
ill used[100][100];
string mass[100];
ill n,m;
void dfs4(ill i, ill j) {
//  cout << i << " " << j << "\n";
  used[i][j] = 1;
  if(i > 0 && used[i - 1][j] == 0) {
    dfs4(i - 1, j);
  }
  if(j < n - 1 && used[i][j + 1] == 0) {
    dfs4(i, j + 1);
  }
  if(j > 0 && used[i][j -1] == 0) {
    dfs4(i, j - 1);
  }
  if(i < m - 1 && used[i + 1][j] == 0) {
    dfs4(i + 1, j);
  }
}
int main() {
  cin >> m >> n;
  for(ill i = 0; i < m; i++) {
    for (ill j = 0; j < n; j++) {
      used[i][j] = 0;
    }
  }
  for (ill i = 0; i < m; i++) {
    cin >> mass[i];
    for (ill j = 0; j < n; j++) {
      if(mass[i][j] == '.') {
        used[i][j] = 1;
      }
    }
  }
//  for(ill i = 0; i < m; i++) {
//    for (ill j = 0; j < n; j++) {
//      cout << used[i][j];
//    }
//    cout << "\n";
//  }
  ill cnt = 0;
  for (ill i = 0; i < m; i++) {
    for (ill j = 0; j < n; j++) {
      if(used[i][j] != 1) {
        cnt++;
        dfs4(i, j);
//        cout << "end one dfs" << "\n";
      }
    }
  }
  cout << cnt;
  return 0;
}