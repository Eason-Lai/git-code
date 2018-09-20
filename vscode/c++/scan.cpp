#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
//判断是否为空格，是的话index前移再判断下一位
bool IsSpace(char *s, int &index) 
{
    int i=index;
    while ( s[index] == ' ' ) {
        index++;
    }  
    if ( i == index ) return true;
    else return false;
}
//判断是否为特殊符号
char* IsSymbol(char *s, int &index)
{
    char* ns=new char[5];

}
//判断是否为数字（常数）
char* IsNumber(char *s, int &index)
{
    char* ns=new char[10];
    int k=0;
    while ( s[index] >= 48 && s[index] <= 57 ) {  //开头为0-9或者后面含有0-9
        ns[k]=s[index];
        k++;
        index++;
    }
    if ( k != 0 ) cout<<ns<<"\t\t\t"<<"数"<<endl;
    return ns;
}
int main()
{
    char str[200];
    int i;
    int length;
    while ( cin.getline(str,200) ) {
        if ( str[0] == '\0' ) break; //判断是否未最后一行
        i=0;
        length=strlen(str);
        while ( i != length ) {
            IsSpace(str,i);
            IsNumber(str,i);
        }
    }
    return 0;
}
