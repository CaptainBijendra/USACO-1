/*
ID: suzyzha1
PROG: barn1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const int maxs = 210;

int m,s,c,ans;
int num[maxs];
int interval[maxs];

void buble_sort(int *d,int size)
{
	int tmp;
	for(int i=size-1;i>0;i--)
		for(int j=0;j<i;j++)
			if(d[j]>d[j+1])
			{
				tmp=d[j]; d[j]=d[j+1]; d[j+1]=tmp;
			}
}

int main()
{
	fstream fin("barn1.in",ios::in);
	fstream fout("barn1.out",ios::out);

	fin>>m>>s>>c;

	if(c<=m)
	{
		fout<<c<<endl;

		fin.close();
		fout.close();
		return 0;
	}

	for(int i=0;i<c;i++)
		fin>>num[i];

	buble_sort(num,c);

	int n=0;
	for(int i=1;i<c;i++)
		if(num[i]-num[i-1]>1)
		{
			interval[n]=num[i]-num[i-1]-1;
			n++;
		}

	if(n+1<=m)
	{
		fout<<c<<endl;

		fin.close();
		fout.close();
		return 0;
	}

	buble_sort(interval,n);

	ans=c;
	for(int i=0;i<=n-m;i++)
		ans+=interval[i];

	fout<<ans<<endl;
	
	fin.close();
	fout.close();
	return 0;
}
