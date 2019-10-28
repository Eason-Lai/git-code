#include <iostream>
using namespace std;
#include <algorithm>
#include<stack>
#include<sstream>
#include<vector>
#include<queue>
#include<set>
#include <stdio.h>
#include <string>
#include <string.h>
#include <map>


//8
class NFA_Node;

class Trans//trans¿‡£∫Ω” ’ƒ≥∏ˆ◊÷ƒ∏£®incept£©£¨ø…“‘µΩƒ≥∏ˆ◊¥Ã¨Ω·µ„(des)
{
public:
	char incept;
	NFA_Node* des;
	Trans(char incept, NFA_Node* des)
	{
		this->incept = incept;
		this->des = des;
	}
};

class NFA_Node//NFA_Node¿‡£∫√ø∏ˆ◊¥Ã¨Ω·µ„µƒID£®state_ID£©,∏√Ω·µ„µƒtrans, «∑Ò±ª∑√Œ π˝£®visit£©
{
public:
	int stateID;
	vector<Trans*> t;
	bool visit;
	NFA_Node(int stateID)
	{
		visit = false;
		this->stateID = stateID;
	}
	void AddTrans(Trans* tt)
	{
		t.push_back(tt);
	}

};

class NFA//NFA¿‡£∫’˚∏ˆNFAÕºµƒø™ º◊¥Ã¨Ω·µ„£®start£©£¨Ω· ¯◊¥Ã¨Ω·µ„£®end£©
{
public:
	NFA_Node* start;
	NFA_Node* end;
	NFA() {}
	NFA(int SID, char c)
	{
		NFA_Node* s1 = new NFA_Node(SID);
		NFA_Node* s2 = new NFA_Node(SID + 1);
		Trans* tt = new Trans(c, s2);
		s1->AddTrans(tt);
		start = s1;
		end = s2;
	}

};

class Converter  //’˝‘Ú◊™ªªŒ™NFA
{
public:
	int S_ID;//◊¥Ã¨Ω·µ„ID ˝
	Converter(string str)
	{
		pretreat(str);//ÃÌº”¡¨Ω”‘ÀÀ„∑˚
		Houzhui(this->lamb);//◊™ªØŒ™∫Û◊∫±Ì¥Ô Ω
		S_ID = 1;//≥ı º◊¥Ã¨IDŒ™1
	}
	Converter() { S_ID = 1; }

	void show()//œ‘ æ∫Û◊∫±Ì¥Ô Ω
	{
		cout << this->lamb << endl;
	}


	NFA ToNFA()//∫Û◊∫’˝‘Ú±Ì¥Ô Ω◊™ªªŒ™NFA
	{
		//stNFA.Clear();
		//Operator_Stack.Clear();
		NFA tempb, tempb1, tempb2;

		char tempc1;
		for (int i = 0;i < lamb.size();i++)//»Áπ˚ «‘ÀÀ„∑˚£¨≥ˆNFA’ª∂•µƒ¡Ω∏ˆ‘™ÀÿΩ¯––‘ÀÀ„
		{
			tempc1 = lamb[i];
			if (isOperator(tempc1))
			{
				switch (tempc1)
				{
				case '|':
					tempb1 = stNFA.top();
					stNFA.pop();
					tempb2 = stNFA.top();
					stNFA.pop();
					tempb1 = Union(tempb2, tempb1);
					stNFA.push(tempb1);
					break;
				case '&':
					tempb1 = stNFA.top();
					stNFA.pop();
					tempb2 = stNFA.top();
					stNFA.pop();
					tempb2 = Connect(tempb1, tempb2);
					stNFA.push(tempb2);
					break;
				case '*':
					tempb1 = stNFA.top();
					stNFA.pop();
					tempb1 = Closure(tempb1);
					stNFA.push(tempb1);
					break;
				}
			}
			else//»Áπ˚ «ø…Ω” ‹µƒ◊¥Ã¨£®◊÷ƒ∏£©£¨‘Ú–¬‘ˆ“ª∏ˆNFA£¨Ω´NFA»Î’ª
			{
				tempb = NFA(S_ID, tempc1);
				S_ID += 2;
				stNFA.push(tempb);
			}
		}
		tempb = stNFA.top();
		stNFA.pop();
		return tempb;//∑µªÿ’ª∂•£¨NFAµƒ∆ º◊¥Ã¨
	}


private:
	stack<NFA> stNFA;
	stack<char> Operator_Stack;
	string lamb;//lambŒ™stræ≠¥¶¿Ì◊™ªª≥…µƒ◊÷∑˚¥Æ
	bool isOperator(char c)// «∑ÒŒ™‘ÀÀ„∑˚
	{
		switch (c)
		{
		case '|':
		case '&':
		case '(':
		case ')':
		case '!':
		case '*': return true;
		default: return false;
		}
	}

