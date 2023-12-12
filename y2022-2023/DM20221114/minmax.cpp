#include "iostream"
#include "set"
#include "string"
#include "vector"
int n;
using namespace std;
typedef int long long lli;

int main() {

  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  vector<lli> vec;
  lli a;
  lli count = 0;
  for (int i = 0; i < n; i++) {
    cin >> a;
    vec.push_back(a);
  }
  multiset<lli> set;
  for(int i = 2; i <= n; i++) {
    set.clear();
    for(int j = 0; j < i; j++) {
      set.insert(vec[j]);
    }
    lli min;
    lli max;
    for (int j = 0; j < n - i; j++) {
      min = *set.begin();
      max = *(--set.end());
      count += (max - min);
      set.erase(set.find(vec[j]));
      set.insert(vec[j + i]);
    }
    min = *set.begin();
    max = *(--set.end());
    count += (max - min);
  }
  cout << "\n" << count;
  return 0;
}