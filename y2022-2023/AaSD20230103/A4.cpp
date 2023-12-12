#include "iostream"
#include "vector"
#include "algorithm"
#include "cmath"
#include "iomanip"
using namespace std;
typedef int long long ill;


ill n;
double INF = 10000000000;
vector<pair<double, double>> graf;
vector<double> dst;
vector<bool>used;
double dist(pair<double, double> a, pair<double, double> b) {
    return sqrt(pow(abs(a.first - b.first), 2) + pow(abs(a.second - b.second), 2));
}

int main() {

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    double a, b;
    used.resize(n);
    dst.resize(n);
    fill(used.begin(), used.end(), false);
    for(ill i = 0; i < n; i++) {
        cin >> a >> b;
        graf.push_back(make_pair(a, b));
        dst[i] = INF;
    }
    dst[0] = 0;
    for(ill i = 0; i < n; i++) {
        ill v = -1;
        for(ill j = 0; j < n; j++) {
            if(!used[j] && (v == -1 || dst[j] < dst[v])) {
                v = j;
            }
        }
        used[v] = true;
        for(ill j = 0; j < n; j++) {
            if(!used[j]) {
                dst[j] = min(dst[j], dist(graf[j], graf[v]));
            }
        }
    }
    double sum = 0;
    for(ill i = 1; i < n; i++) {
        sum += dst[i];
    }
    cout << fixed << setprecision(9) << sum << "\n";
    return 0;
}