	int getOperatorNumber(char t1)//µ√µΩ‘ÀÀ„∑˚”≈œ»º∂
	{
		switch (t1)
		{
		case '$': return 0;
		case '!': return 1;
		case ')': return 2;
		case '|': return 3;
		case '&': return 4;
		case '*': return 5;
		case '(': return 6;
		default: return 7;
		}
	}

	bool Operator_Less_Than(char t1, char t2)//≈–∂œ‘ÀÀ„∑˚”≈œ»º∂±£¨∑µªÿ1Œ™Aµƒ”≈œ»º∂–°”⁄µ»”⁄B
	{
		int temp1 = getOperatorNumber(t1);
		int temp2 = getOperatorNumber(t2);
		if (temp1 <= temp2)
			return true;
		return false;
	}


	void pretreat(string str)// ‰»Î’˝‘Ú±Ì¥Ô Ω  πab±‰≥…a&b£®œ‘ æ±Ì¥Ô¡¨Ω”‘ÀÀ„∑˚£©  
	{
		int i = 0;
		char c, pc;

		pc = str[i];
		c = str[++i];
		while (str[i] != '\0')
		{
			if (((pc == ')'&&c == '(')) || (!isOperator(pc) && !isOperator(c)) || (!isOperator(pc) && c == '(') || (pc == ')'&&!isOperator(c)) || (pc == '*'&&!isOperator(c)) || (pc == '*'&&c == '('))//Àƒ÷÷«Èøˆ–Ë“™º”&	
				str.insert(i, "&");
			pc = str[i++];
			c = str[i];
		}
		cout<<"i===="<<i<<endl;
		str += "!";//Ω· ¯±Í÷æ
		this->lamb = str;
	}


	void Houzhui(string lamb)//Ω´÷–◊∫±Ì¥Ô Ω◊™ªØŒ™∫Û◊∫±Ì¥Ô Ω
	{
		string l = "";
		Operator_Stack.push('$');//∆ º±Í÷æ
		char tempc, tempc2;

		for (int i = 0;i < lamb.size();i++)
		{
			tempc = lamb[i];
			if (isOperator(tempc))
			{
				switch (tempc)
				{
				case '(': Operator_Stack.push(tempc); break;
				case ')':
					while (Operator_Stack.top() != '(')
					{
						tempc2 = Operator_Stack.top();
						Operator_Stack.pop();
						l += tempc2;
					}
					Operator_Stack.pop();
					break;
				default:
					tempc2 = Operator_Stack.top();//∫Õ’ª∂•µƒ‘™Àÿ±»Ωœ”≈œ»º∂
					while (tempc2 != '('&&Operator_Less_Than(tempc, tempc2))//µ±«∞‘ÀÀ„∑˚”≈œ»º∂±»’ª∂•‘ÀÀ„∑˚”≈œ»º∂–°£¨‘Ú’ª∂•≥ˆ’ª£¨µ±«∞»Î’ª
					{
						tempc2 = Operator_Stack.top();
						Operator_Stack.pop();
						l += tempc2;
						tempc2 = Operator_Stack.top();
					}
					Operator_Stack.push(tempc);
					break;
				}
			}
			else
				l += tempc;
		}
		this->lamb = l;
	}

	NFA& Connect(NFA G1, NFA G2) //∞—G1¡¨‘⁄G2∫Û√Ê 
	{
		Trans* t = new Trans('@', G1.start);
		G2.end->AddTrans(t);
		G2.end = G1.end;
		return G2;//∑µªÿ“ª∏ˆNFA,G2µƒend∏ƒ±‰¡À
	}
	NFA& Union(NFA G1, NFA G2) //G1|G2
	{
		NFA_Node* n1 = new NFA_Node(S_ID++);
		Trans* t1 = new Trans('@', G1.start);
		Trans* t2 = new Trans('@', G2.start);
		n1->AddTrans(t1);
		n1->AddTrans(t2);

		NFA_Node* n2 = new NFA_Node(S_ID++);
		Trans* t3 = new Trans('@', n2);
		Trans* t4 = new Trans('@', n2);
		G1.end->AddTrans(t3);
		G2.end->AddTrans(t4);

		NFA* G = new NFA();
		G->start = n1;
		G->end = n2;

		return *G;//∑µªÿ“ª∏ˆNFA
	}
	NFA& Closure(NFA G2) //G2*
	{
		Trans* t = new Trans('#', G2.start);//#±Ì æ «÷ÿ∏¥µƒø’ ‰»Î  
		G2.end->AddTrans(t);

		NFA_Node* n1 = new NFA_Node(S_ID++);
		Trans* t1 = new Trans('@', n1);
		G2.end->AddTrans(t1);

		NFA_Node* n2 = new NFA_Node(S_ID++);
		Trans* t2 = new Trans('@', G2.start);
		n2->AddTrans(t2);


		Trans* t3 = new Trans('@', n1);
		n2->AddTrans(t3);

		NFA* G = new NFA();
		G->start = n2;
		G->end = n1;

		return *G;
	}
};

