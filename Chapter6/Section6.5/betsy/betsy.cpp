/*
ID: suzyzha1
PROG: betsy
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int n,tot,ans=0;
const int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

bool g[9][9];

int count_around(int x,int y)
{
	int around=0;
	for(int i=0;i<4;i++)
	{
		int tx=x+dir[i][0];
		int ty=y+dir[i][1];

		if(!g[tx][ty])
			around++;
	}
	return around;
}

void dfs(int x,int y,int sum)
{
	if(x==n && y==1)
	{
		if(sum==tot)
			ans++;

		return;
	}

	int vertical=0,horizontal=0;
	int necessary=0,nx,ny;

	for(int i=0;i<4;i++)
	{
		int tx=x+dir[i][0];
		int ty=y+dir[i][1];
		if(g[tx][ty]) continue;

		if(i<2) horizontal++;
		else vertical++;

		if(tx==n && ty==1) continue;
		int tmp=count_around(tx,ty);
		if(tmp<2)
		{
			necessary++;
			nx=tx;
			ny=ty;
		}
	}
	if(horizontal==2 && vertical==0) return;
	if(horizontal==0 && vertical==2) return;

	if(necessary>1) return;

	if(necessary==0)
	{
		for(int i=0;i<4;i++)
		{
			int tx=x+dir[i][0];
			int ty=y+dir[i][1];

			if(g[tx][ty]) continue;

			g[tx][ty]=true;
			dfs(tx,ty,sum+1);
			g[tx][ty]=false;
		}
	}
	else /* necessary==1 */
	{
		g[nx][ny]=true;
		dfs(nx,ny,sum+1);
		g[nx][ny]=false;
	}
}

int main()
{
	fstream fin("betsy.in",ios::in);
	fstream fout("betsy.out",ios::out);

	fin>>n;
	tot=n*n;

	for(int i=1;i<=n;i++)
		g[0][i]=g[i][0]=g[n+1][i]=g[i][n+1]=true;

	g[1][1]=true;
	dfs(1,1,1);

	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}