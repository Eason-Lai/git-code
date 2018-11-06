#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;
const int MaxNum = 50;
char str[MaxNum]; //输入的正则表达式
int j[256]; //判断映射（区分符号和字符）
int f[256];  //字符映射数组
char fc[MaxNum];
int fnum; //加入的字符映射数
int ind; //字符串下标
int nfa_state; //当前nfa的创建的状态数
int nfa_symbol; //当前nfa的符号数
char error_word[20][20];
vector<int> **nfa_table;
int *dfa_table[MaxNum*3];
vector <int> dfa_list[MaxNum*3];
vector <int> dfa0[MaxNum];
int dfa_state; //当前dfa的创建的状态数
int dfa_symbol; //当前dfa的符号数
int *min_table[MaxNum*3]; //DNA最小化后的表格
int min_state;
int flag;

struct NFA
{
	int num;
	int symbol; 
	NFA *next;	
};

struct Node
{
    int begin;
    int end;
};


struct NFA nfa_arr[MaxNum*3];
Node node;

Node E();
Node T();
Node F();
Node P();
void init();
void error_word_init();
void error(int num);
char gettoken();
char nexttoken();
int charfun(char c);
void link(int begin,int end,int sym);
void nfa_deal();
bool exist_vec(int num,vector<int> &v);
bool add_vec(int num,vector <int> &v);
vector<int> dfa_link0(int row);
vector<int> dfa_link1(int row,int symbol);
void nfa_dfa();
int add_dfa_list(vector <int> v);
vector<int> dfa_visit(int state);
vector<int> add_vector(vector<int> a,vector<int> b);
int dfa_val(int state);
void dfa_min();

int main()
{
    int i,j,k,n;
    vector <int> v;
    init();
    cin>>str;
    //node = E();
    nfa_deal();
    cout<<nfa_symbol;
    // cout<<"b"<<node.begin<<endl;
    // cout<<"e"<<node.end<<endl;
    // cout<<"state:"<<nfa_state<<endl;
    // cout<<"symbol:"<<nfa_symbol<<endl;
    // //nfa_deal(); //正则表达式转nfa
    // nfa_dfa();  //nfa转dfa
    // cout<<dfa_state<<endl;
    // dfa_min();  //dfa最小化
    // cout<<"min_state"<<min_state<<endl;

    return 0;
}

void init()
{
    int i;
    for (i=0;i<MaxNum*2;i++)
    {
        nfa_arr[i].num = i;
        nfa_arr[i].symbol = -1;
        nfa_arr[i].next = 0;
    }
    nfa_state = 0;
    nfa_symbol =0;
    fnum=0;
    //初始化字符数组，-1为空映射
    for (i=0;i<256;i++)  
    {
        f[i]=-1;
        fc[i]=0;
    }
    //初始化判断数组，0为空映射
    for (i=0;i<256;i++)  
    {
        j[i]=0;
    }
    for (i = 48; i <= 57; i++)  j[i] = 1; //数字
    for (i = 97; i <= 122; i++) j[i] = 1; //小写字母
    for (i = 65; i <= 90; i++)  j[i] = 1; //大写字母
    j['.']=2;
    j['*']=2;
    j['|']=2;
    j['(']=2;
    j[')']=2;
    flag = 1;
}

int charfun(char c)
{
    if ( f[c] == -1 ) 
    {
        fnum++;
        f[c]=fnum;
        fc[fnum] = c;
        
    }
    return f[c];
}

void link(int begin,int end,int sym)
{
    NFA *p,*newnode;
    p=&nfa_arr[begin];
    newnode = new NFA;
    newnode->num  = end;
    newnode->symbol = sym;
    newnode->next = 0;
    while ( p->next != 0 )
    {
        p = p->next;
    }
    p->next = newnode;
}

void error_word_init()
{
    strcpy(error_word[1],"字符串下标越界");
    strcpy(error_word[2],"缺少')'");
    strcpy(error_word[3],"ind越界");
    strcpy(error_word[4],"ind越界");
    strcpy(error_word[5],"ind越界");
}

void error(int num)
{
    cout<<error_word[num]<<endl;
}

char gettoken()
{
    if ( ind >= 0 && ind <= strlen(str) ) 
        return str[ind];
    else 
    {
        error(1);
        return 0;
    }
}

char nexttoken()
{
    ind++;
    if ( ind >= 0 && ind <= strlen(str) ) 
        return ind;
    else 
    {
        error(1);
        return 0;
    }
}

