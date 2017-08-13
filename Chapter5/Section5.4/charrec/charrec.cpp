/*
ID: suzyzha1
PROG: charrec
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;
const int tot = 27;
const int maxn = 1220;

char dict[tot][24][24];

int n;
char s[maxn][24];
int diff[maxn][tot+2][24],cost[maxn][tot+2][4];
int f[maxn],g[maxn],pre[maxn];

char ans[100];

int main()
{
	fstream fdict("font.in",ios::in);
	int tmp;
	fdict>>tmp;
	for(int i=0;i<tot;i++)
		for(int j=0;j<20;j++)
			fdict>>dict[i][j];

	fdict.close();
	fstream fin("charrec.in",ios::in);
	fstream fout("charrec.out",ios::out);	

	fin>>n;
	for(int i=1;i<=n;i++)
		fin>>s[i];
	
	/* diff[k][i][j]: difference between s[k] and dict[i][j] */
	for(int k=1;k<=n;k++)
		for(int i=0;i<tot;i++)
			for(int j=0;j<20;j++)
				for(int p=0;p<20;p++)
					if(s[k][p]!=dict[i][j][p])
						diff[k][i][j]++;

	int sum,sum2;
	for(int k=1;k<=n-18;k++)
		for(int i=0;i<tot;i++)
		{
			cost[k][i][0]=INT_MAX;
			for(int j=0;j<20;j++)
			{	
				sum=0;
				for(int p=0;p<j;p++)
					sum+=diff[k+p][i][p];
				for(int p=j+1;p<20;p++)
					sum+=diff[k+p-1][i][p];

				cost[k][i][0]=min(cost[k][i][0],sum);
			}
			///
			if(k>n-19) continue;
			cost[k][i][1]=0;
			for(int j=0;j<20;j++)
				cost[k][i][1]+=diff[k+j][i][j];

			///

			if(k>n-20) continue;
			cost[k][i][2]=INT_MAX;
			for(int j=0;j<20;j++)
			{
				sum=0;
				for(int p=0;p<j;p++)
					sum+=diff[k+p][i][p];
				for(int p=j+2;p<21;p++)
					sum+=diff[k+p][i][p-1];

				sum2=min(diff[k+j][i][j],diff[k+j+1][i][j]);
				cost[k][i][2]=min(cost[k][i][2],sum+sum2);
			}
		}

	for(int k=1;k<=n;k++) f[k]=INT_MAX;

	for(int k=0;k<=n-18;k++)
		if(f[k]!=INT_MAX)
		{
			for(int i=0;i<=2;i++)
			{
				if(k+19+i>n) break;

				int min=INT_MAX,idx=0;
				for(int j=0;j<tot;j++)
					if(cost[k+1][j][i]<min)
					{
						min=cost[k+1][j][i];
						idx=j;
					}

				if(min==INT_MAX) continue;
				if(f[k]+min<f[k+19+i])
				{
					f[k+19+i]=f[k]+min;
					g[k+19+i]=idx;
					pre[k+19+i]=k;
				}
			}
		}

	int i=n,count=0;
	while(i>0)
	{
		count++;
		ans[count]=(g[i]==0) ? ' ':(char)(g[i]+'a'-1);

		i=pre[i];
	}

	for(int i=count;i>=1;i--)
		fout<<ans[i];
	fout<<endl;
	fin.close();
	fout.close();
	return 0;
}