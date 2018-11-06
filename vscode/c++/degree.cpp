#include <cstdio>
using namespace std;
const int maxn = 200005;
int d[maxn];
int t, n, m, k;
int main()
{
    int i, j, u, v;
    int maxd;
    int a, b, c;
    scanf("%d", &t);
    for (i = 0; i < t; i++)
    {
        scanf("%d%d%d", &n, &m, &k);
        maxd = 0;
        for (j = 0; j < n; j++)
        {
            d[j] = 0;
        }
        for (j = 0; j < m; j++)
        {
            scanf("%d%d", &u, &v);
            d[u]++;
            d[v]++;
        }
        for (j = 0; j < n; j++)
        {
            if (d[j] > maxd)
                maxd = d[j];
        }
        a = n - 1 - m;
        c = maxd + a + k;
        if (c >= n - 1)
            maxd = n - 1;
        else
            maxd = c;
        printf("%d\n", maxd);
    }
    return 0;
}