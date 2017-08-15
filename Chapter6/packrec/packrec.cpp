/*
ID: suzyzha1
PROG: packrec
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

struct Rectangular
{
	int x,y;
	bool operator == (const Rectangular &b)
	{
		if(x==b.x && y==b.y) return true;
		else return false;
	}
} backup[4],rec[4],best[1000];

bool used[4];
int now[4],dir[4];

int ans,num;

void get_area(int layout)
{
	int x=0,y=0;
	switch(layout)
	{
		case 0:
			for(int i=0;i<4;i++)
			{
				x+=rec[i].x;
				y=max(y,rec[i].y);
			}
			break;
		case 1:
			for(int i=1;i<4;i++)
			{
				x+=rec[i].x;
				y=max(y,rec[i].y);
			}
			x=max(x,rec[0].x);
			y+=rec[0].y;
			break;
		case 2:
			x=max(rec[0].x+rec[1].x,rec[3].x)+rec[2].x;
			y=max(rec[2].y,rec[3].y+max(rec[0].y,rec[1].y));
			break;
		case 3:
			x=rec[0].x+max(rec[1].x,rec[2].x)+rec[3].x;
			y=max(rec[0].y,rec[3].y);
			y=max(y,rec[1].y+rec[2].y);
			break;
		case 4:
			x=max(rec[0].x,rec[1].x)+rec[2].x+rec[3].x;
			y=max(rec[2].y,rec[3].y);
			y=max(y,rec[0].y+rec[1].y);
			break;
		case 5:
			y=max(rec[0].y+rec[1].y,rec[2].y+rec[3].y);
			x=max(rec[0].x+rec[2].x,rec[1].x+rec[3].x);
			if(rec[1].y>rec[3].y)
			{
				x=max(x,rec[1].x+rec[2].x);
			}
			else
			if(rec[1].y<rec[3].y)
			{
				x=max(x,rec[0].x+rec[3].x);
			}
			
			break;
	}

	if(ans<0 || x*y<ans)
	{
		ans=x*y;
		best[0].x=x<y ? x:y;
		best[0].y=x<y ? y:x;	
		num=1;
	}
	else
	if(x*y==ans)
	{
		best[num].x=x<y ? x:y;
		best[num].y=x<y ? y:x;	
		num++;
	}
}

void dfs(int cur,int layout)
{
	if(cur==4)
	{
		for(int i=0;i<4;i++)
			rec[i]=backup[now[i]];

		get_area(layout);
		return;
	}

	for(int i=0;i<4;i++)
		if(!used[i])
		{
			now[cur]=i;
			used[i]=true;
			dfs(cur+1,layout);
			used[i]=false;
		}
}

bool cmp(const Rectangular &a,const Rectangular &b)
{
	if(a.x<b.x) return true;
	if(a.x>b.x) return false;
	if(a.y<b.y) return true;
	return false;
}

int main()
{
	fstream fin("packrec.in",ios::in);
	fstream fout("packrec.out",ios::out);

	for(int i=0;i<4;i++)
	{
		fin>>rec[i].x>>rec[i].y;
		backup[i]=rec[i];
	}

	ans=-1; num=0;
	int tmp;
	for(int a=0;a<2;a++)
	{
		for(int b=0;b<2;b++)
		{
			for(int c=0;c<2;c++)
			{
				for(int d=0;d<2;d++)
				{
					for(int i=0;i<6;i++)
						dfs(0,i);

					tmp=backup[3].x; backup[3].x=backup[3].y; backup[3].y=tmp;
				}
				tmp=backup[2].x; backup[2].x=backup[2].y; backup[2].y=tmp;
			}
			tmp=backup[1].x; backup[1].x=backup[1].y; backup[1].y=tmp;
		}
		tmp=backup[0].x; backup[0].x=backup[0].y; backup[0].y=tmp;
	}

	sort(best,best+num,cmp);

	fout<<ans<<endl;
	for(int i=0;i<num;i++)
		if(i==0 || !(best[i]==best[i-1]))
			fout<<best[i].x<<" "<<best[i].y<<endl;

	fin.close();
	fout.close();
	return 0;
}