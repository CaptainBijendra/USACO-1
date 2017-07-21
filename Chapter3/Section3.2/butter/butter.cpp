/*
ID: suzyzha1
PROG: butter
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;

const int maxp = 802;
const int maxm = 3000;

int n,p,m;
int w[maxp],dist[maxp];
int head[maxp],next_edge[maxm],en[maxm],len[maxm];

int ans=INT_MAX;
int l,r,qu[10*maxm];
bool in_qu[maxp];

void spfa(int s)
{
	memset(in_qu,0,sizeof(in_qu));

	for(int i=1;i<=p;i++)
		dist[i]=INT_MAX;

	dist[s]=0;
	qu[0]=s;
	in_qu[s]=true;
	l=0; r=1;

	int cur,u,v;
	while(l<r)
	{
		cur=qu[l];
		l++;

		u=head[cur];
		while(u>=0)
		{
			v=en[u];
			if(dist[v]>dist[cur]+len[u])
			{
				dist[v]=dist[cur]+len[u];
				if(!in_qu[v])
				{
					qu[r]=v;
					in_qu[v]=true;
					r++;
				}
			}
			u=next_edge[u];
		}
		in_qu[cur]=false;
	}
}

int get_sum()
{
	int res=0;
	for(int i=1;i<=p;i++)
	{
		if(w[i]>0 && dist[i]==INT_MAX)
			return INT_MAX;
		res+=w[i]*dist[i];
		if(res>ans) return res;
	}
	return res;
}

int main()
{
	fstream fin("butter.in",ios::in);
	fstream fout("butter.out",ios::out);

	int tmp;
	fin>>n>>p>>m;
	for(int i=0;i<n;i++)
	{
		fin>>tmp;
		w[tmp]++;
	}

	for(int i=1;i<=p;i++)
		head[i]=-1;

	int a,b,c;
	for(int i=1;i<=m;i++)
	{
		fin>>a>>b>>c;
		next_edge[i<<1]=head[a]; head[a]=i<<1; en[i<<1]=b;
		next_edge[(i<<1)+1]=head[b]; head[b]=(i<<1)+1; en[(i<<1)+1]=a;
		len[i<<1]=len[(i<<1)+1]=c;
	}

	for(int i=1;i<=p;i++)
	{
		spfa(i);
		tmp=get_sum();
		ans=tmp<ans ? tmp:ans;
	}

	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}