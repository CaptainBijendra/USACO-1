/*
ID: suzyzha1
PROG: fence6
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int maxn = 102;
const int maxm = 202;
const int maxd = 30000;

int n,m;
int v[maxn][2][10],len[maxn];
int g[maxm][maxm],dist[maxm][maxm];


int main()
{
	fstream fin("fence6.in",ios::in);
	fstream fout("fence6.out",ios::out);

	fin>>n;
	m=n<<1;
	for(int i=1;i<m;i++)
		for(int j=i+1;j<=m;j++)
			g[i][j]=g[j][i]=maxd;

	for(int i=0;i<n;i++)
	{
		int s;
		fin>>s;
		fin>>len[s];
		int a = s<<1;
		int b = a-1;
		g[a][b]=g[b][a]=len[s];

		fin>>v[s][0][0]>>v[s][1][0];
		for(int j=1;j<=v[s][0][0];j++)
			fin>>v[s][0][j];
		
		for(int j=1;j<=v[s][1][0];j++)
			fin>>v[s][1][j];
	}

	for(int i=1;i<=n;i++)
		for(int k=0;k<=1;k++)
		{
			int s = (i<<1)-1+k ,t;
			int sum = v[i][k][0];
			for(int j=1;j<=sum;j++)
			{
				int cur = v[i][k][j];
				bool flag=false;
				for(int p=1;p<=v[cur][0][0];p++)
					if(v[cur][0][p]==i)
					{
						flag=true;
						break;
					}

				if(flag) t=(cur<<1)-1;
				else t=cur<<1;

				g[s][t]=g[t][s]=0;
			}
		}

	for(int i=1;i<=m;i++)
		for(int j=1;j<=m;j++)
			dist[i][j]=g[i][j];
	
	int ans=maxd;
	for(int k=1;k<=m;k++)
	{
		for(int i=1;i<k-1;i++)
			for(int j=i+1;j<k;j++)
			{
				int tmp = g[k][i]+dist[i][j]+g[j][k];
				if(tmp==0) continue;
				ans=tmp<ans ? tmp:ans;
			}

		for(int i=1;i<=m;i++)
			if(i!=k)
				for(int j=1;j<=m;j++)
					if(j!=i && j!=k)
					{
						int tmp = dist[i][k]+dist[k][j];
						dist[i][j]=tmp<dist[i][j] ? tmp:dist[i][j];
					}
	}
	
	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}