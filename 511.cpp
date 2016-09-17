#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <stdio.h>

using namespace std;

#define ll long long
#define base 1000000000

ll n;
long k;

long q[5000];

long** D;
long** ans;
long** tmp_matrix;
long* d;
long* tmp_d;
long* res = new long[k];


void fast_mul(long* a, long* b){
    for (int i = 0; i < k; i++)
        tmp_d[i] = 0;
    for (int j = 0; j < k; j++)
    {
        for (int r = 0; r < k; r++){
            tmp_d[j] = (tmp_d[j] + a[r] * b[(j - r + k) % k]) % base;
        }
    }
    for (int i = 0; i < k; i++)
        a[i] = tmp_d[i];
}

long* get_ans(long b){

    for (int i = 0; i < k; i++)
        res[i] = 0;
    res[0] = 1;
    while (b > 0){
        if (b % 2)
            fast_mul(res, d);
        b >>= 1;
        fast_mul(d, d);

    }
    return res;
}



int main()
{
    n = 1234567898765;
    k = 4321;
    //cin >> n >> k;
    tmp_matrix = new long*[k];
    D = new long*[k];
    ans = new long*[k];
    for (int i = 0; i < k; i++)
        tmp_matrix[i] = new long[k],D[i] = new long[k], ans[i] = new long[k];
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            D[i][j] = 0;
    for (ll i = 1; i * i <= n; i++)
        if (n % i == 0){
            q[i % k]++;
            if ((n / i) != i) q[ (n / i) % k]++;
        }

    /*
    for (int i = 0; i < k; i++)
        for (auto item : q)
            D[i][(i + item.first) % k] = item.second;
    */

    d = new long[k];
    tmp_d = new long[k];
    for (int i = 0; i < k; i++)
        d[i] = q[i];

    d = get_ans(n);

    long x = (k - (n % k)) % k;
    //cout << ans[0][x] << endl;
    cout << d[x];
    return 0;
}