void Display(NFA &G, set<char> &S, vector<NFA_Node*> &V)// ‰≥ˆNFA
{
	cout << "’˝‘Ú±Ì¥Ô Ω◊™NFA" << endl;
	queue<NFA_Node*> MyQueue;
	MyQueue.push(G.start);
	cout << "ø™ º◊¥Ã¨" << G.start->stateID << endl;
	char tt;
	while (!MyQueue.empty())
	{
		NFA_Node* tmp = MyQueue.front();
		MyQueue.pop();
		V.push_back(tmp);//∑≈»ÎœÚ¡ø
		tmp->visit = true;
		if (tmp->t.size() > 0)
			cout << "¥”◊¥Ã¨" << tmp->stateID << "≥ˆ∑¢" << endl;
		if (tmp->t.size() > 0)
			for (int i = 0;i < tmp->t.size();i++)//∏√Ω·µ„µƒÀ˘”–trans
			{
				tt = tmp->t[i]->incept;
				if (tt != '@'&&tt != '#')
					S.insert(tt);//∑≈»ÎSET”–¬—”√£ø£ø£°£°£°
				if (tt == '@')
				{
					cout << tmp->stateID << "---" << "epsilon" << "--->" << tmp->t[i]->des->stateID;
					if (tmp->t[i]->des->t.size() == 0) cout << "Ω” ’◊¥Ã¨";//≈–∂œ∏ƒtrans «∑ÒŒ™÷’÷π◊¥Ã¨
					cout << endl;
					if (tmp->t[i]->des->visit == false)//π„∂»±È¿˙
					{
						MyQueue.push(tmp->t[i]->des);tmp->t[i]->des->visit = true;
					}
				}
				else if (tt == '#')
				{
					cout << tmp->stateID << "---" << "epsilonªÿµΩ" << "--->" << tmp->t[i]->des->stateID << endl;
				}
				else
				{
					cout << tmp->stateID << "---" << tt << "--->" << tmp->t[i]->des->stateID;
					if (tmp->t[i]->des->t.size() == 0) cout << "Ω” ’◊¥Ã¨";
					cout << endl;
					if (tmp->t[i]->des->visit == false)
					{
						MyQueue.push(tmp->t[i]->des);tmp->t[i]->des->visit = true;
					}
				}
			}
	}
	cout << "Ω” ’◊¥Ã¨" << G.end->stateID << endl;
}

class DFA_Edge;

class DFA_Node//DFAΩ·µ„£¨◊¥Ã¨±‡∫≈stateID,√ø∏ˆµ„µƒ±ﬂt(œÚ¡øEdge)
{
public:
	int stateID;
	vector<DFA_Edge*> t;
	vector<int> ori;//?
	bool flag;//≈–∂œ «∑Òƒ‹µΩ¥Ô÷’÷π◊¥Ã¨
	DFA_Node(int s)
	{
		flag = false;
		stateID = s;
	}
};

class DFA_Edge//DFAµƒ±ﬂ£¨ø…Ω” ‹µƒ◊÷ƒ∏£®incept£©,∏√±ﬂµƒ÷’µ„£®des£©, «∑Ò∑√Œ π˝£®visit£©
{
public:
	char incept;
	DFA_Node* des;
	bool visit;
	DFA_Edge(char a, DFA_Node* &b)
	{
		incept = a;
		des = b;
		visit = false;
	}
};

/*class Union
{
public:
vector<int> data;
int unionID;
int flag;//=0 ±∏√ºØ∫œ“—±ª∑÷¡—
Union(Union* p)
{
for (int i = 0;i < p->data.size();i++)
this->data[i] = p->data[i];
}
Union(int id)
{
this->unionID = id;
this->flag = 1;
}
};*/

const int MAX = 100;
class NFA_To_DFA
{
public:
	int MaxStatus;//DFAµƒ◊¥Ã¨ ˝◊‹¡ø
	NFA_Node* start;//∆ ºΩ·µ„
	int cando;//¥ÊNFAµƒΩ” ’◊¥Ã¨ !!!!!!!!

