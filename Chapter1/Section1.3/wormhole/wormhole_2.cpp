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

const int maxn = 14;

int n;
int x[maxn],y[maxn];
int hole_pair[maxn],next_on_right[maxn];

int ans=0;

bool stuck()
{
	for(int i=1;i<=n;i++)
	{
		int pos=i;
		for(int j=0;j<n;j++)
			pos=next_on_right[hole_pair[pos]];

		if(pos!=0) return true;
	}

	return false;
}

void dfs(int cur,int n) 
{
	if(cur>n)
	{
		if(stuck())
			ans++;

		return;
	}

	if(hole_pair[cur]!=-1)
		dfs(cur+1,n);
	else
		for(int i=cur+1;i<=n;i++)
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
	for(int i=1;i<=n;i++)
		fin>>x[i]>>y[i];

	int tmp;
	for(int i=n;i>1;i--)
		for(int j=1;j<i;j++)
			if(y[j]>y[j+1] || (y[j+1]==y[j] && x[j]>x[j+1]))
			{
				tmp=y[j+1]; y[j+1]=y[j]; y[j]=tmp;
				tmp=x[j+1]; x[j+1]=x[j]; x[j]=tmp;
			}
	
	for(int i=1;i<n;i++)
		if(y[i]==y[i+1] && x[i]<=x[i+1])
			next_on_right[i]=i+1;
		
	memset(hole_pair,-1,sizeof(hole_pair));
	dfs(1,n);
	
	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}
