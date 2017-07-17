/*
ID: suzyzha1
PROG: ttwo
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;

const char dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};

char board[12][12];

struct Position
{
	int x,y,d;
	// bool operator==(const Position &b)
	// {
	// 	return (x==b.x && y==b.y && d==b.d);
	// }
} farmer,cows;

int vis_farmer[12][12][4],vis_cows[12][12][4];

Position get_next(Position cur)
{
	Position res;
	int x,y;
	x=cur.x+dir[cur.d][0];
	y=cur.y+dir[cur.d][1];
	if(x<0 || y<0 || x>9 || y>9 || board[x][y]=='*')
	{
		res=cur;
		res.d=(cur.d+1)%4;
	}
	else
	{
		res.x=x;
		res.y=y;
		res.d=cur.d;
	}
	return res;
}

int main()
{
	fstream fin("ttwo.in",ios::in);
	fstream fout("ttwo.out",ios::out);

	for(int i=0;i<10;i++)
		fin>>board[i];
	fin.close();

	int fx,fy,cx,cy,fd,cd;

	for(int i=0;i<10;i++)
		for(int j=0;j<10;j++)
			if(board[i][j]=='F')
			{
				farmer.x=i;
				farmer.y=j;
			}
			else
			if(board[i][j]=='C')
			{
				cows.x=i;
				cows.y=j;
			}

	farmer.d=cows.d=0;

	Position t1,t2;
	int time=0,max_time=INT_MAX,loop_time_farmer,loop_time_cow;
	vis_farmer[farmer.x][farmer.y][farmer.d]=vis_cows[cows.x][cows.y][cows.d]=1;
	while(true)
	{
		time++;
		t1=get_next(farmer);
		t2=get_next(cows);
		if(t1.x==t2.x && t1.y==t2.y)
		{
			fout<<time<<endl;
			break;
		}
		if(vis_farmer[t1.x][t1.y][t1.d] && vis_cows[t2.x][t2.y][t2.d] && max_time==INT_MAX)
		{
			loop_time_farmer=time-vis_farmer[t1.x][t1.y][t1.d];
			loop_time_cow=time-vis_cows[t2.x][t2.y][t2.d];
			max_time=time+loop_time_farmer*loop_time_cow;
		}
		if(time>max_time)
		{
			fout<<0<<endl;
			break;
		}
		farmer=t1;
		cows=t2;
		vis_farmer[farmer.x][farmer.y][farmer.d]=time+1;
		vis_cows[cows.x][cows.y][cows.d]=time+1;
	}

	fout.close();
	return 0;
}