Node E()
{
    int a,b;
    Node temp,t;
    temp = T();
    cout<<"E ";
    cout<<"index="<<ind<<" token="<<gettoken()<<endl;
    while ( gettoken() == '|' )
    {
        nexttoken();
        t = T();
        a = ++nfa_state;
        b = ++nfa_state;
        link(a,temp.begin,0);
        link(a,t.begin,0);
        link(temp.end,b,0);
        link(t.end,b,0);
        temp.begin = a;
        temp.end = b;
    }
    return temp;
}

Node T()
{
    Node temp,t;
    temp = F();
    cout<<"T ";
    cout<<"index="<<ind<<" token="<<gettoken()<<endl;
    while ( gettoken() == '.' )
    {
        nexttoken();
        t = F();
        link(temp.end,t.begin,0);
        temp.end = t.end;
        cout<<"."<<endl;
    }
    return temp;
}

Node F()
{
    int a,b;
    Node temp,t;
    temp = P();
    cout<<"F ";
    cout<<"index="<<ind<<" token="<<gettoken()<<endl;
    while ( gettoken() == '*' )
    {
        nexttoken();
        a = ++nfa_state;
        b = ++nfa_state;
        link(a,temp.begin,0);
        link(temp.end,b,0);
        link(temp.end,temp.begin,0);
        link(a,b,0);
        temp.begin = a;
        temp.end = b;
    }
    return temp;
}

Node P()
{
    int a,b;
    Node temp,t;
    cout<<"P ";
    cout<<"index="<<ind<<" token="<<gettoken()<<endl;
    if ( gettoken() == '(' )
    {
        nexttoken();
        temp = E();
        if ( gettoken() == ')' )
        {
            nexttoken();
        }
        else
        {
            error(2);
        }
    }
    else if ( j[gettoken()] != 2 )
    {
        cout<<ind<<gettoken()<<endl;
        a = ++nfa_state;
        b = ++nfa_state;
        cout<<"a="<<a<<endl;
        cout<<"b="<<b<<endl;
        link(a,b,charfun(gettoken()));
        temp.begin = a;
        temp.end = b;
        nexttoken();
    }
    return temp;
}

void nfa_deal()
{
    node = E();
    int i,j,k,s,n,vn;
    NFA *p;
    vector <int> v;
    nfa_table = new vector<int>* [nfa_state+1]; 
    for (i=0;i<=nfa_state;i++)
    {
        nfa_table[i] = new vector<int> [fnum+1];
    }
    for (i=1;i<=nfa_state;i++)
    {
        p = &nfa_arr[i];
        while ( p-> next != 0 )
        {
            p = p->next;
            s = p->symbol;
            //cout<<"i:"<<i<<" s:"<<s<<endl;
            n = p->num;
            //cout<<i<<n<<endl;
            nfa_table[i][s].push_back(n);
        }
    }
    dfa_symbol = nfa_symbol;
    /*for (i=1;i<=nfa_state;i++)
    {
        for (j=0;j<=fnum;j++)
        {
            v = nfa_table[i][j];
            if ( !v.empty() )
            {
                vn = v.capacity();
                for (k=0;k<vn;k++)
                {
                    cout<<v[k];
                }
            }
        }
    }*/
}
bool exist_vec(int num,vector <int> &v)
{
    int i,n;
    if ( !v.empty() ) 
    {
        n = v.capacity();
        for (i=0;i<n;i++)
        {
            if ( v[i] == num ) return true;
        }
    }
    return false;
}

bool add_vec(int num,vector <int> &v)
{
    if ( exist_vec(num,v) )
    {
        return false;
    }
    else
    {
        v.push_back(num);
        return true;
    }
}

vector<int> add_vector(vector<int> a,vector<int> b)
{
    int i,n;
    int table[nfa_state+1];
    vector <int> v;
    v = a;
    for (i=0;i<=nfa_state;i++)
    {
        table[i] = 0;
    }
    n = a.capacity();
    for (i=0;i<n;i++)
    {
        table[a[i]] = 1;
    }
    n = b.capacity();
    for (i=0;i<n;i++)
    {
        if (!table[b[i]]) v.push_back(b[i]);
    }
    return v;
}

vector<int> dfa_link0(int row)
{
    if ( !dfa0[row].empty() ) return dfa0[row];
    int i,j,now,vn;
    vector <int> v;
    vector <int> t;
    add_vec(row,v);
    now = 1;
    v = add_vector(v,nfa_table[row][0]);
    vn = v.capacity();
    while ( now < vn )
    {
        dfa_link0(v[now]);
        v = add_vector(v,dfa0[v[now]]);
        now++;
        vn = v.capacity();
    }
    dfa0[row] = v;
    return v;
}

