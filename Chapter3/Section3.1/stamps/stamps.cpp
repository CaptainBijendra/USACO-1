/*
ID: suzyzha1
PROG: stamps
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

int m,n;
int val[52],f[2010002];

int main()
{
	fstream fin("stamps.in",ios::in);
	fstream fout("stamps.out",ios::out);

	fin>>m>>n;
	int maxv=0;
	for(int i=1;i<=n;i++)
	{
		fin>>val[i];
		f[val[i]]=1;
		maxv=val[i]>maxv ? val[i]:maxv;
	}

	for(int i=1;i<=n;i++)
	{
		for(int j=val[i]+1;j<=val[i]+maxv;j++)
			if(f[j-val[i]]>0 && f[j-val[i]]<m && (f[j-val[i]]+1<f[j] || f[j]==0))
			{
				f[j]=f[j-val[i]]+1;
				maxv=j>maxv ? j:maxv;
			}
	}

	int i=0;
	for(i=1;i<=maxv;i++)
	{
		if(f[i]==0 || f[i]>m)
			break;
	}

	fout<<i-1<<endl;
	
	fin.close();
	fout.close();
	return 0;
}