	int T[MAX][MAX];//∂˛Œ¨ ˝◊È¥Ê¥¢£¨Tµƒ±Ì ˙µƒ±Ì æDNF◊¥Ã¨£¨∫·µƒ±Ì æNFA◊¥Ã¨°£T[2][1]=1±Ì æ£¨‘⁄DFAµƒ◊¥Ã¨2ø…“‘µΩ¥ÔNFAµƒ◊¥Ã¨1
	int visit[MAX];//∏√◊¥Ã¨ «∑Ò±ª∑√Œ π˝
	vector<NFA_Node*> tmp;//œÚ¡ø°™°™NFAΩ·µ„£¨”√”⁄◊™ªØ ±¡Ÿ ±¥Ê¥¢	
	vector<NFA_Node*> nfa;//œÚ¡ø°™°™NFAΩ·µ„	
	vector<DFA_Node*> dfa;//œÚ¡ø°™°™DFAΩ·µ„
	set<char> Alpha;



	NFA_To_DFA(int max, NFA_Node* &S, int cando)//≥ı ºªØ
	{
		this->MaxStatus = max;
		this->start = S;
		this->cando = cando;
		Init();
		for (int i = 0;i <= MAX;i++)
			for (int j = 0;j <= MAX;j++)
				T[i][j] = 0;
	}

	void Init()
	{
		for (int i = 0;i <= this->MaxStatus;i++)
		{
			this->visit[i] = 0;
		}
		this->tmp.clear();
	}

	NFA_Node*& findnfa(int st)//Õ®π˝◊¥Ã¨st,’“µΩnfaΩ·µ„
	{
		for (int i = 0;i < nfa.size();i++)
			if (nfa[i]->stateID == st) return nfa[i];
	}
	DFA_Node*& finddfa(int st)
	{
		for (int i = 0;i < dfa.size();i++)
			if (dfa[i]->stateID == st) return dfa[i];
	}

	void findclosure(NFA_Node* p)//’“≥ˆ∏√µ„µƒepsilon±’∞¸
	{
		visit[p->stateID] = 1;
		visit[0]++;//visit[0]º«¬º∏√µ„ «∑Òø…æ≠π˝epsilonµΩ¥Ô∆‰À˚◊¥Ã¨
		if (p->t.size() == 0) return;
		for (int i = 0;i < p->t.size();i++)
		{
			if (!visit[p->t[i]->des->stateID] && (p->t[i]->incept == '#' || p->t[i]->incept == '@'))//∏√Ω·µ„√ª”–±ª∑√Œ π˝£¨«“Ω” ‹◊¥Ã¨Œ™ø’
				findclosure(p->t[i]->des);
		}
	}

	void moveto(int st, char c)
	{
		//	if(st==2) cout<<T[st][0]<<endl;
		for (int i = 1;i <= MaxStatus;i++)
		{
			if (T[st][i])
			{
				NFA_Node* p = findnfa(i);
				if (p->t.size()>0)
					for (int j = 0;j < p->t.size();j++)
						if (p->t[j]->incept == c)
						{
							tmp.push_back(p->t[j]->des);
						}//cout<<c<<" "; cout<<p->t[j]->des->stateID<<endl;}
			}
		}
	}

	void closure()
	{
		for (int i = 0;i < tmp.size();i++)
		{
			findclosure(tmp[i]);
		}
	}

	int AddStatus()//T[0][0]µ±«∞◊¥Ã¨ºØ∫œ ˝ ≥ı ºŒ™0 £®µ±«∞DFAµƒΩ⁄µ„ ˝£©
	{
		if (visit[0] == 0)//±Ì æ√ª”–◊¥Ã¨
			return -2;

		for (int i = 1;i <= T[0][0];i++)
		{
			if (visit[0] != T[i][0])//¥ÀºØ∫œ◊¥Ã¨ ˝≤ª“ª—˘ ‘ÚÃ¯π˝ 
				continue;
			int j = 1;
			for (;j <= MaxStatus;j++)
				if (visit[j] != T[i][j])//”–“ª∏ˆ◊¥Ã¨≤ª“ª—˘ ‘ÚÃ¯π˝°£Ω· ¯—≠ª∑£¨–¬‘ˆ◊¥Ã¨
					break;
			if (j == (MaxStatus + 1))  //Àµ√˜æÿ’ÛT÷–“—”–¥ÀºØ∫œ,≤¢∑µªÿŒª÷√  
				return i;
		}

		T[0][0]++;//µ±«∞DFAµƒΩ⁄µ„ ˝
		for (int i = 0;i <= MaxStatus;i++)
			T[T[0][0]][i] = visit[i];
		//	cout<<T[T[0][0]][0];
		return -1;

	}//∑µªÿ-1±Ì æ≤Â»Î¡À–¬◊¥Ã¨ºØ∫œ

