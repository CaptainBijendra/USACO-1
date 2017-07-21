/*
ID: suzyzha1
PROG: msquare
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;

struct Square
{
	int config[8];
} target;

Square init = { .config = {1,2,3,4,5,6,7,8} };

struct Node
{
	Square sq;
	int steps,last;
	char opr;
};

int head,tail;
Node qu[40330];
bool vis[41000];

const int tr[][8]={
	{7,6,5,4,3,2,1,0},
	{3,0,1,2,5,6,7,4},
	{0,6,1,3,4,2,5,7}
};

const int factorial[]={1,1,2,6,24,120,720,5040};

void transform(int mode,const Square &st,Square &res)
{
	for(int i=0;i<8;i++)
		res.config[i]=st.config[tr[mode][i]];
}

int cantor(Square *a)
{
	int res=0,t;

	for(int i=0;i<7;i++)
	{
		t=0;
		for(int j=i+1;j<8;j++)
			if(a->config[j]>a->config[i])
				t++;

		res+=t*factorial[7-i];
	}

	return res;
}

int main()
{
	fstream fin("msquare.in",ios::in);
	fstream fout("msquare.out",ios::out);

	for(int i=0;i<8;i++) fin>>target.config[i];

	int tar_cantor=cantor(&target);

	if(cantor(&init)==tar_cantor)
	{
		fout<<0<<endl<<endl;
		fin.close();
		fout.close();
		return 0;
	}

	head=0; tail=1;
	qu[0].sq=init;
	qu[0].steps=0;
	qu[0].last=0;
	vis[cantor(&init)]=true;

	int idx=0;
	Node cur;
	Square tmp;
	bool flag=false;
	while(head<tail)
	{
		cur=qu[head];
		head++;
		
		for(int i=0;i<3;i++)
		{
			transform(i,cur.sq,tmp);

			int j=cantor(&tmp);
			if(vis[j]) continue;
			vis[j]=true;

			qu[tail].sq=tmp;
			qu[tail].steps=cur.steps+1;
			qu[tail].last=head-1;
			qu[tail].opr='A'+i;

			tail++;

			if(j==tar_cantor)
			{
				idx=tail-1;
				flag=true;
				break;
			}
		}
		if(flag) break;
	}

	fout<<qu[idx].steps<<endl;

	int count=0,i=0;
	char ans[200];
	while(idx>0)
	{
		ans[i]=qu[idx].opr;
		idx=qu[idx].last;
		i++;
	}
	i--;
	count=0;
	while(i>=0)
	{
		fout<<ans[i];
		i--;
		count++;
		if(count%60==0)
		{
			count=0;
			fout<<endl;
		}
	}
	if(count) fout<<endl;

	fin.close();
	fout.close();
	return 0;
}