/*
ID: suzyzha1
PROG: rect1
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int n,m,tot;
struct Rectangle
{
	int x1,x2,y1,y2,color;
} rect[1002];

int color_count[2502];

void float_up(int cur,int x1,int y1,int x2,int y2,int co)
{
	if(cur>tot)
	{
		if(y2>y1 && x2>x1)
			color_count[co]+=(y2-y1)*(x2-x1);
		return;
	}

	if(y1>=rect[cur].y2 || y2<=rect[cur].y1 || x1>=rect[cur].x2 || x2<=rect[cur].x1)
	{
		float_up(cur+1,x1,y1,x2,y2,co);
		return;
	}

	if(y2>rect[cur].y2)
	{
		float_up(cur+1,x1,rect[cur].y2,x2,y2,co);
		y2=rect[cur].y2;
	}
	if(y1<rect[cur].y1)
	{
		float_up(cur+1,x1,y1,x2,rect[cur].y1,co);
		y1=rect[cur].y1;
	}

	if(x1<rect[cur].x1) float_up(cur+1,x1,y1,rect[cur].x1,y2,co);
	if(x2>rect[cur].x2) float_up(cur+1,rect[cur].x2,y1,x2,y2,co);
}

int main()
{
	fstream fin("rect1.in",ios::in);
	fstream fout("rect1.out",ios::out);

	fin>>n>>m>>tot;

	rect[0].x1=rect[0].y1=0;
	rect[0].x2=n;
	rect[0].y2=m;
	rect[0].color=1;

	int max_color=1;
	for(int i=1;i<=tot;i++)
	{
		fin>>rect[i].x1>>rect[i].y1>>rect[i].x2>>rect[i].y2>>rect[i].color;
		max_color=max_color>rect[i].color ? max_color:rect[i].color;
	}
	
	for(int i=0;i<=tot;i++)
		float_up(i+1,rect[i].x1,rect[i].y1,rect[i].x2,rect[i].y2,rect[i].color);
	
	for(int i=1;i<=max_color;i++)
		if(color_count[i]>0)
			fout<<i<<" "<<color_count[i]<<endl;

	fin.close();
	fout.close();
	return 0;
}