	void Convert()
	{
		int i, j;

		findclosure(start);//’“≥ˆ∆ ºµ„µƒepsilon±’∞¸
		AddStatus();//∏¸–¬T[][] ˝◊È£¨£®∏√◊¥Ã¨µƒ±‡∫≈Œ™NFAµƒ£©
		DFA_Node* s1 = new DFA_Node(1);//–¬‘ˆDFAµƒ∆ ºΩ·µ„
		if (visit[cando]) s1->flag = true;//∆ ºΩ·µ„ «∑Òƒ‹µΩ¥ÔΩ· ¯◊¥Ã¨

		for (i = 1;i <= MaxStatus;i++)
			if (visit[i]) s1->ori.push_back(i);//¥Ê»Î∏√µ„æ≠π˝epsilonø…¥ÔµƒÀ˘”–◊¥Ã¨£®∏√◊¥Ã¨µƒ±‡∫≈Œ™NFAµƒ£©

		dfa.push_back(s1);//DFAœÚ¡ø¥Ê»Î∆ ºµ„
		Init();

		//cout<<Alpha.size();     

		for (i = 1;i <= T[0][0];i++)//iƒø«∞µƒ◊¥Ã¨ºØ∫œ∫≈ £®∏√◊¥Ã¨±‡∫≈Œ™DFAµƒ£©
		{
			for (set<char>::iterator t1 = Alpha.begin();t1 != Alpha.end();t1++)//setø…≈≈–Ú,œ»’“æ≠π˝aµƒ£¨‘Ÿ’“æ≠π˝b,c,d...
			{
				moveto(i, *t1);//¥”DFA◊¥Ã¨i,æ≠π˝◊÷∑˚t1ø…µΩ¥Ôµƒ◊¥Ã¨∫≈¥Ê»ÎœÚ¡øtmp(∏√◊¥Ã¨µƒ±‡∫≈Œ™NFAµƒ)
				closure();//’“≥ˆœÚ¡øtmpµƒÀ˘”–epsilon±’∞¸£¨º¥◊¥Ã¨iæ≠π˝◊÷∑˚t1µƒepsilon±’∞¸


				if ((j = AddStatus()) >= 0)//√ª”––¬◊¥Ã¨≤˙…˙ 
				{
					DFA_Edge* e1 = new DFA_Edge(*t1, finddfa(j));
					finddfa(i)->t.push_back(e1);

				}
				else if (j == -1)//≤˙…˙¡À–¬◊¥Ã¨ 
				{
					DFA_Node* d1 = new DFA_Node(T[0][0]);//–¬‘ˆDFAΩ·µ„
					if (visit[cando]) d1->flag = true;// «∑Òƒ‹µΩ¥ÔΩ· ¯◊¥Ã¨
					for (int tt = 1;tt <= MaxStatus;tt++)
						if (visit[tt]) d1->ori.push_back(tt);//¥Ê»Î∏√µ„æ≠π˝epsilonø…¥ÔµƒÀ˘”–◊¥Ã¨£®∏√◊¥Ã¨µƒ±‡∫≈Œ™NFAµƒ£©
					dfa.push_back(d1);//DFAœÚ¡ø¥Ê»Î–¬‘ˆµ„

					DFA_Edge* e1 = new DFA_Edge(*t1, finddfa(T[0][0]));//–¬‘ˆDFA±ﬂ
					finddfa(i)->t.push_back(e1);
					//		cout<<T[0][0]<<endl;
				}

				Init();
			}
		}
	}

	void show(DFA_Node* p)
	{
		if (p->ori.size() == 0) return;
		cout << "(‘≠◊¥Ã¨";
		for (int i = 0;i < p->ori.size();i++)
			cout << p->ori[i];
		cout << ")";
	}

	void Display()
	{
		cout << "NFA◊™DFA" << endl;
		for (int i = 0;i < dfa.size();i++)
			dfs(dfa[i]);
	}

	void dfs(DFA_Node* &p)
	{
		if (p->t.size()>0)
			for (int i = 0;i < p->t.size();i++)
				if (p->t[i]->visit == false)
				{
					cout << p->stateID;
					if (p->flag) cout << "(Ω” ’◊¥Ã¨)";
					show(p);
					cout << "---" << p->t[i]->incept << "--->" << p->t[i]->des->stateID;
					show(p->t[i]->des);
					if (p->t[i]->des->flag) cout << "(Ω” ’◊¥Ã¨)";
					cout << endl;
					p->t[i]->visit = true;
					dfs(p->t[i]->des);
				}
	}

