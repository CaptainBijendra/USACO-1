/*
ID: suzyzha1
PROG: snail
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;
const int maxn = 130;
const int dir[][2] = {{1,0},{0,1},{-1,0},{0,-1}};

int n,m,ans;
bool barrier[maxn][maxn],vis[maxn][maxn];

void dfs(int x,int y,int d,int len)
{
	int tx,ty;
	ans=len>ans ? len:ans;
	tx=x+dir[d][0];
	ty=y+dir[d][1];

	if(vis[tx][ty]) return;
	if(tx<1 || ty<1 || tx>n || ty>n || barrier[tx][ty])
	{
		for(int i=0;i<4;i++)
			if(i!=d)
			{
				tx=x+dir[i][0];
				ty=y+dir[i][1];
				if(tx<1 || ty<1 || tx>n || ty>n || barrier[tx][ty] || vis[tx][ty])
					continue;

				vis[tx][ty]=true;
				dfs(tx,ty,i,len+1);
				vis[tx][ty]=false;
			}
	}
	else
	{
		vis[tx][ty]=true;
		dfs(tx,ty,d,len+1);
		vis[tx][ty]=false;
	}
}

int main()
{
	fstream fin("snail.in",ios::in);
	fstream fout("snail.out",ios::out);

	int x,y;
	char tmp[50];

	fin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		fin>>tmp;
		y=tmp[0]-'A'+1;
		x=atoi(tmp+1);
		barrier[x][y]=true;
	}

	vis[1][1]=true;
	dfs(1,1,0,1);
	dfs(1,1,1,1);

	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}