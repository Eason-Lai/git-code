#include <cstdio>
using namespace std;
int t, mx, my, n;
long long sum;
int main()
{
    int i, j, x, y, min;
    int a, b;
    scanf("%d", &t);
    for (i = 0; i < t; i++)
    {
        sum=0;
        scanf("%d%d%d", &mx, &my, &n);
        for (j = 0; j < n; j++)
        {
            min = 2000000;
            scanf("%d%d", &x, &y);
            a = mx - x;
            b = my - y;
            if (a < min)
                min = a;
            if (b < min)
                min = b;
            if (x < min)
                min = x;
            if (y < min)
                min = y;
            sum+=min;
        }
        printf("%lld\n",sum);
    }
    return 0;
}
