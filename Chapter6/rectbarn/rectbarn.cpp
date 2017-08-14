/*
ID: suzyzha1
PROG: rectbarn
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
const int maxn = 3002;

int n,m;
bool broken[maxn][maxn];

/* le:left.  ri:right */
int height[maxn],le[maxn],ri[maxn];

int main()
{
	fstream fin("rectbarn.in",ios::in);
	fstream fout("rectbarn.out",ios::out);

	int a,b,p;
	fin>>n>>m>>p;
	for(int i=0;i<p;i++)
	{
		fin>>a>>b;
		broken[a][b]=true;
	}

	int ans=0,k;
	for(int i=1;i<=n;i++)
	{
		k=0;
		for(int j=1;j<=m;j++)
		{
			if(broken[i][j])
				le[j]=height[j]=k=0;
			else
			{
				k++;
				if(le[j]==0) le[j]=k;
				else le[j]=min(k,le[j]);
				
				height[j]++;
			}
		}

		k=0;
		for(int j=m;j>=1;j--)
		{
			if(broken[i][j])
			{
				ri[j]=k=0;
				continue;
			}
			else
			{
				k++;
				if(ri[j]==0) ri[j]=k; 
				else ri[j]=min(k,ri[j]);
				
				ans=max(ans,height[j]*(le[j]+ri[j]-1));
			}
		}
	}

	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}