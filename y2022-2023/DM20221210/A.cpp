#include <algorithm>
#include "iostream"
#include "vector"

using namespace std;


typedef int long long ill;
ill n;

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    freopen("schedule.in", "r", stdin);
    freopen("schedule.out", "w", stdout);

    cin >> n;
    pair<ill, ill> arr[n];
    ill max = 0;
    ill sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> arr[i].first >> arr[i].second;
        max = std::max(max, arr[i].first);
    }
    bool ans[max];
    for (ill i = 0; i < max; i++) {
        ans[i] = false;
    }
    sort(arr, arr + n, [](pair<ill, ill> a, pair<ill, ill> b) { return a.second > b.second; });
    for (ill i = 0; i < n; i++) {
        ill pos = arr[i].first - 1;
        while (pos >= 0 && ans[pos]) {
            --pos;
        }
        if (pos < 0) {
            sum += arr[i].second;
        } else {
            ans[pos] = true;
        }
    }
    cout << sum << "\n";
    return 0;
}