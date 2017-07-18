/*
ID: suzyzha1
PROG: maze1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;

const char dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};

char board[12][12];

int width,height;
string maze[210];
int dist[2][102][40],exits[2][2],num=0;
bool vis[102][40];
int qu[4000][2],head,tail;

void bfs(int sx,int sy,int time)
{
	int x,y,tx,ty;

	head=0; tail=1;
	qu[0][0]=sx;
	qu[0][1]=sy;
	vis[sx][sy]=true;
	dist[time][sx][sy]=1;

	while(head<tail)
	{
		x=qu[head][0];
		y=qu[head][1];
		head++;

		for(int i=0;i<4;i++)
		{
			tx=x+dir[i][0];
			ty=y+dir[i][1];
			if(tx<1 || ty<1 || tx>height || ty>width || vis[tx][ty]) continue;

			if(maze[2*x-1+dir[i][0]][2*y-1+dir[i][1]]!=' ') continue;

			qu[tail][0]=tx;
			qu[tail][1]=ty;
			tail++;
			vis[tx][ty]=true;
			dist[time][tx][ty]=dist[time][x][y]+1;
		}
	}

}

int main()
{
	fstream fin("maze1.in",ios::in);
	fstream fout("maze1.out",ios::out);

	fin>>width>>height;
	getline(fin,maze[0]);
	for(int i=0;i<2*height+1;i++)
		getline(fin,maze[i]);

	fin.close();

	for(int j=0;j<2*width+1;j++)
	{
		if(maze[0][j]==' ')
		{
			exits[num][0]=1;
			exits[num][1]=(j+1)/2;
			num++;
			if(num==2) break;
		}
		if(maze[2*height][j]==' ')
		{
			exits[num][0]=height;
			exits[num][1]=(j+1)/2;
			num++;
			if(num==2) break;
		}
	}

	if(num<2)
		for(int i=0;i<2*height+1;i++)
		{
			if(maze[i][0]==' ')
			{
				exits[num][0]=(i+1)/2;
				exits[num][1]=1;
				num++;
				if(num==2) break;
			}
			if(maze[i][2*width]==' ')
			{
				exits[num][0]=(i+1)/2;
				exits[num][1]=width;
				num++;
				if(num==2) break;
			}
		}
	
	bfs(exits[0][0],exits[0][1],0);

	memset(vis,0,sizeof(vis));
	bfs(exits[1][0],exits[1][1],1);

	int k,ans=1;
	for(int i=1;i<=height;i++)
		for(int j=1;j<=width;j++)
		{
			k=dist[0][i][j]<dist[1][i][j] ? dist[0][i][j]:dist[1][i][j];
			ans=k>ans ? k:ans;
		}

	fout<<ans<<endl;
	fout.close();
	return 0;
}