	/*vector<Union*> u;//dfaµƒ◊¥Ã¨ºØ∫œœÚ¡ø
	vector<Union*> temp;//temp[i]:ƒ≥◊¥Ã¨æ≠ƒ≥◊÷∑˚ø…µΩ¥Ô◊¥Ã¨i
	int count = 2;//µ±«∞ºØ∫œ ˝
	int id;
	int ifincept;
	int endid;
	int endunionid;
	int hasincept;//’‚∏ˆºØ∫œµƒÀ˘”–‘™Àÿƒ‹∑ÒΩ” ‹∏√◊÷∑˚

	DFA_Node* tempdfa;

	void init()
	{
	u.clear();
	Union *fstart = new Union(1);
	Union *fend = new Union(2);
	for (int i = 0;i < dfa.size();i++)//±È¿˙À˘“‘DFAΩ·µ„£¨’“≥ˆ∑«÷’Ã¨∫Õ÷’Ã¨£¨ªÆ∑÷ºØ∫œ
	{
	if (dfa[i]->flag)  fend->data.push_back(dfa[i]->stateID);
	else fstart->data.push_back(dfa[i]->stateID);
	}
	u.push_back(fstart);
	u.push_back(fend);

	for (int i = 0;i < u[0]->data.size();i++)
	cout << u[0]->data[i];
	}

	int findendunionid(int id)
	{
	for (int i = 0;i < u.size();i++)
	{
	for (int j = 0;j < u[i]->data.size();j++)
	{
	if (id == u[i]->data[j])
	{
	return u[i]->unionID;
	}
	}

	}

	}

	Union* findbelongunion(int unionid)
	{
	for (int i = 0;i < temp.size();i++)
	{
	if (unionid == temp[i]->unionID)
	return temp[i];
	}
	Union *newunion = new Union(unionid);
	temp.push_back(newunion);
	return newunion;
	}

	void test()
	{
	for (set<char>::iterator t1 = Alpha.begin();t1 != Alpha.end();t1++)
	{
	for (int i = 0;i < u.size();i++)//µ±«∞ºØ∫œ
	{
	temp.clear();
	hasincept = 0;
	for (int j = 0;j < u[i]->data.size();j++)//µ±«∞ºØ∫œ‘™Àÿ
	{
	id = u[i]->data[j];
	ifincept = 0;
	tempdfa = finddfa(id);
	for (int k = 0;k < tempdfa->t.size();k++)//’“µΩµ±«∞‘™Àÿµƒ÷’÷π◊¥Ã¨ID
	{
	if ((tempdfa->t[k])->incept == *t1)
	{
	ifincept = 1;
	endid = tempdfa->t[k]->des->stateID;
	break;
	}

	}
	if (ifincept == 0)endunionid = 0;//0±Ì æŒﬁΩ” ‹
	else endunionid = findendunionid(endid);

	Union *nowunion = findbelongunion(endunionid);//’“≥ˆ‘⁄temp¿Ô Ù”⁄ƒƒ∏ˆºØ∫œ
	nowunion->data.push_back(id);//Ω´id∑≈»Î∏√ºØ∫œ
	}
	if (temp.size() > 1)//¥Û”⁄1±Ì æ”––¬◊¥Ã¨≤˙…˙
	{
	for (int t = 0;t < temp.size();t++)
	{
	if (temp[t]->unionID != u[i]->unionID)
	{
	cout << temp[t]->unionID << endl;
	u.push_back(temp[i]);
	}
	}
	}

	}//±È¿˙ºØ∫œΩ· ¯
	cout << "num" << u.size();
	for (int test = 0;test < u.size();test++)
	cout << u[test]->unionID;
	}//±È¿˙setΩ· ¯
	cout << endl;
	}
	*/


	int state;			        //◊¥Ã¨ 1 ~ state
	map<char, int> inSignInt;	// ‰»Î∑˚
	vector<char>	inSign;		// ‰»Î∑˚ºØ∫œ
	int inSize;					// ‰»Î∑˚∏ˆ ˝
	set<int> final;		     	//÷’Ã¨
	int	  S;				    //∆ º∑˚
	int stateMap[101][101];  	//Õº
	bool reach[101][101];		//ø…¥Ô–‘
	multimap<int, int> nextState; //÷±Ω”∫ÛºÃ (√≤À∆√ª”√µΩ)
	bool useless[101];			   //±Íº«Œ™Œﬁ”√◊¥Ã¨
	vector<set<int> > que;			//◊¥Ã¨∂”¡–
									//int def = 1000000;


