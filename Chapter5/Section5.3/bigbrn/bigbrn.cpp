/*
ID: suzyzha1
PROG: bigbrn
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;
const int maxn = 1002;

int n,m,ans;
bool tree[maxn][maxn];
int f[maxn][maxn];

int min3(int a,int b,int c)
{
	if(a<b && a<c) return a;
	if(a>b) a=b;
	return a<c ? a:c;
}

int main()
{
	fstream fin("bigbrn.in",ios::in);
	fstream fout("bigbrn.out",ios::out);

	fin>>n>>m;
	int x,y;
	for(int i=1;i<=m;i++)
	{
		fin>>x>>y;
		tree[x][y]=true;
	}

	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(!tree[i][j])
			{
				f[i][j]=min3(f[i-1][j-1],f[i-1][j],f[i][j-1])+1;
				ans=f[i][j]>ans ? f[i][j]:ans;
			}

	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}