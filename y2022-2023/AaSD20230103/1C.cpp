#include "iostream"
#include "vector"
#include "algorithm"
#include "cmath"
#include "iomanip"
#include "string"
#include "cmath"

using namespace std;
typedef int long long ill;
string s;
ill n;
vector<ill> z;

void z_function() {
    for (ill i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> s;
    n = s.size();
    z.resize(n);
    z_function();
//    for(auto i : z) {
//        cerr << i << " ";
//    }
//    cerr << "\n";
    ill size = n;
    for(ill i = 1; i < n; i++) {
        if(n % i == 0) {
            if(i == 1 && z[1] != n - 1) {
                continue;
            }
            if(i + z[i] != n) {
                continue;
            }
            size = i;
            break;
        }
    }
    cout << size;
    return 0;
}