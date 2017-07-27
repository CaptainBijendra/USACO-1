/*
ID: suzyzha1
PROG: fence6
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <climits>

using namespace std;

const int maxn = 102;
const int maxm = 202;
const int maxd = 300;

int n,m,ans;
int init_g[maxm][maxm],g[maxm][maxm];
int f[maxm],idx[maxm],new_id[maxm],dist[maxm][maxm];

int find_f(int cur)
{
	if(cur==f[cur]) return cur;
	f[cur]=find_f(f[cur]);
	return f[cur];
}

void union_v(int a,int b)
{
	int x=find_f(a);
	int y=find_f(b);
	if(x==y) return;
	f[x]=y;
}

int main()
{
	fstream fin("fence6.in",ios::in);
	fstream fout("fence6.out",ios::out);

	fin>>n;
	m=n<<1;
	for(int i=1;i<m;i++)
		for(int j=i+1;j<=m;j++)
			g[i][j]=g[j][i]=maxd;

	for(int i=1;i<=m;i++)
		f[i]=i;

	int s;
	for(int i=0;i<n;i++)
	{
		fin>>s;
		fin>>len[s];

		fin>>n1>>n2;
		for(int j=0;j<n1;j++)
			fin>>v[s][0][j];
		
		for(int j=0;j<n2;j++)
		{
			fin>>v[s][1][j];
			dir[s][j]=true;
		}
	}
	

	idx[0]=0;
	for(int i=1;i<=m;i++)
		if(find_f(i)==i)
		{
			idx[0]++;
			idx[idx[0]]=i;
			new_id[i]=idx[0];
		}
	m=idx[0];	

	ans=INT_MAX;
	for(int k=1;k<=m;k++)
	{
		for(int i=1;i<k-1;i++)
			for(int j=i+1;j<k;j++)
				ans=min(ans,g[k][i]+dist[i][j]+g[j][k]);

		for(int i=1;i<=m;i++)
			if(i!=k)
				for(int j=1;j<=m;j++)
					if(j!=i && j!=k)
						dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
	}
	
	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}