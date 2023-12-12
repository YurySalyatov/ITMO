#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iostream>

const int SIZE = 7;
std::string input;

using namespace std;
typedef long long ll;
string for_parse;
ll now = 0;
int success = 1;
ll *parse() {
    if (for_parse[now] == 'B') {
        ++now;
        ll *p = new ll[7];
        fill_n(p, 7, 0);
        p[1] = 1;
        return p;
    } else if (for_parse[now] == 'P') {
        ++now;
        ++now;
        ll *p1 = parse();
        ++now;
        ll *p2 = parse();
        ++now;
        ll *ans = new ll[7];
        fill_n(ans, 7, 0);
        for (ll i = 0; i < 7; i++) {
            for (ll j = 0; j < 7; j++) {
                if (i + j < 7) {
                    ans[i + j] += p1[i] * p2[j];
                }
            }
        }
        return ans;
    } else if (for_parse[now] == 'L') {
        ++now;
        ++now;
        ll *p = parse();
        ++now;
        ll *ans = new ll[7];
        fill_n(ans, 7, 0);
        for (ll i = 0; i < 7; i++) {
            ans[i] = (i == 0 ? 1 : 0);
            for (ll j = 0; j < i; j++) {
                ans[i] += p[i - j] * ans[j];
            }
        }
        return ans;
    } else if (for_parse[now] == 'S') {
        ++now;
        ++now;
        ll *p = parse();
        ++now;
        ll *ans = new ll[7];
        fill_n(ans, 7, 0);
        ll *q = new ll[7];
        q[0] = 1;
        q[1] = -p[1];
        q[2] = (p[1] * (p[1] - 1)) / 2 - p[2];
        q[3] = p[1] * p[2] - p[3] - (p[1] * (p[1] - 1) * (p[1] - 2)) / (2 * 3);
        q[4] = (p[2] * (p[2] - 1)) / 2 - p[4] + p[1] * p[3] - p[2] * (p[1] * (p[1] - 1)) / 2 +
               (p[1] * (p[1] - 1) * (p[1] - 2) * (p[1] - 3)) / (2 * 3 * 4);
        q[5] = p[2] * p[3] - p[5] + p[4] * p[1] - (p[2] * (p[2] - 1)) / 2 * p[1] - (p[1] * (p[1] - 1)) / 2 * p[3] +
               (p[1] * (p[1] - 1) * (p[1] - 2)) / (2 * 3) * p[2] -
               (p[1] * (p[1] - 1) * (p[1] - 2) * (p[1] - 3) * (p[1] - 4)) / (2 * 3 * 4 * 5);
        q[6] = p[5] * p[1] - p[1] * p[2] * p[3] + (p[1] * (p[1] - 1)) / 2 * (p[2] * (p[2] - 1)) / 2 -
               (p[1] * (p[1] - 1)) / 2 * p[4] +
               (p[1] * (p[1] - 1) * (p[1] - 2)) / (2 * 3) * p[3] -
               (p[1] * (p[1] - 1) * (p[1] - 2) * (p[1] - 3)) / (2 * 3 * 4) * p[2] +
               (p[1] * (p[1] - 1) * (p[1] - 2) * (p[1] - 3) * (p[1] - 4) * (p[1] - 5)) / (2 * 3 * 4 * 5 * 6) +
               (p[3] * (p[3] - 1)) / 2 -
               p[6] - (p[2] * (p[2] - 1) * (p[2] - 2)) / (2 * 3) + p[2] * p[4];
        for (ll i = 0; i < 7; i++) {
            ans[i] = (i == 0 ? 1 : 0);
            for (ll j = 0; j < i; j++) {
                ans[i] -= q[i - j] * ans[j];
            }
        }
        return ans;
    }
    ll *ret = new ll[7];
    fill_n(ret, 7, 0);
    return ret;
}

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

long long coef(long long n, long long k) {
    long long res = 1;
    for (long long i = n - k + 1; i <= n; ++i) {
        res *= i;
    }
    for (long long j = 2; j <= k; ++j) {
        res /= j;
    }
    return res;
}

size_t pos = 0;

