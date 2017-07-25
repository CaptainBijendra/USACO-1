/*
ID: suzyzha1
PROG: camelot
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <cmath>

using namespace std;

const int maxn = 32;
const int maxm = 28;
const int maxd = 4000;
const int dir[][2] = {{-1,-2},{-2,-1},{-2,1},{-1,2},{1,-2},{2,-1},{2,1},{1,2}};

int n,m,total,num=0,ans;
struct Coordinate
{
	int x,y;
} king,knight;

int king_dist[maxn][maxm],dist[maxn][maxm][2];

int cost[maxn][maxm],king_cost[maxn][maxm];

int move(int x,int y,int k)
{
	int tx,ty,f=0;

	for(int i=0;i<8;i++)
	{
		tx=x+dir[i][0];
		ty=y+dir[i][1];

		if(tx<1 || ty<1 || tx>n || ty>m) continue;

		if(dist[tx][ty][k]>dist[x][y][k]+1)
		{
			dist[tx][ty][k]=dist[x][y][k]+1;
			f=1;
		}
	}

	if(k==0 && dist[x][y][1]>dist[x][y][0]+king_dist[x][y])
	{
		dist[x][y][1]=dist[x][y][0]+king_dist[x][y];
		if(king_dist[x][y]>f) f=king_dist[x][y];
	}

	return f;
}

void calc_dist(int sx,int sy)
{
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			dist[i][j][0]=dist[i][j][1]=maxd;

	int maxd;
	dist[sx][sy][0]=0;
	maxd=dist[sx][sy][1]=king_dist[sx][sy];

	int flag;
	for(int d=0;d<=maxd;d++)
	{
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				if(dist[i][j][0]==d)
				{
					flag=move(i,j,0);
					if(d+flag>maxd) maxd=d+flag;
				}
				if(dist[i][j][1]==d)
				{
					flag=move(i,j,1);
					if(d+flag>maxd) maxd=d+flag;
				}
			}
	}
}

int main()
{
	fstream fin("camelot.in",ios::in);
	fstream fout("camelot.out",ios::out);

	int a;
	char b;
	fin>>n>>m;
	fin>>b>>a;
	king.x=a;
	king.y=b-'A'+1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			king_dist[i][j]=king_cost[i][j]=max(abs(i-king.x),abs(j-king.y));

	while(!fin.eof())
	{
		fin>>b>>a;
		if(fin.eof()) break;

		knight.x=a;
		knight.y=b-'A'+1;

		calc_dist(knight.x,knight.y);

		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++)
			{
				cost[i][j]+=dist[i][j][0];
				if(dist[i][j][1]-dist[i][j][0]<king_cost[i][j])
					king_cost[i][j]=dist[i][j][1]-dist[i][j][0];
			}
	}

	ans=INT_MAX;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(cost[i][j]+king_cost[i][j]<ans)
				ans=cost[i][j]+king_cost[i][j];

	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}