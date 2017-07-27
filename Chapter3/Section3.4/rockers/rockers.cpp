/*
ID: suzyzha1
PROG: rockers
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int n,m,total,t[22];
int f[22][22][22];

int main()
{
	fstream fin("rockers.in",ios::in);
	fstream fout("rockers.out",ios::out);

	fin>>n>>total>>m;
	for(int i=1;i<=n;i++)
		fin>>t[i];

	int last_max;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(t[i]<=total)
			{
				last_max=0;
				if(i>1 && j>1)
					for(int k=0;k<=total;k++)
						last_max=last_max>f[i-1][j-1][k] ? last_max:f[i-1][j-1][k];
			}
			for(int k=0;k<=total;k++)
				f[i][j][total]=max(f[i][j][total],f[i][j-1][k]);

			for(int k=total-1;k>=0;k--)
			{
				f[i][j][k]=f[i-1][j][k];
				if(k+t[i]<=total)
				{
					f[i][j][k]=max(f[i][j][k],f[i-1][j][k+t[i]]+1);
					f[i][j][k]=max(f[i][j][k],last_max+1);
				}
			}
		}

	int ans=0;
	for(int k=0;k<=total;k++)
		ans=ans>f[n][m][k] ? ans:f[n][m][k];

	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}