	void Input()		// ‰»Î
	{
		state = MaxStatus;//DFAµƒµ±«∞◊¥Ã¨ ˝
		int index = 1;
		for (set<char>::iterator t1 = Alpha.begin();t1 != Alpha.end();t1++)
		{
			inSignInt[*t1] = index++;//inSignInt(a)=1,inSignInt(b)=2£ª∞—◊÷∑˚±‰≥… ˝◊÷£¨“◊”⁄¥Ê¥¢
			inSign.push_back(*t1);//ø…Ω” ‹◊÷∑˚µƒœÚ¡ø
		}
		inSize = inSign.size();//ø…Ω” ‹◊÷∑˚µƒ∏ˆ ˝

		for (int i = 0;i < dfa.size();i++)
		{
			if (dfa[i]->flag)
			{
				final.insert(dfa[i]->stateID);//¥Ê∑≈÷’Ã¨µƒset
			}
		}
		S = 1;//∆ º◊¥Ã¨Œ™1

		int a, b, c;//aŒ™ø™ º◊¥Ã¨£¨bŒ™æ≠π˝µƒ◊÷∑˚£¨cŒ™µΩ¥Ô◊¥Ã¨
		for (int i = 0;i < dfa.size();i++)
		{
			a = dfa[i]->stateID;
			for (int j = 0;j < dfa[i]->t.size();j++)
			{
				b = dfa[i]->t[j]->incept;
				c = dfa[i]->t[j]->des->stateID;
				stateMap[a][inSignInt[b]] = c;		 //»Á£∫ f(1,a)=2;   stateMap[i][j]=x,i◊¥Ã¨æ≠π˝±‡∫≈Œ™jµƒ◊÷∑˚ø…µΩ¥Ôx◊¥Ã¨
				reach[a][c] = 1;//reach[i][j]±Ì æi,j¡Ω∏ˆ◊¥Ã¨ «ø…¥Ôµƒ
				nextState.insert(make_pair(a, c));
			}
		}
	}

	void floyd()			//»Œ“‚¡Ω◊¥Ã¨º‰ø…¥Ô–‘ reach[][]
	{
		for (int k = 1; k <= state; k++) {
			for (int i = 1; i <= state; i++) {
				for (int j = 1; j <= state; j++) {

					if (reach[i][k] == 1 && reach[k][j] == 1) {
						reach[i][j] = 1;
					}
				}
			}
		}

	}

	bool startTo(int n)			//∆ ºÃ¨S ƒ‹∑Ò µΩ¥Ô n					
	{
		if (S == n)         //±æ…Ì «∆ ºÃ¨
			return true;

		return reach[S][n];
	}

	bool toFinal(int n)			//n ƒ‹∑ÒµΩ¥Ô ÷’Ã¨						
	{
		if (find(final.begin(), final.end(), n) != final.end())  //±æ…Ì «÷’Ã¨
			return true;

		for (set<int>::iterator iter = final.begin(); iter != final.end(); ++iter) {
			int j = *iter;
			if (reach[n][j])
				return true;
		}

		return false;
	}

	void markUseless()		//±Íº«Œﬁ”√◊¥Ã¨								
	{
		for (int i = 1; i <= state; i++) {
			if ((startTo(i) == false || toFinal(i) == false)) { //&&find(final.begin(),final.end(),i)==final.end()&&S!=i) {
				useless[i] = true;
			}
		}
	}

	int findFromQue(int x)		//x «∂”¡–que÷–µ⁄º∏∏ˆªÆ∑÷÷–µƒ‘™Àÿ		
	{
		int i;
		for (i = 0; i<que.size(); i++) {
			if (find(que[i].begin(), que[i].end(), x) != que[i].end())
				break;
		}
		//	cout<<i<<"-"<<endl;					//
		return i;
	}

	bool divit(int i, int j)	//∏˘æ› ‰»Î∑˚jªÆ∑÷∂”¡–÷–µ⁄i∏ˆºØ∫œ		
	{
		multimap<int, int> m;
		set<int> s;
		int x, f;
		for (set<int>::iterator iter = que[i].begin(); iter != que[i].end(); ++iter) {
			x = stateMap[*iter][j];
			f = findFromQue(x);
			m.insert(make_pair(f, *iter));
			s.insert(f);
		}
		//	cout<<i<<" "<<s.size()<<"*"<<endl;							//
		//	return 0;
		if (s.size() <= 1) {
			return false;		//√ª±ªªÆ∑÷
		}
		else {
			que.erase(que.begin() + i);
			for (set<int>::iterator sIter = s.begin();sIter != s.end();++sIter) {
				multimap<int, int>::iterator mIter = m.find(*sIter);
				int cnt = m.count(*sIter);
				set<int> newSet;
				for (int k = 0; k != cnt; k++, ++mIter) {
					newSet.insert(mIter->second);
				}
				que.push_back(newSet);
			}
		}
		return true;
	}

