/**
 * 来源：https://www.cnblogs.com/skywang12345/p/3603669.html
 **/
#include <cstdio>
#include <algorithm>
#include <vector>
#define _for(i, a, b) for (int i = (a); i < (b); i++)
#define _rep(i, a, b) for (int i = (a); i <= (b); i++)

using std::vector;

int GetMaxDigits(int a[], int len) {
    int ans = a[0];
    _for(i, 1, len)
        ans = (a[i] > ans ? a[i] : ans);
    return ans;
}

void CountSort(int a[], const int &n, const int &exp) {
    vector<int> output;
    int bucket[10] = {0};

    _for(i, 1, n)
        bucket[(a[i] / exp) % 10]++;

    _for(i, 1, 10)
        bucket[i] += bucket[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[bucket[(a[i] / exp) % 10] - 1] = a[i];
        bucket[(a[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) a[i] = output[i];
}

void RadixSort(int a[], int n) {
    int biggest = GetMaxDigits(a, n);
    for (int exp = 1; biggest / exp != 0; exp *= 10)
        CountSort(a, n, exp);
}