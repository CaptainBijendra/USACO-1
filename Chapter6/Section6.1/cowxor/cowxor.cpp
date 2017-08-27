/*
ID: suzyzha1
PROG: cowxor
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;
const int max_len = 21;
const int maxn = 100002;

int n,d[maxn];
int ans,st,en;

struct Node
{
public:
	int rank;
	Node *l,*r;

	Node() { rank=0; l=r=NULL; }
	void add(int cur,int r);
} trie;

void Node::add(int cur,int r)
{
	int idx = max_len,tmp;
	Node *p = &trie;

	while(idx>=0 && p!=NULL)
	{
		tmp=cur&(1<<idx);
		if(tmp==0)
		{
			if(p->l==NULL)
				p->l=new Node();
			p=p->l;
		}
		else
		{
			if(p->r==NULL)
				p->r=new Node();
			p=p->r;
		}
		idx--;
	}

	p->rank=r;
}

void find_best(int cur,int cur_end)
{
	int idx = max_len,tmp;
	Node *p = &trie, *q;

	while(idx>=0 && p!=NULL)
	{
		int tmp=cur&(1<<idx);
		if(tmp==0)
		{
			if(p->r!=NULL) q=p->r;
			else q=p->l;
		}
		else
		{
			if(p->l!=NULL) q=p->l;
			else q=p->r;
		}
		p=q;
		idx--;
	}

	tmp = (d[p->rank]) ^ cur;
	if(tmp>ans)
	{
		ans=tmp;
		st=p->rank+1;
		en=cur_end;
	}
}

int main()
{
	fstream fin("cowxor.in",ios::in);
	fstream fout("cowxor.out",ios::out);

	trie.add(0,0);
	ans=-1;

	fin>>n;
	for(int i=1;i<=n;i++)
	{
		fin>>d[i];
		d[i]^=d[i-1];
		find_best(d[i],i);

		trie.add(d[i],i);
	}

	fout<<ans<<" "<<st<<" "<<en<<endl;
	fin.close();
	fout.close();
	return 0;
}