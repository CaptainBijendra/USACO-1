/*
ID: suzyzha1
PROG: stall4
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int maxn = 202;

int n,m;
int v[maxn][maxn],match[maxn],vis[maxn],res[maxn];

bool find_match(int cur)
{
	int t;
	for(int i=1;i<=v[cur][0];i++)
	{
		t=v[cur][i];
		if(vis[t]) continue;

		vis[t]=true;
		if(res[t]==0 || find_match(res[t]))
		{
			res[t]=cur;
			return true;
		}
	}
	return false;
}

int main()
{
	fstream fin("stall4.in",ios::in);
	fstream fout("stall4.out",ios::out);

	fin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		fin>>v[i][0];
		for(int j=1;j<=v[i][0];j++)
			fin>>v[i][j];
	}
	
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		if(find_match(i))
			ans++;
	}

	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}