/*
ID: suzyzha1
PROG: range
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <cmath>

using namespace std;

int n;
const int maxn = 252;

char field[maxn][maxn];
int f[maxn][maxn],square[maxn];

int main()
{
	fstream fin("range.in",ios::in);
	fstream fout("range.out",ios::out);

	fin>>n;
	for(int i=0;i<n;i++)
		fin>>field[i];

	for(int i=0;i<n;i++)
	{
		if(field[0][i]=='1') f[0][i]=1;
		else f[0][i]=0;

		if(field[i][0]=='1') f[i][0]=1;
		else f[i][0]=0;
	}

	int k;
	for(int i=1;i<n;i++)
		for(int j=1;j<n;j++)
		{
			if(field[i][j]=='0') continue;
			f[i][j]=1;
			if(f[i-1][j-1]==0) continue;

			for(k=1;k<=f[i-1][j-1];k++)
				if(field[i][j-k]=='0' || field[i-k][j]=='0')
					break;

			f[i][j]+=k-1;
			for(int k=2;k<=f[i][j];k++)
				square[k]++;
		}
	
	for(int i=2;i<=n;i++)
		if(square[i])
			fout<<i<<" "<<square[i]<<endl;

	fin.close();
	fout.close();
	return 0;
}