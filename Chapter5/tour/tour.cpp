/*
ID: suzyzha1
PROG: tour
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
const int maxn = 102;

int n,m;
char city[maxn][20];
bool g[maxn][maxn];
int f[maxn][maxn];

int get_id(char *s)
{
	for(int i=1;i<=n;i++)
		if(strcmp(s,city[i])==0)
			return i;

	return 0;
}

int main()
{
	fstream fin("tour.in",ios::in);
	fstream fout("tour.out",ios::out);

	fin>>n>>m;
	for(int i=1;i<=n;i++)
		fin>>city[i];

	int x,y;
	char st[20],en[20];
	for(int i=0;i<m;i++)
	{
		fin>>st>>en;
		x=get_id(st);
		y=get_id(en);

		if(x<y) g[x][y]=true;
		else g[y][x]=true;
	}

	f[1][1]=1;
	int ans=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n;j++)
		{
			for(int k=1;k<j;k++)
				if(g[k][j])
				{
					if(k==i && i!=1) continue;

					if(f[i][k]>0 && f[i][k]+1>f[i][j])
						f[i][j]=f[i][k]+1;
				}

			f[j][i]=f[i][j];
		}

		if(i==n)
		{
			if(f[n][n]-1>ans)
				ans=f[n][n]-1;
		}
		else
		if(g[i][n] && f[i][n]>ans)
			ans=f[i][n];
	}
	
	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}