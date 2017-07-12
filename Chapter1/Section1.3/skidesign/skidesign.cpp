/*
ID: suzyzha1
PROG: skidesign
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

const int maxn = 1010;

int n;
int h[maxn];
int ans;

int square(int a)
{
	return a*a;
}

int main()
{
	fstream fin("skidesign.in",ios::in);
	fstream fout("skidesign.out",ios::out);

	int max_height=0,min_height=101;
	fin>>n;
	for(int i=1;i<=n;i++)
	{
		fin>>h[i];
		max_height=h[i]>max_height ? h[i]:max_height;
		min_height=h[i]<min_height ? h[i]:min_height;
	}
	if(max_height-min_height<17)
	{
		fout<<0<<endl;
		fin.close();
		fout.close();
		return 0;		
	}

	ans=INT_MAX;
	int tmp;
	for(int i=min_height;i<=max_height-17;i++)
	{
		tmp=0;
		for(int j=1;j<=n;j++)
			if(h[j]>i+17)
				tmp+=square(h[j]-i-17);
			else
			if(h[j]<i)
				tmp+=square(i-h[j]);

		ans=tmp<ans ? tmp:ans;
	}
	
	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}
