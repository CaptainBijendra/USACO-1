/*
ID: suzyzha1
PROG: lgame
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxm = 40002;

string init;
int n,num[30],v[130];
char letters[30];

int ans=0,sum=0;
struct Plan
{
	string s[2];
	bool is_pair;

	Plan(){ is_pair=false; }

	bool operator == (const Plan &b)
	{
		if(is_pair!=b.is_pair) return false;
		if(s[0]!=b.s[0]) return false;
		if(!is_pair) return true;
		if(s[1]!=b.s[1]) return false;
		return true;
	}
} best[200];

class TrieNode
{
public:
	bool is_word;
	TrieNode *ch[26];

	TrieNode()
	{
		is_word=false;
		for(int i=0;i<26;i++) ch[i]=NULL;
	}
	void add(string s);
} root;

void TrieNode::add(string s)
{
	TrieNode *p=&root;
	for(int i=0;i<s.length();i++)
	{
		int tmp=s[i]-'a';
		if(p->ch[tmp]==NULL)
			p->ch[tmp]=new TrieNode();
		
		p=p->ch[tmp];
	}
	p->is_word=true;
}

void dfs2(int cur,TrieNode *p,int sumv,string s,int max_len,string *first)
{
	if(cur==max_len)
	{
		if(!p->is_word) return;

		if(sumv>=ans)
		{
			if(sumv>ans)
			{
				ans=sumv;
				sum=0;
			}
			sum++;
			best[sum].s[0]=*first;
			best[sum].s[1]=s;
			best[sum].is_pair=true;
		}
		return;
	}

	for(int i=1;i<=n;i++)
		if(num[i] && p->ch[letters[i]-'a']!=NULL)
		{
			num[i]--;
			dfs2(cur+1,p->ch[letters[i]-'a'],sumv+v[letters[i]],s+letters[i],max_len,first);
			num[i]++;
		}
}

void dfs1(int cur,TrieNode *p,int sumv,string s,int max_len)
{
	if(cur==max_len)
	{
		if(!p->is_word) return;

		if(max_len<init.length())
		{
			for(int i=1;i<=init.length()-max_len;i++)
				dfs2(0,&root,sumv,"",i,&s);
		}
		if(sumv>=ans)
		{
			if(sumv>ans)
			{
				ans=sumv;
				sum=0;
			}
			sum++;
			best[sum].s[0]=s;
			best[sum].is_pair=false;
		}
		return;
	}

	for(int i=1;i<=n;i++)
		if(num[i] && p->ch[letters[i]-'a']!=NULL)
		{
			num[i]--;
			dfs1(cur+1,p->ch[letters[i]-'a'],sumv+v[letters[i]],s+letters[i],max_len);
			num[i]++;
		}
}

bool cmp(const Plan &a,const Plan &b)
{
	int tmp=a.s[0].compare(b.s[0]);
	if(tmp<0) return true;
	if(tmp>0) return false;

	if(!a.is_pair && b.is_pair) return true;
	if(a.is_pair && !b.is_pair) return false;

	tmp=a.s[1].compare(b.s[1]);
	return (tmp<0);
}

int main()
{
	fstream fin("lgame.in",ios::in);
	fstream fdict("lgame.dict",ios::in);
	fstream fout("lgame.out",ios::out);

	fin>>init;
	fin.close();
	
	string tmp;
	while(!fdict.eof())
	{
		fdict>>tmp;
		if(tmp==".")
			break;
		root.add(tmp);
	}

	fdict.close();

	n=0;
	for(int i=0;i<init.length();i++)
	{
		bool flag=true;
		for(int j=1;j<=n;j++)
			if(init[i]==letters[j])
			{
				flag=false;
				num[j]++;
				break;
			}

		if(flag)
		{
			n++;
			letters[n]=init[i];
			num[n]=1;
		}
	}

	v['e']=v['i']=v['s']=1;
	v['r']=v['t']=v['a']=v['n']=2;
	v['o']=v['l']=3;
	v['u']=v['d']=v['c']=4;
	v['y']=v['p']=v['g']=v['h']=v['b']=v['m']=5;
	v['w']=v['f']=v['k']=v['v']=6;
	v['q']=v['j']=v['z']=v['x']=7;

	for(int i=3;i<=min(7,(int)init.length());i++)
		dfs1(0,&root,0,"",i);

	for(int i=1;i<=sum;i++)
		if(best[i].is_pair)
			if(best[i].s[0].compare(best[i].s[1])>0)
				best[i].s[0].swap(best[i].s[1]);

	sort(best+1,best+sum+1,cmp);

	fout<<ans<<endl;
	for(int i=1;i<=sum;i++)
	{
		if(i>1 && best[i]==best[i-1])
			continue;

		if(best[i].is_pair)
			fout<<best[i].s[0]<<" "<<best[i].s[1]<<endl;
		else
			fout<<best[i].s[0]<<endl;
	}
	
	fout.close();
	return 0;
}