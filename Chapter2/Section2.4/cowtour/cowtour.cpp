/*
ID: suzyzha1
PROG: cowtour
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <cmath>
#include <iomanip>

using namespace std;
const int maxn = 152;
const double maxd = 1e12;

int n;
int location[maxn][2];
double point_dist[maxn][maxn],dist[maxn][maxn],max_dist[maxn],block_diameter[maxn];
bool adjacency[maxn][maxn];

int num=0,co[maxn],co_size[maxn],co_idx[maxn][maxn];

int color(int cur)
{
	if(co[cur]>0) return 0;
	co[cur]=num;

	int res=1;
	for(int i=0;i<n;i++)
		if(adjacency[cur][i] && co[i]<0)
			res+=color(i);
	return res;
}

void floyd()
{
	double tmp;
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
			if(i!=k)
			for(int j=0;j<n;j++)
				if(j!=i && j!=k)
					if(dist[i][k]<maxd-1e-4 && dist[k][j]<maxd-1e-4)
					{
						tmp=dist[i][k]+dist[k][j];
						if(dist[i][j]>tmp) dist[i][j]=tmp;
					}	
}

int main()
{
	fstream fin("cowtour.in",ios::in);
	fstream fout("cowtour.out",ios::out);

	fin>>n;
	for(int i=0;i<n;i++) fin>>location[i][0]>>location[i][1];

	string tmp;
	for(int i=0;i<n;i++)
	{
		fin>>tmp;
		for(int j=0;j<n;j++)
			adjacency[i][j]=tmp[j]-'0';
	}

	double k;
	for(int i=0;i<n;i++)
	{
		dist[i][i]=point_dist[i][i]=0;
		for(int j=i+1;j<n;j++)
		{
			k=(double)location[i][0]-location[j][0];
			point_dist[i][j]=k*k;
			k=(double)location[i][1]-location[j][1];
			point_dist[i][j]+=k*k;
			point_dist[i][j]=sqrt(point_dist[i][j]);
			point_dist[j][i]=point_dist[i][j];

			if(adjacency[i][j])
				dist[i][j]=dist[j][i]=point_dist[i][j];
			else
				dist[i][j]=dist[j][i]=maxd;
		}
	}

	memset(co,-1,sizeof(co));
	for(int i=0;i<n;i++)
		if(co[i]<0)
		{
			num++;
			co_size[num]=color(i);
		}

	floyd();

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(i!=j && co[i]==co[j])
			{
				block_diameter[co[i]]=dist[i][j]>block_diameter[co[i]] ? dist[i][j]:block_diameter[co[i]];
				max_dist[i]=dist[i][j]>max_dist[i] ? dist[i][j]:max_dist[i];
			}

	double ans=maxd,diameter;
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
			if(co[i]!=co[j])
			{
				diameter=max_dist[i]+point_dist[i][j]+max_dist[j];
				if(diameter>ans) continue;
				for(int k=1;k<=num;k++)
					if(block_diameter[k]>diameter)
						diameter=block_diameter[k];
				ans=diameter;				
			}

	fout<<fixed;
	fout<<setprecision(6)<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}