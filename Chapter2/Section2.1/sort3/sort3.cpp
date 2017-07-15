/*
ID: suzyzha1
PROG: sort3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int n;
int seq[1010];

int num[4];

int main()
{
	fstream fin("sort3.in",ios::in);
	fstream fout("sort3.out",ios::out);

	fin>>n;
	for(int i=1;i<=n;i++)
	{
		fin>>seq[i];
		num[seq[i]]++;
	}

	int mis21=0,mis31=0,mis1=0,mis23=0,mis32=0,mis12=0,mis13=0;
	for(int i=1;i<=n;i++)
	{
		switch(seq[i])
		{
			case 1:
				if(i>num[1]) mis1++;
				if(i>num[1] && i<=num[1]+num[2]) mis12++;
				if(i>num[1]+num[2]) mis13++;
				break;
			case 2:
				if(i<=num[1]) mis21++;
				else
				if(i>num[1]+num[2]) mis23++;
				break;
			case 3:
				if(i<=num[1]) mis31++;
				else
				if(i<=num[1]+num[2]) mis32++;
				break;
		}
	}

	int ans=mis1;

	if(mis12>=mis21) ans+=mis32+mis12-mis21;
	else ans+=mis23+mis13-mis31;
	
	fout<<ans<<endl;

	fin.close();
	fout.close();
	return 0;
}
