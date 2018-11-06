#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//判断单个字符
bool IsNum(char c);       //数字
bool IsLowercase(char c); //小写字母
bool IsCapital(char c);   //大写字母
bool Isalphabet(char c);  //字母

//处理对应字符
bool IsSpace(char *s, int &index);                //处理空格以及换行
char *IsSymbol(char *s, int &index);              //处理特殊符号
char *IsNumber(char *s, int &index);              //处理数字
char *IsWord(char *s, int &index);                //处理单词（标识符或关键字）
char *IsString(char *s, int &index);              //处理字符串
char *IsAnnotation(char *s, int &index, int len); //处理注释符

void init();
void judge(char *str, int length);

struct Eworld
{
    Eworld *front;
    char str[15];
    Eworld *next;
};

class Hash_Word
{
  public:
    Hash_Word();
    Eworld *findlist(char *s);
    void insert(char *s); //导入
    bool dele(char *s);   //删除
    bool search(char *s); //搜索

  private:
    const static int n = 47;
    Eworld *hashtable;
};

Hash_Word hw;
int table[256]; //映射各字符类别的数组

Hash_Word::Hash_Word()
{
    int i;
    hashtable = new Eworld[n];
    for (i = 0; i < n; i++)
    {
        hashtable[i].front = 0;
        hashtable[i].str[0] = 0;
        hashtable[i].next = 0;
    }
}

Eworld *Hash_Word::findlist(char *s)
{
    int i, len, sum;
    Eworld *p, *newnode;
    len = strlen(s);
    sum = 0;
    for (i = 0; i < len; i++)
    {
        sum += s[i];
    }
    sum = sum % n;
    p = &hashtable[sum];
    return p;
}

void Hash_Word::insert(char *s)
{
    Eworld *p, *newnode;
    p = findlist(s);
    while (p->next != 0)
        p = p->next;
    newnode = new Eworld;
    p->next = newnode;
    newnode->front = p;
    strcpy(newnode->str, s);
    newnode->next = 0;
}

bool Hash_Word::dele(char *s)
{
    Eworld *p;
    p = findlist(s);
    while (strcmp(p->str, s) != 0 && p->next != 0)
        p = p->next;
    if (strcmp(p->str, s) != 0)
        return false;
    p->front->next = p->next;
    return true;
}

bool Hash_Word::search(char *s)
{
    Eworld *p;
    p = findlist(s);
    while (strcmp(p->str, s) != 0 && p->next != 0)
        p = p->next;
    if (strcmp(p->str, s) != 0)
        return false;
    return true;
}

void init()
{
    int i;
    //0默认 1数字 2小写字母 3大写字母 4空格换行 5特殊符号 6双引号（串）
    for (i = 0; i <= 255; i++)
        table[i] = 0; //默认
    for (i = 48; i <= 57; i++)
        table[i] = 1; //数字
    for (i = 97; i <= 122; i++)
        table[i] = 2; //小写字母
    for (i = 65; i <= 90; i++)
        table[i] = 3; //大写字母

    //空格 换行
    table[32] = 4;
    table[10] = 4;
    table[13] = 4;

    //特殊符号 > < = + - * / % & ;
    for (i = 33; i <= 47; i++)
        table[i] = 5;
    for (i = 58; i <= 64; i++)
        table[i] = 5;
    for (i = 91; i <= 96; i++)
        table[i] = 5;
    for (i = 123; i <= 126; i++)
        table[i] = 5;

    table['"'] = 6; //双引号"

    table['/'] = 7; //注释

    //将关键字导入到hashtable
    char key[][15] = {"iostream", "main", "for", "do", "while", "switch", "case", "return", "include", "break", "if", "else", "default", "using", "namespace",
                      "cout", "cin", "fstream", "printf", "scanf", "cstdio", "class", "struct", "public", "private", "protected", "std",
                      "iostream.h", "int", "char", "double", "float", "bool", "string", "void"};
    for (i = 0; i < 34; i++)
    {
        hw.insert(key[i]);
    }
}

