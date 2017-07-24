/*
ID: suzyzha1
PROG: fence
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;

const int maxn = 502;
const int maxf = 1030;

int f;
int d[maxn][maxn];
int map[maxn][maxn];

int Eulerian[maxf];

void dfs(int cur)
{
	for(int i=1;i<=d[cur][0];i++)
		if(map[cur][d[cur][i]])
		{
			map[cur][d[cur][i]]--;
			map[d[cur][i]][cur]--;
			dfs(d[cur][i]);
		}

	Eulerian[0]++;
	Eulerian[Eulerian[0]]=cur;
}

int main()
{
	fstream fin("fence.in",ios::in);
	fstream fout("fence.out",ios::out);

	fin>>f;
	int st,en;
	for(int i=0;i<f;i++)
	{
		fin>>st>>en;
		d[st][0]++;
		d[st][d[st][0]]=en;
		d[en][0]++;
		d[en][d[en][0]]=st;
		map[st][en]++;
		map[en][st]++;
	}

	int tmp;
	for(int i=1;i<=500;i++)
		if(d[i][0])
		{
			for(int j=d[i][0];j>1;j--)
				for(int k=1;k<j;k++)
					if(d[i][k]>d[i][k+1])
					{
						tmp=d[i][k]; d[i][k]=d[i][k+1]; d[i][k+1]=tmp;
					}
		}

	int start=0;
	for(int i=1;i<=500;i++)
		if(d[i][0]%2)
		{
			start=i;
			break;
		}

	if(start==0)
		for(int i=1;i<=500;i++)
			if(d[i][0])
			{
				start=i;
				break;
			}

	Eulerian[0]=0;
	dfs(start);

	for(int i=f+1;i>=1;i--)
		fout<<Eulerian[i]<<endl;
	
	fin.close();
	fout.close();
	return 0;
}