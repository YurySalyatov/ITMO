#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
typedef long long int lli;
vector<vector<lli>> parse_table;
vector<lli> log_table;
lli answer(lli l, lli r) {
    lli k = log_table[r - l + 1];
    return min(parse_table[l][k], parse_table[r - (1 << k) + 1][k]);
}

int main() {
    lli n, m, a1, u, v;
    cin >> n >> m >> a1 >> u >> v;
    for (lli i = 0; i < n; i++) {
        vector<lli> parse_table_i;
        for (lli j = 0; j < (int) log2l(n) + 2; j++) {
            parse_table_i.push_back(0);
        }
        parse_table.push_back(parse_table_i);
    }
    for (lli i = 0; i < n + 1; i++) {
        log_table.push_back(0);
    }
    for (lli i = 2; i < n + 1; i++) {
        log_table[i] = log_table[i / 2] + 1;
    }
    lli *a = new lli[n];
    a[0] = a1;
    for (lli i = 1; i < n; i++) {
        a[i] = (23 * a[i - 1] + 21563) % 16714589;
    }
    for (lli i = 0; i < n; i++) {
        parse_table[i][0] = a[i];
    }
    int j = 1;
    while ((1 << j) <= n) {
        for (lli i = 0; i < n - (1 << j) + 1; i++) {
            parse_table[i][j] = min(parse_table[i][j - 1], parse_table[i + (1 << (j - 1))][j - 1]);
        }
        j++;
    }
    lli r = answer(min(u - 1, v - 1), max(u - 1, v - 1));
    for (lli i = 1; i < m + 1; i++) {
        if (i == m) {
            cout << u << " " << v << " " << r << "\n";
        }
        u = ((17 * u + 751 + r + 2 * i) % n) + 1;
        v = ((13 * v + 593 + r + 5 * i) % n) + 1;
        r = answer(min(u - 1, v - 1), max(u - 1, v - 1));
    }
    return 0;
}
