/*
ID: suzyzha1
PROG: fact4
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

int n,ans=1;

int main()
{
	fstream fin("fact4.in",ios::in);
	fstream fout("fact4.out",ios::out);

	fin>>n;

	int j;
	int c2=0,c5=0;
	for(int i=2;i<=n;i++)
	{
		j=i;
		while(j>0 && (j&1)==0) { j>>=1; c2++; }
		while(j>0 && j%5==0) { j/=5; c5++; }

		ans=ans*j%10;
	}

	c2-=c5;
	while(c2)
	{
		ans=(ans<<1)%10;
		c2--;
	}
	
	fout<<ans<<endl;
	
	fin.close();
	fout.close();
	return 0;
}