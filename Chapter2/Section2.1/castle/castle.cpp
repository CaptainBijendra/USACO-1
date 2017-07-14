/*
ID: suzyzha1
PROG: castle
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

/*
1: wall to the west
2: wall to the north
4: wall to the east
8: wall to the south
*/
const int dir[4][2]={{0,-1},{-1,0},{0,1},{1,0}};

const int maxn = 52;
int m,n;
int floorplan[maxn][maxn];

int num_of_rooms=0;
int size[maxn*maxn];
int co[maxn][maxn];

int color_room(int x,int y,int cur_color)
{
	co[x][y]=cur_color;

	int sum=1,tx,ty;
	for(int k=0;k<4;k++)
		if((floorplan[x][y]&(1<<k))==0)
		{
			tx=x+dir[k][0];
			ty=y+dir[k][1];
			if(tx<1 || ty<1 || tx>n || ty>m || co[tx][ty]>0) continue;

			sum+=color_room(tx,ty,cur_color);
		}

	return sum;
}

int main()
{
	fstream fin("castle.in",ios::in);
	fstream fout("castle.out",ios::out);

	fin>>m>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			fin>>floorplan[i][j];

	fin.close();

	int max_size=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(co[i][j]==0)
			{
				num_of_rooms++;
				size[num_of_rooms]=color_room(i,j,num_of_rooms);
				if(size[num_of_rooms]>max_size) max_size=size[num_of_rooms];
			}

	int tx,ty;
	int new_max_size=0,wall_dir,module_x,module_y;
	for(int j=1;j<=m;j++)
		for(int i=n;i>=1;i--)
		{
			for(int k=1;k<=2;k++)
				if((floorplan[i][j]&(1<<k))>0)
				{
					tx=i+dir[k][0];
					ty=j+dir[k][1];
					if(tx<1 || ty<1 || tx>n || ty>m || co[tx][ty]==co[i][j]) continue;
					if(size[co[i][j]]+size[co[tx][ty]]>new_max_size)
					{
						new_max_size=size[co[i][j]]+size[co[tx][ty]];
						module_x=i;
						module_y=j;
						wall_dir=k;
					}
				}
		}

	fout<<num_of_rooms<<endl;
	fout<<max_size<<endl;
	fout<<new_max_size<<endl;

	if(wall_dir==1) fout<<module_x<<" "<<module_y<<" N"<<endl;
	else fout<<module_x<<" "<<module_y<<" E"<<endl;

	fout.close();
	return 0;
}