	void division()				//ªÆ∑÷À˘”–ºØ∫œ							
	{
		for (set<int>::iterator iter = final.begin(); iter != final.end(); ++iter) {     //œ˚≥˝÷’Ã¨ºØ∫œ÷–µƒŒﬁ”√◊¥Ã¨
			if (useless[*iter]) {
				final.erase(iter);
				iter = final.begin();
			}
		}
		que.push_back(final);
		set<int> s;
		for (int i = 1; i <= state; i++) {
			if (find(final.begin(), final.end(), i) == final.end()) {
				if (!useless[i]) {					//Œﬁ”√◊¥Ã¨≤ª»Î∂”
					s.insert(i);
				}
			}
		}
		que.push_back(s);        //œ»Ω´ ∑«÷’Ã¨°¢÷’Ã¨ªÆ∑÷

								 //	cout<<*(que[0].begin()+1)<<" "<<*(que[1].end()-1);
								 //	return;
		bool flag = true;				//ƒ‹∑ÒºÃ–¯ªÆ∑÷µƒ±Í÷æ
		for (int i = 0; ; i++) {
			//	cout<<"*";
			if (i >= que.size()) {
				if (flag == true)
					break;
				else {
					i = 0;
					flag = true;
				}
			}
			for (int j = 1; j <= inSize; j++) {
				//	cout<<"*";
				if (divit(i, j)) {
					flag = false;
					i--;
					break;
				}
			}
		}
	}

	void Output()
	{
		cout << endl << "Œﬁ”√◊¥Ã¨”–£∫" << endl;
		for (int i = 1; i <= state; i++) {
			if (useless[i])
				cout << i << " ";
		}
		cout << endl;

		cout << endl << "◊Ó÷’µƒªÆ∑÷ «£∫" << endl;
		cout << "P = (";
		for (int i = 0; i<que.size(); i++) {
			cout << " { ";
			for (set<int>::iterator iter = que[i].begin(); iter != que[i].end(); iter++) {
				if (iter != que[i].begin())
					cout << ",";
				cout << *iter;
			}
			cout << " } ";
		}
		cout << ")" << endl;

		cout << endl << "◊Ó–°ªØµƒNFA±Ì:" << endl;
		cout << " \t";
		for (int i = 0; i<inSign.size(); i++) {
			cout << inSign[i] << "\t";
		}
		cout << endl;

		vector<string > strQ;
		for (int i = 0; i<que.size(); i++) {
			string s;
			for (set<int>::iterator iter = que[i].begin(); iter != que[i].end(); ++iter) {
				s.push_back(*iter + '0');
			}
			strQ.push_back(s);
		}
		int out[100][100];
		for (int i = 0; i<que.size(); i++) {
			if (!strQ[i].empty())
				cout << *strQ[i].begin();
			char a= *strQ[i].begin();
			cout << "\t";
			for (int j = 0; j<inSign.size(); j++) {
				int x = stateMap[*(que[i].begin())][inSignInt[inSign[j]]];
				int f = findFromQue(x);
				if (f < strQ.size() && !strQ[f].empty())
				{
					cout << *strQ[f].begin();
					out[*strQ[i].begin()-48][j] = *strQ[f].begin()-48;
				}
				else out[*strQ[i].begin() - 48][j] =0;
				cout << "\t";
			}
			cout << endl;
		}

		cout << "switch(state)" << endl;
		cout << "{" << endl;
		for (int i = 1; i < que.size(); i++)
		{
			cout << " case " << *strQ[i].begin() - 48 << ":" << endl;
			for (int j = 0; j < inSign.size(); j++)
			{
				if (out[*strQ[i].begin() - 48][j] != 0)
				{
					cout << "   if(input==" << inSign[j] << ")" <<endl;
					cout << " {";
					cout << "   state=" << out[*strQ[i].begin() - 48][j] << ";" << endl;
					cout << "     break;" << endl;
					cout << " }" << endl;

				}
				
			}
			cout << "  error();" << endl;
		}
		cout << "default: error();" << endl;
		cout << "}" << endl;

	}



};




int main()
{

	string str;
	char s[100];
	while (gets(s))
	{
		str = s;
		cout<<str.length()<<endl;
		Converter cnt(str);
		cnt.show();
		NFA result = cnt.ToNFA();
		
		//NFA_To_DFA(int max, NFA_Node* &S, int cando)
		NFA_To_DFA ntd(cnt.S_ID - 1, result.start, result.end->stateID);

		//	cout<<result.start->stateID;
		//	cout<<result.start->t.size();

		Display(result, ntd.Alpha, ntd.nfa);

		ntd.Convert();

		ntd.Display();
		ntd.Input();
		ntd.floyd();
		ntd.markUseless();
		ntd.division();
		ntd.Output();

	}
	while (1);
}