void judge(char *str, int length)
{
    int index, t, flag;
    flag = 0;
    index = 0;
    while (index < length)
    {
        t = table[str[index]];
        //0默认 1数字 2小写字母 3大写字母 4空格换行 5特殊符号 6双引号（串） 7注释“/”
        switch (t)
        {
        case 0:
            break;
        case 1: //数字
        {
            IsNumber(str, index);
            break;
        }
        case 2: //小写字母
        {
            IsWord(str, index);
            break;
        }
        case 3: //大写字母
        {
            IsWord(str, index);
            break;
        }
        case 4: //空格换行
        {
            IsSpace(str, index);
            break;
        }
        case 5: //特殊符号
        {
            IsSymbol(str, index);
            break;
        }
        case 6: //双引号（串）
        {
            IsString(str, index);
            break;
        }
        case 7: //注释
        {
            IsAnnotation(str, index, length);
            break;
        }
        default:
        {
            flag = 1;
            cout << "不知道这是什么东西" << endl;
            break;
        }
        }
        if (flag)
            break;
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
    while (table[s[index]] == 4)
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
    while (table[s[index]] == 5)
    {
        ns[k] = s[index];
        k++;
        index++;
    }
    if (k != 0)
        cout << ns << "\t\t\t\t"
             << "特殊符号" << endl;
}

//判断是否为数字（常数）
char *IsNumber(char *s, int &index)
{
    char *ns = new char[10];
    int k = 0;
    while (table[s[index]] == 1) //开头为0-9或者后面含有0-9
    {
        ns[k] = s[index];
        k++;
        index++;
    }
    if (k != 0)
        cout << ns << "\t\t\t\t"
             << "数" << endl;
    return ns;
}

//判断是否为单词
char *IsWord(char *s, int &index)
{
    char *ns = new char[15];
    int k = 0;
    bool flag = false;
    if (Isalphabet(s[index])) //第一个字母
    {
        ns[k] = s[index];
        k++;
        index++;
        while (table[s[index]] == 1 || Isalphabet(s[index]) || s[index] == '_' || s[index] == '.') //开头为0-9或者后面含有0-9
        {
            ns[k] = s[index];
            k++;
            index++;
        }
    }
    flag = hw.search(ns);
    if (flag)
        cout << ns << "\t\t\t\t"
             << "关键字" << endl;
    else
        cout << ns << "\t\t\t\t"
             << "标识符" << endl;
}

//判断是否为串
char *IsString(char *s, int &index)
{
    char *ns = new char[30];
    int k = 0;
    if (s[index] == '"')
    {
        ns[k] = s[index];
        k++;
        index++;
        while (s[index] != '"')
        {
            ns[k] = s[index];
            k++;
            index++;
        }
        ns[k] = s[index];
        k++;
        index++;
    }
    if (k != 0)
        cout << ns << "\t\t\t\t"
             << "串" << endl;
}

//判断是否为串
char *IsAnnotation(char *s, int &index, int len)
{
    char *ns = new char[50];
    int k = 0;
    if (s[index] == '/' && s[index+1] == '/')
    {
        ns[k] = s[index];
        ns[++k] = s[++index];
        k++;
        index++;
        while (index != len)
        {
            ns[k] = s[index];
            k++;
            index++;
        }
        ns[k] = s[index];
        k++;
        index++;
    }
    if (k != 0)
        cout << ns << "\t\t\t\t"
             << "注释" << endl;
}

int main()
{
    char str[200];
    int i;
    int length;
    init();
    ifstream fs;
    fs.open("/Users/liyixun/git-code/vscode/c++/testcpp.txt", ios::in);
    while (!fs.eof())
    {
        fs.getline(str, 200);
        judge(str, strlen(str));
    }
    fs.close();
    return 0;
}
