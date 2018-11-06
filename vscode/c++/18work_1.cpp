#include <iostream>
using namespace std;
int main()
{
    long long i,n,sum;
    int j;
    for (j=1;j<5;j++)
    {
        sum=0;
        cout<<"n=";
        cin>>n;
        for (i=1;i<=n-1;i++)
        {
            sum+=i;;
        }
        cout<<"sum="<<sum<<endl;
        cout<<"sum%n="<<sum%n<<endl;
    }
    return 0;
}