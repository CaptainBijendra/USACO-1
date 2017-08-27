/*
ID: suzyzha1
PROG: latin
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int n,tot;
long long ans=0;

int row_sum[8],col_sum[8];
bool row[8][8],col[8][8];

void dfs(int x,int y)
{
	int tmp;
	if(x>n-2)
	{
		ans++;
		return;
	}
	if(y==0)
	{
		row[x][x]=col[0][x]=true;
		row_sum[x]=x;
		col_sum[0]+=x;
		if(y<n-2) dfs(x,y+1);
		else dfs(x+1,0);

		row[x][x]=col[0][x]=false;
		row_sum[x]=0;
		col_sum[0]-=x;
		return;
	}

	for(int i=0;i<n;i++)
		if(row[x][i]==0 && col[y][i]==0)
		{
			if(y==n-2)
			{
				tmp=tot-row_sum[x]-i;
				if(col[n-1][tmp])
					continue;
			}
			if(x==n-2)
			{
				tmp=tot-col_sum[y]-i;
				if(row[n-1][tmp]) continue;
				row[n-1][tmp]=true;
			}
			if(y==n-2) col[n-1][tot-row_sum[x]-i]=true;

			row[x][i]=true;
			col[y][i]=true;
			row_sum[x]+=i;
			col_sum[y]+=i;

			if(y<n-2) dfs(x,y+1);
			else dfs(x+1,0);
			
			row[x][i]=false;
			col[y][i]=false;
			row_sum[x]-=i;
			col_sum[y]-=i;
			if(x==n-2)
				row[n-1][tot-col_sum[y]-i]=false;
			if(y==n-2)
				col[n-1][tot-row_sum[x]-i]=false;
		}
}

int main()
{
	fstream fin("latin.in",ios::in);
	fstream fout("latin.out",ios::out);

	fin>>n;
	tot=n*(n-1)/2;
	for(int i=0;i<n;i++)
		col[i]=1<<i;

	dfs(1,0);

	for(int i=1;i<n;i++)
		ans*=i;

	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}
