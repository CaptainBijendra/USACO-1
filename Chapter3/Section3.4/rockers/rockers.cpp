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
int f[22][22];

int main()
{
	fstream fin("rockers.in",ios::in);
	fstream fout("rockers.out",ios::out);

	fin>>n>>total>>m;
	for(int i=1;i<=n;i++)
		fin>>t[i];

	for(int i=1;i<=n;i++)
		for(int j=1;j<=t[i];j++)
	fin.close();
	fout.close();
	return 0;
}