/*
ID: suzyzha1
PROG: job
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int maxm = 32;
const int maxn = 1002;

int n,m[2];
int t[2][maxm];
int delay[2][maxm],cost[2][maxn];

int main()
{
	fstream fin("job.in",ios::in);
	fstream fout("job.out",ios::out);

	fin>>n>>m[0]>>m[1];
	for(int i=0;i<=1;i++)
		for(int j=1;j<=m[i];j++)
			fin>>t[i][j];

	for(int k=0;k<=1;k++)
	{
		for(int i=1;i<=n;i++)
		{
			int mind=delay[k][1]+t[k][1];
			int best=1;
			for(int j=2;j<=m[k];j++)
				if(delay[k][j]+t[k][j]<mind)
				{
					mind=delay[k][j]+t[k][j];
					best=j;
				}

			delay[k][best]=cost[k][i]=mind;
		}
	}

	int maxt1=0,maxt2=0;
	for(int i=1;i<=n;i++)
	{
		maxt1=max(cost[0][i],maxt1);
		maxt2=max(cost[0][i]+cost[1][n+1-i],maxt2);
	}

	fout<<maxt1<<" "<<maxt2<<endl;
	fin.close();
	fout.close();
	return 0;
}