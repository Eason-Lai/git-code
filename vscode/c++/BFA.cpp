#include <iostream>
#include <vector>
using namespace std;
char str[50];
int c[256]; //映射符号对应的类型 1:字母，数字； 2:闭包； 3：或； 4:括号； 
struct Link{
    int sign;
    int arrive;
};
vector <struct Link> s[50];
void init();
int deal(int begin,int strb,int stre);
int main()
{
    cin>>str;
    return 0;
}
void init()
{
    int i,j;
    for (i = 0; i <= 255; i++)
        c[i] = 0; //默认
    for (i = 48; i <= 57; i++)
        c[i] = 1; //数字
    for (i = 97; i <= 122; i++)
        c[i] = 1; //小写字母
    for (i = 65; i <= 90; i++)
        c[i] = 1; //大写字母
    c['*']=2;
    c['|']=3;
    c['(']=4;
    c[')']=5;
}
int deal(int begin,int strb,int stre)
{
    int now;
    int index=begin;
    switch (index)
    {
        case 1:
        {
            break;
        }
    }
    return now;
}