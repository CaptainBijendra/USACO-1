/*
ID: suzyzha1
PROG: fence4
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;
const int maxn = 210;
const double small = 1e-2;

int n;
struct Point
{
	int x,y;
} vertice[maxn],observer;

struct Vec
{
	int x,y;
	Vec(Point &a,Point &b) { x=b.x-a.x; y=b.y-a.y; }
};

int idx[maxn];
bool visable[maxn];
int num=0,ans[maxn];

bool diff_side(int a,int b)
{
	Vec u(vertice[a],vertice[a+1]);
	Vec v(vertice[a],vertice[b]);
	Vec w(vertice[a],vertice[b+1]);

	int c1 = u.x*v.y - u.y*v.x;
	int c2 = u.x*w.y - u.y*w.x;

	if(c1==0 || c2==0) return false;
	if(c1<0 && c2<0) return false;
	if(c1>0 && c2>0) return false;

	return true;
}

bool angle_cmp(int a,int b)
{
	Vec u(observer,vertice[a]);
	Vec v(observer,vertice[b]);

	double c1 = atan2(u.y,u.x);
	double c2 = atan2(v.y,v.x);

	if(c1<c2) return true;
	return false;
}

int main()
{
	fstream fin("fence4.in",ios::in);
	fstream fout("fence4.out",ios::out);

	fin>>n;
	fin>>observer.x>>observer.y;

	for(int i=1;i<=n;i++) fin>>vertice[i].x>>vertice[i].y;

	fin.close();

	vertice[n+1]=vertice[1];

	bool flag=true;
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
		{
			if(diff_side(i,j) && diff_side(j,i))
			{
				flag=false;
				break;
			}			
		}

	if(!flag)
	{
		fout<<"NOFENCE"<<endl;
		fout.close();
		return 0;
	}

	for(int i=1;i<=n;i++)
		idx[i]=i;
	
	sort(idx+1,idx+n+1,angle_cmp);
	idx[n+1]=idx[1];

	for(int i=1;i<=n;i++)
	{
		vertice[i].x-=observer.x;
		vertice[i].y-=observer.y;
	}
	vertice[n+1]=vertice[1];

	int best;
	double mx,my,k,k2,x,y,mind2;
	bool vertical,horizontal;

for(int times=-1;times<=1;times+=2)
{
	for(int i=1;i<=n;i++)
	{
		int a = idx[i];
		int b = idx[i+1];

		if(vertice[a].x*vertice[b].y-vertice[a].y*vertice[b].x==0)
			continue;

		mx = (double)(vertice[a].x+vertice[b].x)/2 + times*small;
		my = (double)(vertice[a].y+vertice[b].y)/2 + times*small;
		if(fabs(mx)>1e-8)
		{
			k = my/mx;
			vertical = false;
		}
		else
		{
			vertical = true;
			k=0;
		}

		if(fabs(my)<1e-8)
			horizontal = true;
		else
			horizontal = false;

		bool flag=false;
		for(int j=1;j<=n;j++)
		{
			double c1 = mx*vertice[j].y - my*vertice[j].x;
			double c2 = mx*vertice[j+1].y - my*vertice[j+1].x;
			
			if(c1<1e-8 && c2<1e-8) continue;
			if(c1>-1e-8 && c2>-1e-8) continue;
			
			if(vertice[j].x==vertice[j+1].x)
			{
				x=vertice[j].x;
				y=k*x;
			}
			else
			{
				k2 = 1.0*(vertice[j+1].y-vertice[j].y)/(vertice[j+1].x-vertice[j].x);

				if(vertical)
				{
					x = mx;
					y = k2*(x-vertice[j].x)+vertice[j].y;
				}
				else
				{
					x = vertice[j].y - k2*vertice[j].x;
					x /= (k-k2);
					y = k*x;					
				}
			}

			
			if(horizontal)
			{
				if(x>1e-8 && mx<-1e-8) continue;
				if(x<-1e-8 && mx>1e-8) continue;
			}
			else
			{
				if(y>1e-8 && my<-1e-8) continue;
				if(y<-1e-8 && my>1e-8) continue;				
			}

			if(!flag)
			{
				flag=true;
				mind2 = x*x + y*y;
				best = j;
			}
			else
			{
				double tmp = x*x + y*y;
				if(tmp<mind2)
				{
					best=j;
					mind2=tmp;
				}
			}
		}

		if(flag)
			visable[best]=true;
	}
}

	num=0;	
	for(int i=1;i<=n-2;i++)
		if(visable[i])
		{
			num++;
			ans[num]=i;
		}

	for(int i=n;i>=n-1;i--)
		if(visable[i])
		{
			num++;
			ans[num]=i;
		}

	for(int i=1;i<=n;i++)
	{
		vertice[i].x+=observer.x;
		vertice[i].y+=observer.y;
	}

	fout<<num<<endl;
	for(int i=1;i<=num;i++)
		if(i==1 || ans[i]!=ans[i-1])
		{
			int cur=ans[i];
			if(cur<n)
				fout<<vertice[cur].x<<" "<<vertice[cur].y<<" "<<vertice[cur+1].x<<" "<<vertice[cur+1].y<<endl;
			else
				fout<<vertice[1].x<<" "<<vertice[1].y<<" "<<vertice[n].x<<" "<<vertice[n].y<<endl;
		}

	fout.close();
	return 0;
}