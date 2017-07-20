/*
ID: suzyzha1
PROG: kimbits
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

int n,m;
long long l;
long long f[32][32];

int main()
{
	fstream fin("kimbits.in",ios::in);
	fstream fout("kimbits.out",ios::out);

	fin>>n>>m>>l;

	for(int j=0;j<=m;j++) f[0][j]=1;

	for(int i=1;i<=n;i++)
	{
		f[i][0]=1;
		for(int j=1;j<=m;j++)
		{
			if(j<=i)
				f[i][j]=f[i-1][j-1]+f[i-1][j];
			else
				f[i][j]=f[i][j-1];
		}
	}

	int k=m;
	for(int i=n;i>=1;i--)
		if(l>f[i-1][k])
		{
			fout<<1;
			l-=f[i-1][k];
			k--;
		}
		else
			fout<<0;
	
	fout<<endl;
	
	fin.close();
	fout.close();
	return 0;
}