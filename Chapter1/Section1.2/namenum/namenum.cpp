/*
ID: suzyzha1
PROG: namenum
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int maxm = 5010;
const char keypad[][3] = {};

int n;
string num;

int m;
string dict[maxm];

int main()
{
	fstream fin("namenum.in",ios::in);
	fstream fout("namenum.out",ios::out);

	fin>>num;
	n=num.length();
	fin.close();

	fstream fin("dict.txt",ios::in);

	m=0;
	while(1)
	{
		fin>>dict[m];
		if(fin.eof()) break;
		m++;
	}

	string cur(n,'A');
	for(int i=0;i<n;i++)
		for(int j=0;j<3;j++)
			cur[i]=keypad[num[i]-'2'][j];

	int l=0,r=m-1,mid;
	while(l<r)
	{
		mid=(l+r)>>1;

	}
	
	fin.close();
	fout.close();
	return 0;
}