vector<int> dfa_link1(int row,int symbol)
{
    int i,j,now,vn;
    vector <int> v;
    vector <int> t;
    now = 0;
    v = nfa_table[row][symbol];
    vn = v.capacity();
    while ( now < vn )
    {
        t = dfa_link0(v[now]);
        v = add_vector(v,t);
        now++;
        vn = v.capacity();
    }
    return v;
}

int add_dfa_list(vector <int> v)
{
    int i;
    if ( v.empty() ) return 0;
    for (i=1;i<=dfa_state;i++)
    {
        if ( dfa_list[i] == v ) return i;
    }
    dfa_state++;
    dfa_list[dfa_state] = v;
    return dfa_state;
}

vector<int> dfa_visit(int state,int symbol)
{
    int i,j,num,t,pn,qn,k;
    int table[nfa_state];
    vector <int> v;
    vector <int> *p,*q;
    for (i=0;i<=nfa_state;i++)
    {
        table[i] = 0;
    }
    num = dfa_list[state].capacity(); //dfa_list[state]为当前要进行连接的闭包
    for (i=0;i<num;i++)
    {
        t = dfa_list[state][i];
        p = &nfa_table[t][symbol];
        pn = p->capacity();
        for (j=0;j<pn;j++)
        {
            table[(*p)[j]] = 1;
            q = &dfa0[(*p)[j]];
            qn = q->capacity();
            for (k=0;k<qn;k++)
            {
                table[(*q)[k]] = 1;
            }
        }
    }
    for (i=0;i<=nfa_state;i++)
    {
        if (table[i]) v.push_back(i);
    }
    return v;
}

void nfa_dfa()
{
    int i,j,t,now_state;
    vector <int> v;
    dfa_state = 0;
    now_state = 0;
    //初始化dfa_list
    for (i=0;i<MaxNum*3;i++)  
    {
        dfa_table[i] = new int[nfa_state+1];
        for (j=0;j<=nfa_symbol;j++)
        {
            dfa_table[i][j] = 0;
        }
    }
    for (i=1;i<=nfa_state;i++)
    {
        dfa_link0(i);
    }
    sort(dfa0[1].begin(),dfa0[1].end());
    dfa_list[1] = dfa0[node.begin];
    dfa_state++;
    now_state++;
    while ( now_state <= dfa_state )
    {
        for (i=1;i<=nfa_symbol;i++)
        {
            v = dfa_visit(now_state,i);
            if ( v.empty() ) 
            {
                dfa_table[now_state][i] = 0;
            }
            else
            {
                t = add_dfa_list(v);
                dfa_table[now_state][i] = t;
            }
        }
        now_state++;
    }
}

int dfa_val(int state)
{
    int i,sum,t;
    t = 1;
    sum = 0;
    for (i=1;i<=dfa_symbol;i++)
    {
        sum = sum + dfa_table[state][i]*t;
        t = t*dfa_state;
    }
    return sum;
}

void dfa_min()
{
    int i,j,t,n;
    int flag=0;
    int val[MaxNum]; //判断状态是否重复出现
    int table[dfa_state+1]; //原dfa同种跳转的状态合一
    int l[dfa_state+1]; //最小化的状态下标所对应的原dfa状态下标
    int rl[dfa_state+1]; //原dfa状态下标对应的最小化的状态下标
    min_state = dfa_state;
    n=0;
    for (i=0;i<MaxNum;i++)
    {
        val[i] = -1;
    }
    for (i=0;i<=min_state;i++)   //各种初始化
    {
        min_table[i] = new int[dfa_symbol+1];
        table[i] = i;
        for (j=0;j<=dfa_symbol;j++)
        {
            min_table[i][j] = 0;
        }
    }
    for (i=1;i<=dfa_state;i++)  //找出可以优化合一的状态
    {
        t = dfa_val(i);
        for(j=1;j<=n;j++)
        {
            if ( t == val[j] ) 
            {
                flag=j;
                break;
            }
        }
        if ( flag == 0 )
        {
            n++;
            val[n] = t;
            l[n] = i; //n为最小化后的状态小标，l[n]为原dfa的状态下标
            rl[i] = n; //i为原dfa的状态下标,rl[i]为最小化后的状态小标
        }
        else
        {
            rl[i] = flag;
            min_state--;
        }
        flag = 0;
    }
    rl[0]=0;
    for (i=1;i<=min_state;i++)  
    {
        for (j=1;j<=dfa_symbol;j++)
        {
            t = dfa_table[l[i]][j];
            min_table[i][j] = rl[t];
        }
    }
}