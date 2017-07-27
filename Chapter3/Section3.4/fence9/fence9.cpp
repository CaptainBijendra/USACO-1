/*
ID: suzyzha1
PROG: fence9
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


int main()
{
	fstream fin("fence9.in",ios::in);
	fstream fout("fence9.out",ios::out);

	int n,m,p,x1,x2,ans=0;
	fin>>n>>m>>p;
	
	double tan1,tan2,fx1,fx2;
	tan1=1.0*n/m;
	tan2=1.0*(n-p)/m;

	for(int y=1;y<m;y++)
	{
		fx1=tan1*y;
		x1=ceil(fx1);
		if(fabs(fx1-x1)<1e-10) x1++;

		fx2=tan2*y+p;
		x2=floor(fx2);
		if(fabs(fx2-x2)<1e-10) x2--;

		if(x1<=x2) ans+=x2-x1+1;
	}

	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}