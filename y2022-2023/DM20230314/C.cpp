#include "iostream"
using namespace std;

int main () {
    long long k;
    cin >> k;
    long long c[k], a[k];
    for(long long i = 0; i < k; i++) {
        cin >> a[i];
    }
    for(long long i = 0; i < k; i++) {
        cin >> c[i];
    }
    long long q[k + 1], p[k];
    fill_n(p, k + 1, 0);
    q[0] = 1;
    long long degq = k + 1;
    for(long long i = 1; i < k + 1; i++) {
        q[i] = -c[i - 1];
    }
    long long deg = 0;
    for(long long i = 0; i < k; i++) {
        for(long long j = 0; j < k; j++) {
            if(i + j < k) {
                p[i + j] += q[j] * a[i];
            }
        }
    }
    for(long long i = 0; i < k; i++) {
        if(p[i] != 0) {
            deg = i;
        }
    }
    cout << deg << endl;
    for (long long i = 0; i < deg + 1; i++) {
        cout << p[i] << " ";
    }
    cout << endl << k << endl;
    for (long long i = 0; i < k + 1; i++) {
        cout << q[i] << " ";
    }
    return 0;
}