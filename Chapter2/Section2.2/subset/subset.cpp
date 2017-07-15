/*
ID: suzyzha1
PROG: subset
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

int n,target;
long long f[800];

int main()
{
	fstream fin("subset.in",ios::in);
	fstream fout("subset.out",ios::out);

	fin>>n;
	fin.close();

	if(n*(n+1)%4>0)
	{
		fout<<0<<endl;
		fout.close();
		return 0;		
	}

	target=n*(n+1)/4;
	f[0]=f[1]=1;
	for(int i=2;i<=n;i++)
	{
		for(int j=max(i*(i+1)/2,target);j>=i;j--)
			f[j]+=f[j-i];
	}

	fout<<f[target]/2<<endl;
	fout.close();
	return 0;
}
