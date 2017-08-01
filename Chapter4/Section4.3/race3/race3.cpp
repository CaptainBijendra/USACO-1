/*
ID: suzyzha1
PROG: race3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int maxn = 52;

int n,g[maxn][maxn];
int qu[maxn];
bool vis[maxn];
int co[maxn];
int key[maxn],cut[maxn];

bool bfs(int block)
{
	memset(vis,0,sizeof(vis));
	int l=0,r=1;
	qu[0]=0;
	vis[0]=true;
	while(l<r)
	{
		int cur=qu[l];
		l++;
		for(int i=1;i<=g[cur][0];i++)
		{
			int t=g[cur][i];
			if(t==n) return true;
			if(vis[t] || t==block) continue;
			
			vis[t]=true;
			qu[r]=t;
			r++;
		}
	}

	return vis[n];
}

bool color(int st,int c,int block)
{
	int l=0,r=1;
	qu[0]=st;
	co[st]=c;
	while(l<r)
	{
		int cur=qu[l];
		l++;
		for(int i=1;i<=g[cur][0];i++)
		{
			int t=g[cur][i];
			if(co[t]==c) continue;
			if(co[t]!=0 && co[t]!=c) return false;
			co[t]=c;
			if(t!=block)
			{
				qu[r]=t;
				r++;
			}
		}
	}
	return true;
}

int main()
{
	fstream fin("race3.in",ios::in);
	fstream fout("race3.out",ios::out);

	n=0;
	int t;
	while(!fin.eof())
	{
		fin>>t;
		if(t==-1) break;
		if(t==-2)
		{
			n++;
			continue;
		}
		g[n][0]++;
		g[n][g[n][0]]=t;
	}
	n--;

	for(int i=1;i<n;i++)
		if(!bfs(i))
		{
			key[0]++;
			key[key[0]]=i;
		}

	for(int i=1;i<=key[0];i++)
	{
		int cur=key[i];

		memset(co,0,sizeof(co));
		color(0,1,cur);
		if(color(cur,2,-1))
		{
			cut[0]++;
			cut[cut[0]]=cur;
		}
	}

	for(int i=0;i<key[0];i++)
		fout<<key[i]<<" ";
	fout<<key[key[0]]<<endl;

	for(int i=0;i<cut[0];i++)
		fout<<cut[i]<<" ";
	fout<<cut[cut[0]]<<endl;

	fin.close();
	fout.close();
	return 0;
}