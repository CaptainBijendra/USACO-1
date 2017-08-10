/*
ID: suzyzha1
PROG: hidden
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;
const int maxn = 200020;

int n;
char s[maxn];

int main()
{
	fstream fin("hidden.in",ios::in);
	fstream fout("hidden.out",ios::out);

	fin>>n;
	for(int i=0;i<n;i+=72)
		fin>>(s+i);

	for(int i=0;i<n;i++)
		s[i+n]=s[i];

	int i=0,j=1,k;
	while(i<n && j<n)
	{
		k=0;
		while(k<n && s[i+k]==s[j+k])
			k++;

		if(s[i+k]>s[j+k])
			i+=k+1;
		else
			j+=k+1;

		if(i==j) j++;
	}

	if(i>j) i=j;
	fout<<i<<endl;
	fin.close();
	fout.close();
	return 0;
}