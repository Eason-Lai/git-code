#include <cstdio>
using namespace std;
int find(int n);
bool check(int a,int b);
void mer(int a,int b);
int fa[5005];
int main() {
    int n,m,q,i;
    int a,b;
    while (scanf("%d %d %d",&n,&m,&q)==3) {
        for (i=1;i<=n;i++){
            fa[i] = i;
        }
        for (i=0;i<m;i++){
            scanf("%d %d",&a,&b);
            mer(a,b);
        }
        for (i=0;i<q;i++){
            scanf("%d %d",&a,&b);
            if ( check(a,b) && a != b ) printf("yes\n");
            else printf("no\n");
        }
    }
    return 0;
}

int find(int n) {
    if ( fa[n] == n ) return n;
    else return fa[n] = find(fa[n]);
}

bool check(int a,int b) {
    if ( find(a) == find(b) ) return true;
    else return false;
}

void mer(int a,int b) {
    if ( !check(a,b) ) fa[a] = fa[b];
}

