/*
ID: suzyzha1
PROG: starry
LANG: C++
*/

#include <iostream>
#include <fstream>


using namespace std;
const int maxn = 110;
const int dir[][2] = 	{{1,0},{0,1},{-1,0},{0,-1},
						{1,1},{1,-1},{-1,1},{-1,-1}};

int n,m;
char map[maxn][maxn];

int colors=0,co[maxn][maxn];
int num[510],stars[510][170][2];

int clusters=0,idx[510];

void dfs(int x,int y)
{
	co[x][y]=colors;
	num[colors]++;
	stars[colors][num[colors]][0]=x;
	stars[colors][num[colors]][1]=y;

	int tx,ty;
	for(int i=0;i<8;i++)
	{
		tx=x+dir[i][0];
		if(tx<0 || tx>=n) continue;
		ty=y+dir[i][1];
		if(ty<0 || ty>=m) continue;
		if(co[tx][ty] || map[tx][ty]=='0') continue;

		dfs(tx,ty);
	}
}

bool same(int a,int b)
{
	if(num[a]!=num[b]) return false;

	bool flag;
	for(int i=1;i<=num[a];i++)
	{
		flag=false;
		for(int j=1;j<=num[a];j++)
			if(stars[a][i][0]==stars[b][j][0] && stars[a][i][1]==stars[b][j][1])
			{
				flag=true;
				break;
			}
		if(!flag) return false;
	}
	return true;
}

void regulate(int cur)
{
	int x=stars[cur][1][0],y=stars[cur][1][1];
	for(int i=2;i<=num[cur];i++)
		if(stars[cur][i][0]<x || (stars[cur][i][0]==x && stars[cur][i][1]<y))
		{
			x=stars[cur][i][0];
			y=stars[cur][i][1];
		}

	for(int i=1;i<=num[cur];i++)
	{
		stars[cur][i][0]-=x;
		stars[cur][i][1]-=y;
	}
}

void rotate(int cur)
{
	int y;
	for(int i=1;i<=num[cur];i++)
	{
		y=n+1-stars[cur][i][0];
		stars[cur][i][0]=stars[cur][i][1];
		stars[cur][i][1]=y;
	}

	regulate(cur);
}

void mirror(int cur)
{
	for(int i=1;i<=num[cur];i++)
		stars[cur][i][1]=n+1-stars[cur][i][1];

	regulate(cur);
}

int main()
{
	fstream fin("starry.in",ios::in);
	fstream fout("starry.out",ios::out);

	fin>>m>>n;
	for(int i=0;i<n;i++)
		fin>>map[i];


	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(map[i][j]!='0' && co[i][j]==0)
			{
				colors++;
				dfs(i,j);
			}

	for(int i=1;i<=colors;i++)
	{
		int x=stars[i][1][0],y=stars[i][1][1];
		for(int j=1;j<=num[i];j++)
		{
			stars[i][j][0]-=x;
			stars[i][j][1]-=y;
		}
	}

	for(int i=1;i<=colors;i++)
		if(idx[i]==0)
		{
			clusters++;
			idx[i]=clusters;

			for(int k=0;k<8;k++)
			{
				for(int j=i+1;j<=colors;j++)
					if(idx[j]==0)
						if(same(i,j))
							idx[j]=clusters;

				if(k==3)
					mirror(i);
				else
					rotate(i);
			}
		}

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<m;j++)
			if(map[i][j]=='0')
				fout<<'0';
			else
				fout<<(char)('a'-1+idx[co[i][j]]);
		
		fout<<endl;
	}

	fin.close();
	fout.close();
	return 0;
}