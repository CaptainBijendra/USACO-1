/*
ID: suzyzha1
PROG: lamps
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

int n,c;
int on_lamps[102],off_lamps[102];

struct Status
{
	long long lamps[2];
};

int num=0;
Status ans[20];

const int button[][2]={{0,1},{0,2},{1,2},{0,3}};

bool legal(Status s)
{
	int tmp;
	for(int i=1;i<=on_lamps[0];i++)
	{
		tmp=on_lamps[i]-1;
		if((s.lamps[tmp/64]&((long long)1<<(tmp%64)))==0) return false;
	}
	for(int i=1;i<=off_lamps[0];i++)
	{
		tmp=off_lamps[i]-1;
		if((s.lamps[tmp/64]&((long long)1<<(tmp%64)))!=0) return false;
	}
	return true;
}

Status press_button(int cur,Status s)
{
	Status t=s;
	for(int i=button[cur][0];i<n;i+=button[cur][1])
		t.lamps[i/64]^=((long long)1<<(i%64));
	return t;
}

void dfs(int cur,int times,Status s)
{
	if(times>c) return;
	if(cur>=4)
	{
		if((c-times)%2) return;

		if(legal(s))
		{
			num++;
			ans[num]=s;
		}
		return;
	}

	dfs(cur+1,times,s);
	dfs(cur+1,times+1,press_button(cur,s));
}

bool cmp(Status a,Status b)
{
	int x,y;
	for(int j=0;j<n;j++)
	{
		x=a.lamps[j/64]&((long long)1<<(j%64));
		y=b.lamps[j/64]&((long long)1<<(j%64));
		if(x==y) continue;
		if(x!=0 && y==0) return false;
		if(y!=0 && x==0) return true;
	}
	return true;
}

int main()
{
	fstream fin("lamps.in",ios::in);
	fstream fout("lamps.out",ios::out);

	int tmp;
	fin>>n>>c;
	while(true)
	{
		fin>>tmp;
		if(tmp==-1) break;
		on_lamps[0]++;
		on_lamps[on_lamps[0]]=tmp;
	}
	while(true)
	{
		fin>>tmp;
		if(tmp==-1) break;
		off_lamps[0]++;
		off_lamps[off_lamps[0]]=tmp;
	}
	fin.close();

	Status s;
	for(int i=0;i<n;i++)
		s.lamps[i/64]|=((long long)1<<(i%64));
	
	dfs(0,0,s);

	sort(ans+1,ans+num+1,cmp);

	if(num==0)
		fout<<"IMPOSSIBLE"<<endl;
	else
		for(int i=1;i<=num;i++)
		{
			for(int j=0;j<n;j++)
				if((ans[i].lamps[j/64]&((long long)1<<(j%64)))!=0)
					fout<<1;
				else
					fout<<0;

			fout<<endl;
		}

	fout.close();
	return 0;
}
