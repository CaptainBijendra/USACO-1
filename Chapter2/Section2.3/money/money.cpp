/*
ID: suzyzha1
PROG: money
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int n,v;
long long f[10002];

int main()
{
	fstream fin("money.in",ios::in);
	fstream fout("money.out",ios::out);

	fin>>v>>n;

	f[0]=1;
	int val;
	for(int i=1;i<=v;i++)
	{
		fin>>val;
		for(int j=val;j<=n;j++)
			f[j]+=f[j-val];
	}

	fout<<f[n]<<endl;
	fin.close();
	fout.close();
	return 0;
}