#include <iostream>
#include <cstdio>
#include <string>
using namespace std;

//判断单个字符
bool IsNum(char c) //数字
{
    return (c >= 48 && c <= 57);
}
bool IsLowercase(char c) //小写字母
{
    return (c >= 97 && c <= 122);
}
bool IsCapital(char c) //大写字母
{
    return (c >= 65 && c <= 90);
}
bool Isalphabet(char c) //字母
{
    return (IsLowercase(c) || IsCapital(c));
}

//判断是否为空格，是的话index前移再判断下一位
bool IsSpace(char *s, int &index)
{
    int i = index;
    while (s[index] == ' ')
    {
        index++;
    }
    if (i == index)
        return true;
    else
        return false;
}

//判断是否为特殊符号
char *IsSymbol(char *s, int &index)
{
    char *ns = new char[5];
}

//判断是否为数字（常数）
char *IsNumber(char *s, int &index)
{
    char *ns = new char[10];
    int k = 0;
    while (IsNum(s[index])) //开头为0-9或者后面含有0-9
    { 
        ns[k] = s[index];
        k++;
        index++;
    }
    if (k != 0)
        cout << ns << "\t\t\t"
             << "数" << endl;
    return ns;
}

//判断是否为单词
char *IsWord(char *s, int &index)
{
    char *ns = new char[15];
    int k = 0;
    if (IsLowercase(s[index]) || IsCapital(s[index])) //第一个字母
    {
        ns[k] = s[index];
        k++;
        index++;
        while (IsNum(s[index]) || Isalphabet(s[index])) //开头为0-9或者后面含有0-9
        { 
            ns[k] = s[index];
            k++;
            index++;
        }
    }
}

//判断是否为串

int main()
{
    char str[200];
    int i;
    int length;
    while (cin.getline(str, 200))
    {
        if (str[0] == '\0')
            break; //判断是否未最后一行
        i = 0;
        length = strlen(str);
        while (i != length)
        {
            IsSpace(str, i);
            IsNumber(str, i);
        }
    }
    return 0;
}