std::vector<long long> parseObject() {
    std::vector<long long> left, right;
    std::vector<long long> result(SIZE);

    char current = input[pos];

    switch (current) {
        case 'B': {
            for (int i = 0; i < result.size(); ++i) {
                if (i != 1) {
                    result[i] = 0;
                } else {
                    result[i] = 1;
                }
            }
            pos++;
            break;
        }
        case 'L': {
            pos += 2;
            left = parseObject();
            pos++;
            result[0] = 1;

            for (int i = 1; i < SIZE; ++i) {
                long long sum = 0;
                for (int j = 1; j <= i; ++j) {
                    sum += left[j] * result[i - j];
                }
                result[i] = sum;
            }
            break;
        }
        case 'S': {
            pos += 2;
            left = parseObject();
            pos++;

            std::vector<std::vector<long long>> matrix(SIZE, std::vector<long long>(SIZE));
            matrix[0][0] = 1;

            for (int i = 1; i < matrix.size(); i++) {
                matrix[0][i] = 1;
                matrix[i][0] = 0;
            }

            result[0] = 1;
            for (int i = 1; i < SIZE; ++i) {
                for (int j = 1; j < SIZE; ++j) {
                    long long sum = 0;
                    for (int k = 0; k <= i / j; ++k) {
                        long long maxx = std::max(left[j] + k - 1, 0LL);
                        sum += coef(maxx, k) * matrix[i - k * j][j - 1];
                    }
                    matrix[i][j] = sum;
                }
                result[i] = matrix[i][i];
            }

            break;
        }

        case 'C': {
            pos += 2;
            left = parseObject();
            pos++;

            std::vector<std::vector<long long>> c(SIZE, std::vector<long long>(SIZE));
            for (int i = 0; i < SIZE; ++i) {
                c[i][1] = left[i];
                c[i][0] = 0;
                c[0][i] = 0;
            }

            for (int i = 1; i < SIZE; ++i) {
                for (int j = 2; j < SIZE; ++j) {
                    long long sum = 0;
                    for (int k = 1; k < i; ++k) {
                        sum += left[k] * c[i - k][j - 1];
                    }
                    c[i][j] = sum;
                }
            }

            result[0] = 0;

            for (int i = 1; i < SIZE; ++i) {
                long long sum = 0;
                for (int j = 1; j <= i; ++j) {
                    long long push = 0;
                    for (int k = 0; k <= j - 1; ++k) {
                        int g = gcd(j, k);
                        long long s = (i % (j / g)) != 0 ? 0 : c[(i * g) / j][g];
                        push += s;
                    }
                    sum += push / j;
                }
                result[i] = sum;
            }
            break;
        }
        case 'P': {
            pos += 2;
            left = parseObject();
            pos++;
            right = parseObject();
            pos++;
            for (int i = 0; i < SIZE; ++i) {
                long long sum = 0;
                for (int j = 0; j <= i; ++j) {
                    sum += left[j] * right[i - j];
                }

                result[i] = sum;
            }
            break;
        }
        default:
            break;
    }

    return result;
}

ll randint(ll s, ll e) {
    ll ran = s + rand() % (e - s + 1);
    return ran;
}
void match(string c) {
    input = c;
    for_parse = c;
    pos = 0;
    now = 0;
    std::vector<long long> result = parseObject();
    for (long long i: result) {
        std::cout << i << " ";
    }
    cout << endl;
    ll* ans = parse();
    for(ll i = 0; i < SIZE; i++) {
        cout << ans[i] << " ";
    }
    cout << endl;
    for(ll i = 0; i < SIZE; i++) {
        if(result[i] != ans[i]) {
            success = 0;
            cout  << endl << "Eblan here" << endl;
            break;
        }
    }
}
string generate(ll leng) {
    if (leng == 0) {
        cout << "B" << endl;
        match("B");
        return "B";
    }
    ll i = randint(0, 2);
    if (i == 0) {
        string c = "S(" + generate(leng - 1) + ")";
        cout << c << endl;
        match(c);
        return c;
    }
    if (i == 1) {
        string c = "L(" + generate(leng - 1) + ")";
        cout << c << endl;
        match(c);
        return c;
    }
    if (i == 2) {
        ll k = randint(0, leng);
        string c = "P(" + generate(k) + "," + generate(leng - k) + ")";
        cout << c << endl;
        match(c);
        return c;
    }
    return "";
}

int main() {
    std::srand(std::time(nullptr));
//    std::getline(std::cin, input);
    ll k = 30;
    string test = generate(k);
    if(!success) {
        cout << "LOOOOOOOOOOL" << endl;
    }

    return 0;
}