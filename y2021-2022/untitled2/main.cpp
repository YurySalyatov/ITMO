#include <iostream>

using namespace std;
void makeSumDO(long long *array, long long len)
{
    for (long long  i = len / 2 - 1; i > 0; i--)
    {
        array[i] = array[2 * i] + array[2 * i + 1];
    }
}

long long  sum_r_l(long long *array, long long l, long long r, long long vl, long long vr, long long v)
{
    if (vl >= r || vr <= l)
    {
        return 0;
    }
    if (l <= vl && vr <= r)
    {
        return array[v];
    }
    long long  vm = (vr + vl) / 2;
    return (sum_r_l(&array[0], l, r, vl, vm, 2 * v) + sum_r_l(&array[0], l, r, vm, vr, 2 * v + 1));
}
void set_and_change(long long  *array, long long  len, long long  value, long long  pos)
{
    long long  v = pos + (len / 2);
    array[v] = value;
    v /= 2;
    while(v != 0)
    {
        array[v] = array[2 * v] + array[ 2 * v + 1];
        v /= 2;
    }
}
int main() {
    long long  n;
    cin >> n;
    long long  k = 1;
    while (k < 2 * n)
    {
        k *= 2;
    }
    long long  array[k];
    array[0] = 0;
    for (long long  i = 0; i < n; i++)
    {
        cin >> array[(k/2) + i];
    }
    for (long long  i = n; i < k; i++)
    {
        array[i + k/2] = 0;
    }
    makeSumDO(&array[0], k);
    string str;
    while (cin >> str)
    {
        long long  a, b;
        cin >> a >> b;
        if (str[2] == 'm')
        {
            cout << sum_r_l(&array[0], a - 1, b - 1, 0, k / 2, 1) + array[k / 2 + b - 1] << "\n";
        }
        else
        {
            set_and_change(&array[0], k, b, a - 1);
        }
    }
    return 0;
}
