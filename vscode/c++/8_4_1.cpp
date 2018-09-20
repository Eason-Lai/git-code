#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
const int maxn = 100005;
int n, q, t, a, b, sum;
char str[maxn];
int c[26][maxn];
void fun();
void judge();
int main()
{
    int i, j, k;
    int mins;
    scanf("%d", &t);
    for (i = 1; i <= t; i++)
    {
        scanf("%d %d\n", &n, &q);
        cin>>str;
        printf("Case #%d:\n", i);
        fun();
        for (j = 1; j <= q; j++)
        {
            sum = 0;
            mins = 95;
            scanf("%d %d", &a, &b);
            a = a - 1;
            judge();
            printf("%d\n", sum);
        }
    }
    return 0;
}
void fun()
{
    int i, j;
    int r;
    for (j = 0; j < 26; j++)
    {
        c[j][0] = 0;
    }
    for (i = 0; i < n; i++)
    {
        r = str[i] - 65;
        for (j = 0; j < 26; j++)
        {
            c[j][i + 1] = c[j][i];
        }
        c[r][i + 1]++;
    }
}
void judge()
{
    int i, j, d;
    d = 0;
    for (i = 0; i < 26; i++)
    {
        d = c[i][b] - c[i][a];
        if (d > 0)
        {
            sum = d;
            break;
        }
    }
}