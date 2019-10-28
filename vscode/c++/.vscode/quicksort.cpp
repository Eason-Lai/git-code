#include <iostream>
#include <vector>
using namespace std;
void quicksort(vector<int> nums)
{   
    nums.size();
}
void Qsort(int a[], int low, int high)
{
    if(low >= high)
    {
        return;
    }
    int first = low;
    int last = high;
    int key = a[first];/*用字表的第一个记录作为枢轴*/
 
    while(first < last)
    {
        while(first < last && a[last] >= key)
        {
            --last;
        }
 
        a[first] = a[last];/*将比第一个小的移到低端*/
 
        while(first < last && a[first] <= key)
        {
            ++first;
        }
         
        a[last] = a[first];    
/*将比第一个大的移到高端*/
    }
    a[first] = key;/*枢轴记录到位*/
    Qsort(a, low, first-1);
    Qsort(a, first+1, high);
}
int main()
{
    vector<int> nums;
    int n,i,m;
    cin>>n;
    for (i=0;i<n;i++)
    {
        cin>>m;
        nums.push_back(m);
    }
    return 0; 
}