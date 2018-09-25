#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int table[256];

//判断单个字符
bool IsNum(char c); //数字
bool IsLowercase(char c); //小写字母
bool IsCapital(char c); //大写字母
bool Isalphabet(char c); //字母

//处理对应字符
bool IsSpace(char *s, int &index); //处理空格以及换行
char *IsSymbol(char *s, int &index); //处理特殊符号
char *IsNumber(char *s, int &index); //处理数字
char *IsWord(char *s, int &index); //处理单词（标识符或关键字）
char *IsString(char *s, int &index); //处理字符串

void init()
{
    int i;
    for (i=0;i<=255;i++) table[i]=0;   //默认
    for (i=48;i<=57;i++) table[i]=1;   //数字
    for (i=97;i<=122;i++) table[i]=2;  //小写字母
    for (i=65;i<=90;i++) table[i]=3;   //大写字母

    //空格 换行
    table[32]=4; 
    table[10]=4;
    table[13]=4;

    //特殊符号 > < = + - * / % & ; 
    for (i=33;i<=47;i++) table[i]=5;   
    for (i=58;i<=64;i++) table[i]=5;   
    for (i=91;i<=96;i++) table[i]=5;   
    for (i=123;i<=126;i++) table[i]=5;   
    
    table[34]=6;  //双引号"
}

void judge()
{
    char c;
    char str[200];
    int ind;
    int t;
    while (c)
    {
        t = table[c];
        switch(t)
        {
            case 0:break;
            case 1:
            {
                IsNumber(str,ind);
                break;
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                break;
            }
            case 4:
            {
                break;
            }
            case 5:
            {
                break;
            }
            case 6:
            {
                break;
            }
            default:
            {
                cout<<"不知道这是什么东西"<<endl;
                break;
            }
        }
    }
}

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
    int k = 0;
    while (!IsNum(s[index]) && !Isalphabet(s[index]))
    {
        ns[k] = s[index];
        k++;
        index++;
    }
    if (k != 0)
        cout << ns << "\t\t\t"
             << "特殊符号" << endl;
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
char *IsString(char *s, int &index)
{
    char *ns = new char[30];
    int k = 0;
    if (s[index] == '"')
    {
        k++;
        index++;
        ns[k] = s[index];
        while (s[index] != '"')
        {
            k++;
            index++;
            ns[k] = s[index];
        }
    }
    if (k != 0)
        cout << ns << "\t\t\t"
             << "串" << endl;
}

int main()
{
    char str[200];
    int i;
    int length;
    init();

    ofstream fs;
    fs.open("test.txt",ios::in);
    
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
