/*
ID: suzyzha1
PROG: milk6
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;

const int maxn = 40;
const int maxm = 1002;

int n,m,max_flow;
int cost[maxn][maxn],g[maxn][maxn];
int st[maxm],en[maxm],c[maxm];
int head,tail,qu[maxn],level[maxn];
int idx[maxm],min_num;
bool now[maxm],best[maxm];

bool bfs()
{
	memset(level,0,sizeof(level));

	head=0; tail=1;
	qu[0]=1;
	level[1]=1;
	while(head<tail)
	{
		int cur=qu[head];
		head++;

		for(int i=1;i<=n;i++)
			if(level[i]==0 && cost[cur][i]>0)
			{
				level[i]=level[cur]+1;
				qu[tail]=i;
				tail++;
			}
	}
	return (level[n]!=0);
}

int flow(int cur,int max_flow)
{
	if(cur==n) return max_flow;

	for(int i=1;i<=n;i++)
		if(level[i]==level[cur]+1 && cost[cur][i]>0)
		{
			int tmp=flow(i,min(max_flow,cost[cur][i]));
			if(tmp<=0) continue;
			cost[cur][i]-=tmp;
			cost[i][cur]+=tmp;
			return tmp;
		}

	return 0;
}

int dinic()
{
	int ans=0;
	while(bfs())
		ans+=flow(1,INT_MAX);
	return ans;
}

void get_best(int cur,int sumcost,int sumn)
{
	if(sumn>=min_num) return;

	if(cur>idx[0])
	{
		if(sumcost!=max_flow) return;

		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				cost[i][j]=g[i][j];

		for(int i=1;i<=idx[0];i++)
			if(now[i])
				cost[st[idx[i]]][en[idx[i]]]-=c[idx[i]];

		if(!bfs())
		{
			min_num=sumn;
			for(int i=1;i<=idx[0];i++) best[i]=now[i];
		}
		return;
	}

	if(sumcost+c[idx[cur]]<=max_flow)
	{
		now[cur]=true;
		get_best(cur+1,sumcost+c[idx[cur]],sumn+1);	
	}

	now[cur]=false;
	get_best(cur+1,sumcost,sumn);
}

int main()
{
	fstream fin("milk6.in",ios::in);
	fstream fout("milk6.out",ios::out);

	fin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		fin>>st[i]>>en[i]>>c[i];
		cost[st[i]][en[i]]+=c[i];
	}
	fin.close();
	for(int k=1;k<=n;k++)
		for(int j=1;j<=n;j++)
			g[k][j]=cost[k][j];

	max_flow=dinic();
	fout<<max_flow<<" ";

	int sum=0;
	for(int i=1;i<=m;i++)
	{
		for(int k=1;k<=n;k++)
			for(int j=1;j<=n;j++)
				cost[k][j]=g[k][j];

		cost[st[i]][en[i]]-=c[i];
		int new_flow=dinic();
		if(new_flow<max_flow)
		{
			idx[0]++;
			idx[idx[0]]=i;
			sum+=c[i];
		}
	}

	if(sum==max_flow)
	{
		for(int i=0;i<=idx[0];i++)
			fout<<idx[i]<<endl;
		fout.close();
		return 0;
	}

	min_num=idx[0];
	get_best(1,0,0);

	fout<<min_num<<endl;
	for(int i=1;i<=idx[0];i++)
		if(best[i])
			fout<<idx[i]<<endl;

	fout.close();
	return 0;
}