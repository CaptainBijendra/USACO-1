/*
ID: suzyzha1
PROG: nuggets
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const int maxv = 2000000000;
const int maxm = 256*256;

int n,d[10];
bool f[maxm];

int gcd(int a,int b)
{
	if(a%b==0) return b;
	return gcd(b,a%b);
}

int main()
{
	fstream fin("nuggets.in",ios::in);
	fstream fout("nuggets.out",ios::out);

	fin>>n;
	for(int i=0;i<n;i++) fin>>d[i];
	fin.close();
	sort(d,d+n);

	if(d[0]==1)
	{
		fout<<0<<endl;
		fout.close();
		return 0;
	}

	int p=d[0];
	for(int i=1;i<n;i++) p=gcd(p,d[i]);

	if(p!=1)
	{
		fout<<0<<endl;
		fout.close();
		return 0;	
	}

	f[0]=true;
	int lim=d[n-1]*d[n-2]-d[n-1]-d[n-2];
	for(int i=0;i<n;i++)
		for(int j=d[i];j<=lim;j++)
			if(f[j-d[i]])
				f[j]=true;

	int ans=0;
	for(int i=lim;i>=1;i--)
		if(!f[i])
		{
			ans=i;
			break;
		}

	fout<<ans<<endl;
	fout.close();
	return 0;
}