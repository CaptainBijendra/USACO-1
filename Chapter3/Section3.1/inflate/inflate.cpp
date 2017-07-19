/*
ID: suzyzha1
PROG: inflate
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

int m,n;
int f[10002];

int points[10002],minutes[10002];

int main()
{
	fstream fin("inflate.in",ios::in);
	fstream fout("inflate.out",ios::out);

	fin>>m>>n;

	for(int i=0;i<n;i++)
		fin>>points[i]>>minutes[i];

	int tmp;
	for(int i=0;i<n;i++)
		for(int j=minutes[i];j<=m;j++)
		{
			tmp=f[j-minutes[i]]+points[i];
			if(tmp>f[j]) f[j]=tmp;
		}

	fout<<f[m]<<endl;

	fin.close();
	fout.close();
	return 0;
}