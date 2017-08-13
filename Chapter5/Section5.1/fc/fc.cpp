/*
ID: suzyzha1
PROG: fc
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;
const int maxn = 10002;

int n;
struct Spot
{
	double x,y;
} spots[maxn];

int top,stack[maxn];

/* Cross product of vector a and b. Vector a starts at spots[st1], ends at spots[en1]. */
double cross_product(int st1,int en1,int st2,int en2) 
{
	double ax = spots[en1].x-spots[st1].x;
	double ay = spots[en1].y-spots[st1].y;
	double bx = spots[en2].x-spots[st2].x;
	double by = spots[en2].y-spots[st2].y;
	return ax*by-bx*ay;
}

bool cmp(const Spot &a,const Spot &b)
{
	double ax = a.x-spots[1].x;
	double ay = a.y-spots[1].y;
	double bx = b.x-spots[1].x;
	double by = b.y-spots[1].y;
	return ax*by-bx*ay>1e-10;
}

void graham_scan()
{
	top=3;
	stack[1]=1; stack[2]=2; stack[3]=3;

	for(int i=4;i<=n;i++)
	{
		while(top>=3 && cross_product(stack[top-1],stack[top],stack[top],i)<1e-10)
			top--;

		top++;
		stack[top]=i;
	}
}

double dist(int a,int b)
{
	double x = spots[b].x-spots[a].x;
	double y = spots[b].y-spots[a].y;
	return sqrt(x*x+y*y);
}

int main()
{
	fstream fin("fc.in",ios::in);
	fstream fout("fc.out",ios::out);

	fin>>n;
	int j=1;
	for(int i=1;i<=n;i++)
	{
		fin>>spots[i].x>>spots[i].y;
		if(i>1)
			if(spots[i].x<spots[j].x || (fabs(spots[i].x-spots[j].x)<1e-10 && spots[i].y<spots[j].y))
				j=i;
	}
	Spot tmp;
	tmp=spots[j]; spots[j]=spots[1]; spots[1]=tmp;

	sort(spots+2,spots+n+1,cmp);

	graham_scan();

	double ans=0;
	for(int i=1;i<top;i++)
		ans+=dist(stack[i],stack[i+1]);
	ans+=dist(stack[1],stack[top]);

	fout<<std::fixed<<std::setprecision(2)<<ans<<endl;

	fin.close();
	fout.close();
	return 0;
}