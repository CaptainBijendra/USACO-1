/*
ID: suzyzha1
PROG: cowcycle
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int f,r,f1,f2,r1,r2,tot;
int front[6],rear[12];

double ans;
int ans_front[6],ans_rear[12];

double ratios[60],diff[60],mean,var;

void update()
{
	int k=1;
	for(int i=1;i<=f;i++)
		for(int j=1;j<=r;j++)
		{
			ratios[k]=1.0*front[i]/rear[j];
			k++;
		}

	double tmp;	
	for(int i=1;i<tot;i++)
		for(int j=1;j<=tot-i;j++)
			if(ratios[j]>ratios[j+1])
			{
				tmp=ratios[j]; ratios[j]=ratios[j+1]; ratios[j+1]=tmp;
			}

	mean=0;
	for(int i=1;i<tot;i++)
	{
	 	diff[i]=ratios[i+1]-ratios[i];
	 	mean+=diff[i];
	}
	mean/=(tot-1);

	var=0;
	for(int i=1;i<tot;i++)
		var+=(diff[i]-mean)*(diff[i]-mean);

	 if(var>ans) return;

	 ans=var;
	 for(int i=1;i<=f;i++) ans_front[i]=front[i];
	 for(int i=1;i<=r;i++) ans_rear[i]=rear[i];
}

void dfs2(int cur)
{
	if(cur>r)
	{
		if(rear[r]*front[f]-3*rear[1]*front[1]<0) return;

		update();
		return;
	}

	for(int i=rear[cur-1]+1;i<=r2;i++)
	{
		rear[cur]=i;
		dfs2(cur+1);
	}
}

void dfs1(int cur)
{
	if(cur>f)
	{
		dfs2(1);
		return;
	}

	for(int i=front[cur-1]+1;i<=f2;i++)
	{
		front[cur]=i;
		dfs1(cur+1);
	}
}

int main()
{
	fstream fin("cowcycle.in",ios::in);
	fstream fout("cowcycle.out",ios::out);

	fin>>f>>r;
	fin>>f1>>f2>>r1>>r2;

	tot=f*r;
	front[0]=f1-1;
	rear[0]=r1-1;

	ans=1e20;
	dfs1(1);
	
	for(int i=1;i<f;i++) fout<<ans_front[i]<<" ";
	fout<<ans_front[f]<<endl;
	for(int i=1;i<r;i++) fout<<ans_rear[i]<<" ";
	fout<<ans_rear[r]<<endl;
	fin.close();
	fout.close();
	return 0;
}