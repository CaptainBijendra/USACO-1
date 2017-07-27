/*
ID: suzyzha1
PROG: fence6
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;

const int maxn = 102;

int n,m,ans;
int v[maxn][2][10],len[maxn];
bool dir[maxn][maxn],vis[maxn];

void dfs(int cur,int d,int sum,int s)
{
	if(sum>=ans) return;

	vis[cur]=true;
	for(int i=1;i<=v[cur][1-d][0];i++)
	{
		int t=v[cur][1-d][i];
		int out=dir[t][cur];
		if(t==s && out==0)
		{
			ans=sum<ans ? sum:ans;
			return;
		}
		if(vis[t]) continue;

		vis[t]=true;
		dfs(t,out,sum+len[t],s);
		vis[t]=false;
	}
}

int main()
{
	fstream fin("fence6.in",ios::in);
	fstream fout("fence6.out",ios::out);

	fin>>n;
	m=n<<1;

	int s;
	for(int i=0;i<n;i++)
	{
		fin>>s;
		fin>>len[s];

		fin>>v[s][0][0]>>v[s][1][0];
		for(int j=1;j<=v[s][0][0];j++)
			fin>>v[s][0][j];
		
		for(int j=1;j<=v[s][1][0];j++)
		{
			fin>>v[s][1][j];
			dir[s][v[s][1][j]]=true;
		}
	}
	
	ans=INT_MAX;
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		dfs(i,0,len[i],i);
	}
	
	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}