/*
ID: suzyzha1
PROG: shuttle
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int n,ans[200];

struct State
{
	char wood[25];
	int empty,move,pre;

	bool operator == (const State &b)
	{
		if(empty!=b.empty) return false;
		if(strncmp(wood,b.wood,(n<<1)+1)==0) return true;
		return false;
	}
} qu[120000];

int main()
{
	fstream fin("shuttle.in",ios::in);
	fin>>n;
	fin.close();

	State target;
	qu[0].move=qu[0].pre=-1;
	qu[0].empty=target.empty=n;
	qu[0].wood[n]=target.wood[n]=' ';
	for(int i=0;i<n;i++)
	{
		qu[0].wood[i]=target.wood[i+n+1]='W';
		qu[0].wood[i+n+1]=target.wood[i]='B';
	}

	char j;
	State cur,tmp;
	int head=0,tail=1,loc,lim=n<<1,idx=-1;
	while(head<tail)
	{
		cur=qu[head];
		head++;

		tmp=cur;
		loc=cur.empty;
		for(int i=-2;i<=2;i++)
			if(i!=0 && loc+i>=0 && loc+i<=lim)
			{
				j=tmp.wood[loc+i];
				if((i==2 || i==-2) && j==tmp.wood[loc+(i/2)]) continue;
				if(j=='W' && i>0) continue;
				if(j=='B' && i<0) continue;

				tmp.wood[loc+i]=' ';
				tmp.wood[loc]=j;
				tmp.empty=loc+i;
				tmp.move=loc+i+1;
				tmp.pre=head-1;
				qu[tail]=tmp;
				tail++;
				if(tmp==target)
				{
					idx=tail-1;
					break;
				}
				tmp=cur;
			}

		if(idx!=-1) break;
	}

	fstream fout("shuttle.out",ios::out);

	while(idx>0)
	{
		ans[0]++;
		ans[ans[0]]=qu[idx].move;
		idx=qu[idx].pre;
	}

	fout<<ans[ans[0]];
	int count=1;
	for(int i=ans[0]-1;i>=1;i--)
	{
		if(count) fout<<" ";
		fout<<ans[i];
		count++;
		if(count==20)
		{
			count=0;
			fout<<endl;
		}
	}
	if(count) fout<<endl;

	fout.close();
	return 0;
}