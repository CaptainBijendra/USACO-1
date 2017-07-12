/*
ID: suzyzha1
PROG: wormhole
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 12;
const int maxw = 145;

int n;
int x[maxn],y[maxn];
int hole_pair[maxn];
bool flag;
bool map[maxw][maxw];

int ans=0;

bool loop(int cur,int start,bool into) /* if into is true, 
					then the cow is going to go into the hole at cur */
{
	if(flag && cur==start && !into) return true;

	flag=true;
	if(!into)
	{
		if(cur<n-1 && map[cur][cur+1])
			return loop(cur+1,start,true);
		else
			return false;
	}
	else
		return loop(hole_pair[cur],start,false);
}

bool stuck()
{
	for(int i=0;i<n;i++)
	{
		flag=false;
		if(loop(i,i,false))
			return true;
	}

	return false;
}

void dfs(int cur,int n) 
{
	if(cur>=n)
	{
		if(stuck())
			ans++;

		return;
	}

	if(hole_pair[cur]!=-1)
		dfs(cur+1,n);
	else
		for(int i=cur+1;i<n;i++)
			if(hole_pair[i]==-1)
			{
				hole_pair[i]=cur;
				hole_pair[cur]=i;
				dfs(cur+1,n);
				hole_pair[i]=hole_pair[cur]=-1;
			}
}

int main()
{
	fstream fin("wormhole.in",ios::in);
	fstream fout("wormhole.out",ios::out);

	fin>>n;
	for(int i=0;i<n;i++)
		fin>>x[i]>>y[i];

	int tmp;
	for(int i=n-1;i>0;i--)
		for(int j=0;j<i;j++)
			if(y[j]>y[j+1] || (y[j+1]==y[j] && x[j]>x[j+1]))
			{
				tmp=y[j+1]; y[j+1]=y[j]; y[j]=tmp;
				tmp=x[j+1]; x[j+1]=x[j]; x[j]=tmp;
			}
	
	for(int i=0;i<n-1;i++)
		if(y[i]==y[i+1] && x[i]<=x[i+1])
			map[i][i+1]=true;
		
	memset(hole_pair,-1,sizeof(hole_pair));
	dfs(0,n);
	
	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}
