#include "iostream"
#include "vector"
#include "algorithm"
#include "cmath"
#include "iomanip"
#include "string"
#include "cmath"

using namespace std;
typedef int long long ill;
string p, t, all;
ill n, m;
vector<ill> z;

void z_function() {
    for (ill i = 1, l = 0, r = 0; i < m + 1 + n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < m + 1 + n && all[z[i]] == all[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }
}

int main() {
    cin >> p >> t;
    all = p + '#' + t;
    n = t.size();
    m = p.size();
    z.resize(m + 1 + n);
    z_function();
    vector<ill> ans;
//    cerr << all << "\n";
//    for(auto i : z) {
//        cerr << i << " ";
//    }
//    cout << "\n";
    for(ill i = m + 1; i < m + 1 + n; i++) {
        if(z[i] == m) {
            ans.push_back(i - m);
        }
    }
    cout << ans.size() << "\n";
    for(ill i : ans) {
        cout << i << " ";
    }
    return 0;
}