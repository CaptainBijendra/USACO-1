/*
ID: suzyzha1
PROG: schlnet
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;
const int maxn = 102;

int n,ans1,ans2;
bool g[maxn][maxn],vis[maxn];
int in_degree[maxn],topo[maxn];

int top=0,stack[maxn];
int idx=0,dfn[maxn],low[maxn];

void dfs(int cur)
{
	topo[0]++;
	topo[topo[0]]=cur;
	vis[cur]=true;
	for(int i=1;i<=n;i++)
		if(g[cur][i] && !vis[i])
		{
			in_degree[i]--;
			dfs(i);
		}
}

void tarjan(int cur)
{
	vis[cur]=true;
	idx++;
	dfn[cur]=low[cur]=idx;

	top++;
	stack[top]=cur;
	for(int i=1;i<=n;i++)
		if(g[cur][i])
		{
			if(!vis[i])
			{
				tarjan(i);
				low[cur]=min(low[cur],low[i]);
			}
			else
			if(dfn[i]<dfn[cur])
				low[cur]=min(low[cur],dfn[i]);
		}

	if(low[cur]==dfn[cur])
	{
		tot++;
		color[cur]=tot;
		while(top>0 && stack[top]!=cur)
		{
			color[stack[top]]=tot;
			top--;
		}
		top--;
	}
}

int main()
{
	fstream fin("schlnet.in",ios::in);
	fstream fout("schlnet.out",ios::out);

	fin>>n;
	int t;
	for(int i=1;i<=n;i++)
		while(true)
		{
			fin>>t;
			if(t==0) break;
			g[i][t]=true;
			in_degree[t]++;
		}
	
	while(topo[0]<n)
	{
		int k=0,min=10000;
		for(int i=1;i<=n;i++)
			if(!vis[i])
				if(in_degree[i]<min)
				{
					min=in_degree[i];
					k=i;
				}

		if(k==0) break;
		dfs(k);
	}
	memset(vis,0,sizeof(vis));

	ans1=0;
	for(int i=1;i<=n;i++)
		if(!vis[topo[i]])
		{
			ans1++;
			dfs(topo[i]);
		}

	fout<<ans1<<endl;

	memset(vis,0,sizeof(vis));

	for(int i=1;i<=n;i++)
		if(!vis[i])
			tarjan(i);

	for(int i=1;)
	
	fout<<ans2<<endl;
	fin.close();
	fout.close();
	return 0;
}