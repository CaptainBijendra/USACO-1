/*
ID: suzyzha1
PROG: nocows
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

const int mo = 9901;

int n,depth;

int f[202][102];

int main()
{
	fstream fin("nocows.in",ios::in);
	fstream fout("nocows.out",ios::out);

	fin>>n>>depth;
	fin.close();

	for(int j=1;j<=depth;j++) f[1][j]=1;

	for(int i=3;i<=n;i++)
		for(int j=1;j<=depth;j++)
			for(int k=1;k<i-1;k++)
				f[i][j]=(f[i][j]+f[k][j-1]*f[i-1-k][j-1])%mo;

	int ans=(f[n][depth]-f[n][depth-1]+mo)%mo;
	fout<<ans<<endl;

	fout.close();
	return 0;
}
