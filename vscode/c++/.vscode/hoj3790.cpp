#include <cstdio>
using namespace std;
void fun(int n,int m);
int main() {
    int n,m;
    do
    {
        scanf("%d %d",&n,&m);
        if (n == 0 && m == 0){
            break;
        } 
        else {
            fun(n,m);
        }
    }while(n==m && n == 0);
    return 0;
}
void fun(int n,int m) {
    int i,j ,s,t ,a,b ,d,p;
    int min_d,min_p;
    min_d = 0;
    min_p = 0;

    //初始化
    int **dis = new int*[n];
    int **cost = new int*[n];
    int *sd = new int[n];
    int *sc = new int[n];
    int *mark = new int[n];
    for (i=0;i<n;i++) {
        dis[i] = new int[n];
        cost[i] = new int[n];
        for (j=0;j<n;j++) {
            dis[i][j] = -1;
            cost[i][j] = -1;
        }
    }

    //接受输入
    for (i=0;i<m;i++) {
        scanf("%d %d %d %d",&a,&b,&d,&p);
        dis[a-1][b-1] = d;
        dis[b-1][a-1] = d;
        cost[a-1][b-1] = p;
        cost[b-1][a-1] = p;
    }    
    scanf("%d %d",&s,&t);
    s--;
    t--;

    for (i=0;i<n;i++) {
        mark[i] = 0;
        sd[i] = dis[s][i];
        if ( sd[i] !=1 ) sc[i] = cost[s][i];
    }

    sd[s] = 0;
    sc[s] = 0;
    mark[s] = 1;

    //处理
    for (i=0;i<n;i++) {
        if ( mark[i] == 1 ) continue;
        for (j=0;j<n;j++) {
            if ( dis[i][j] != -1 && sd[i] != -1 ) {
                if ( sd[j] > dis[i][j] + sd[i] ) {
                    sd[j] = dis[i][j] + sd[i];
                    sc[j] = cost[i][j] + sc[i];
                }
                else if ( sd[j] == dis[i][j] + sd[i] ){
                    if ( sc[i] > cost[i][j] + sc[i] ) {
                        sc[j] = cost[i][j] + sc[i];
                    }               
                }
            }
        }
    }

    min_d = sd[t];
    min_p = sc[t];
    
    //输出结果
    printf("%d %d\n",min_d,min_p);

    //清除
    delete []dis;
    delete []cost;
}