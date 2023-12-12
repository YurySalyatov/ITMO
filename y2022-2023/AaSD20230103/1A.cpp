#include "iostream"
#include "vector"
#include "algorithm"
#include "cmath"
#include "iomanip"
#include "string"
#include "cmath"

using namespace std;
typedef int long long ill;
string all;
ill mod = 1e9 + 7;
ill a = 1013;

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    ill n, m;
    cin >> n >> m;
    ill p[n];
    p[0] = 1;
    for (ill i = 1; i < n; i++) {
        p[i] = (p[i - 1] * a) % mod;
    }
    string s;
    for(ill i = 0; i < n; i++) {
        cin >> s[i];
    }
    ill hashLToR[n], hashRToL[n];
    hashLToR[0] = s[0] - '0';
    hashRToL[0] = s[n - 1] - '0';
    for (ill i = 1; i < n; i++) {
        hashLToR[i] = (hashLToR[i - 1] * a + s[i] - '0') % mod;
        hashRToL[i] = (hashRToL[i - 1] * a + s[n - i - 1] - '0') % mod;
    }
    for(ill i = 0; i < n; i++){
        cerr << hashLToR[i] << " ";
    }
    cerr << "\n";
    for(ill i = 0; i < n; i++){
        cerr << hashRToL[i] << " ";
    }
    cerr << "\n";
    for(ill i = n /2; i > 0; i--) {
        if(i * 2 == n) {
            ill hash0 = hashRToL[n - i - 1], hash1 = hashLToR[i - 1];
            if(hash0 == hash1) {
                cout << n - i << " ";
            }
        } else {
            ill c = n - i - 1, b = n - 2 * i - 1;
            ill hash0 = ((hashRToL[c] - hashRToL[b] * p[i - 1]) % mod + mod) % mod, hash1 = hashLToR[i - 1];
            if(hash1 == hash0) {
                cout << n - i << " ";
            }
        }

    }
    cout << n;
    return 0;
}