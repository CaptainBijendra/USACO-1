/*
ID: suzyzha1
PROG: telecow
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;
const int maxn = 202;

int n,m,tot;
int g[maxn][maxn],backup[maxn][maxn],rest[maxn];

int head,tail,qu[maxn],level[maxn];
int ans,cut[maxn];

bool connected()
{
	memset(level,0,sizeof(level));
	qu[0]=0;
	level[0]=1;
	head=0; tail=1;
	int cur;
	while(head<tail)
	{
		cur=qu[head];
		head++;
		for(int i=1;i<=tot;i++)
			if(g[cur][i]>0 && level[i]==0)
			{
				level[i]=level[cur]+1;
				qu[tail]=i;
				tail++;
			}
	}
	return (level[tot]!=0);
}

int flow(int cur,int max)
{
	if(cur==tot) return max;

	for(int i=1;i<=tot;i++)
		if(g[cur][i]>0 && level[i]==level[cur]+1)
		{
			int new_flow=g[cur][i]<max ? g[cur][i]:max;
			int tmp=flow(i,new_flow);
			if(tmp>0)
			{
				g[cur][i]-=tmp;
				g[i][cur]+=tmp;
				return tmp;
			}
		}

	return 0;
}

int dinic()
{
	int res=0;
	while(connected())
		res+=flow(0,INT_MAX);
	return res;
}

int main()
{
	fstream fin("telecow.in",ios::in);
	fstream fout("telecow.out",ios::out);

	int a,b,st,en;
	fin>>n>>m>>st>>en;
	tot=(n<<1)+1;
	for(int i=0;i<m;i++)
	{
		fin>>a>>b;
		g[a+n][b]=g[b+n][a]=INT_MAX;
	}
	fin.close();

	g[0][st]=g[en+n][tot]=INT_MAX;
	for(int i=1;i<=n;i++)
		if(i!=st && i!=en)
			g[i][i+n]=1;
		else
			g[i][i+n]=INT_MAX;

	for(int i=1;i<=tot;i++)
		for(int j=1;j<=tot;j++)
			backup[i][j]=g[i][j];

	ans=dinic();
	
	if(ans==0)
	{
		fout<<0<<endl<<endl;
		fout.close();
		return 0;
	}
	
	fout<<ans<<endl;

	for(int i=1;i<=n;i++)
		rest[i]=g[i][i+n];

	for(int i=1;i<=n;i++)
		if(i!=st && i!=en && rest[i]==0)
		{
			for(int j=1;j<=tot;j++)
				for(int k=1;k<=tot;k++)
					g[j][k]=backup[j][k];

			g[i][i+n]=0;

			int sum=dinic();
			
			if(sum==ans-1)
			{
				cut[0]++;
				cut[cut[0]]=i;

				backup[i][i+n]=0;
				ans--;
				if(ans==0) break;
			}
		}

	for(int i=1;i<=cut[0];i++)
		if(i==1)
			fout<<cut[i];
		else
			fout<<" "<<cut[i];
	fout<<endl;

	fout.close();
	return 0;
}