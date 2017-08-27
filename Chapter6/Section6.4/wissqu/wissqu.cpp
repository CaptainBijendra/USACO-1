/*
ID: suzyzha1
PROG: wissqu
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int dir[][2] = {{0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1},{-1,1},{-1,-1}};

int nums[5];

struct Square
{
	char s[4][4];
	bool changed[4][4];

	/*char ch;   */
	int x,y; /* position of last changed character */
} st,now[20];

int ans=0;
int plan[20][3];

void get_plan()
{
	for(int i=1;i<=16;i++)
	{
		plan[i][0]=now[i].s[now[i].x][now[i].y];
		plan[i][1]=now[i].x;
		plan[i][2]=now[i].y;
	}
}

bool check(int cur,int x,int y,char c)
{
	if(now[cur].s[x][y]==c) return false;

	int tx,ty;
	for(int i=0;i<8;i++)
	{
		tx=x+dir[i][0];
		if(tx<0 || tx>3) continue;
		ty=y+dir[i][1];
		if(ty<0 || ty>3) continue;

		if(now[cur].s[tx][ty]==c)
			return false;
	}
	return true;
}

void dfs(int cur)
{
	if(cur>16)
	{
		if(ans==0)
			get_plan();
		ans++;
		return;
	}

	for(int i=0;i<5;i++)
		if(nums[i]>0)
		{
			for(int j=0;j<4;j++)
				for(int k=0;k<4;k++)
					if(!now[cur-1].changed[j][k])
						if(check(cur-1,j,k,'A'+i))
						{
							now[cur]=now[cur-1];
							now[cur].s[j][k]='A'+i;
							now[cur].changed[j][k]=true;
							now[cur].x=j;
							now[cur].y=k;

							nums[i]--;
							dfs(cur+1);
							nums[i]++;
						}
		}
}

int main()
{
	fstream fin("wissqu.in",ios::in);
	fstream fout("wissqu.out",ios::out);

	for(int i=0;i<4;i++)
		fin>>st.s[i];

	now[0]=st;
	memset(now[0].changed,0,sizeof(now[0].changed));

	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(check(0,i,j,'D'))
			{
				now[1]=now[0];
				now[1].s[i][j]='D';
				now[1].changed[i][j]=true;
				now[1].x=i;
				now[1].y=j;
				for(int k=0;k<5;k++)
					nums[k]=3;
				dfs(2);
			}

	for(int i=1;i<=16;i++)
		fout<<(char)plan[i][0]<<" "<<plan[i][1]+1<<" "<<plan[i][2]+1<<endl;

	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}
