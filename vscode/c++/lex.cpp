#include <iostream>
#include <stack>
using namespace std;
char str[50]; //输入的正则表达式
int j[256]; //判断映射（区分符号和字符）
int f[256];  //字符映射数组
int fnum; //加入的字符映射数


struct NFA nfa_arr[50];
void init();

int charfun();

void nfa();

int main()
{
    cin>>str;
    return 0;
}

void init()
{
    int i;
    fnum=0;
    //初始化字符数组，-1为空映射
    for (i=0;i<256;i++)  
    {
        f[i]=-1;
    }
    //初始化判断数组，0为空映射
    for (i=0;i<256;i++)  
    {
        j[i]=0;
    }
    for (i = 48; i <= 57; i++)  j[i] = 1; //数字
    for (i = 97; i <= 122; i++) j[i] = 1; //小写字母
    for (i = 65; i <= 90; i++)  j[i] = 1; //大写字母
    j['*']=2;
    j['|']=3;
    j['(']=4;
    j[')']=5;
}

int charfun(char c)
{
    if ( f[c] == -1 ) 
    {
        fnum++;
        f[c]=fnum;
    }
    return f[c];
}

void nfa()
{
    int index; //正则表达式下标
    int t;
    int ch;
    stack <int> symbol; //符号栈
    stack <express_node> expression; //表达式栈
    index = 0;
    while (1)
    {
        t=j[str[index]];
        if ( t % 2 ) //为符号
        {
            switch(t)
            {
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
            }
        }
        else if ( t ) //为字符
        {
            ch = charfun(str[index]);
            express_node *head,*end;
            head=new express_node();
            end=new express_node();
            head->front=0;
            head->symbol=ch;
            head->next=end;
            end->front=head;
            end->symbol=-1; //-1代表无连接
            end->next=0;
            expression.push(*head);
            expression.push(*end);
        }
    }
}