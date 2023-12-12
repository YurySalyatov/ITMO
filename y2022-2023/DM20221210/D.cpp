#include "iostream"
#include "cmath"
#include "set"

using namespace std;


typedef unsigned int long long ill;
ill n, m;
set<ill>has;
bool first() {
    return (has.find(0) != has.end());
}
bool second() {
    for(ill i : has) {
        for(ill j = 0; j < (1 << n); ++j) {
            if(((i & j) == j) && has.find(j) == has.end()) {
                return false;
            }
        }
    }
    return true;
}
int len(ill k) {
    int c = 0;
    while (k > 0) {
        if(k % 2 != 0) {
            c++;
        }
        k >>= 1;
    }
    return c;
}
bool third() {
    for(ill i : has) {
        for(ill j : has) {
            if(len(i) > len(j)) {
                bool has_one = false;
                for (int t = 0; t < n; t++) {
                    if ((i & (1 << t)) && !(j & (1 << t))) {
                        if (has.find(j | (1 << t)) != has.end()) {
                            has_one = true;
                            break;
                        }
                    }
                }
                if(!has_one) {
                    return false;
                }
            }
        }
    }
    return true;
}
int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    freopen("check.in", "r", stdin);
    freopen("check.out", "w", stdout);
    cin >> n >> m;
    for(ill i = 0; i < m; ++i) {
        ill count, a, k = 0;
        cin >> count;
        for(ill j = 0; j < count; ++j) {
            cin >> a;
            a--;
            k |= (1 << a);
        }
        has.insert(k);
    }
    if(first() && second() && third()) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}