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
const char keypad[][3] = {	'A','B','C',
							'D','E','F',
							'G','H','I',
							'J','K','L',
							'M','N','O',
							'P','R','S',
							'T','U','V',
							'W','X','Y'};

int n;
string num;

int m;
string dict[maxm];

int idx=0;
string ans[maxm];

bool valid(string s)
{
	int l=0,r=m-1,mid;
	while(l<=r)
	{
		mid=(l+r)>>1;
		if(dict[mid]==s) return true;
		else
		if(dict[mid].compare(s)>0) r=mid-1;
		else l=mid+1;
	}

	return false;
}

void dfs(int cur,string s)
{
	if(cur>=n)
	{
		if(valid(s))
		{
			ans[idx]=s;
			idx++;
		}
		return;
	}

	for(int j=0;j<3;j++)
	{
		s[cur]=keypad[num[cur]-'2'][j];
		dfs(cur+1,s);
	}
}

int main()
{
	fstream fin("namenum.in",ios::in);
	fstream fout("namenum.out",ios::out);

	fin>>num;
	n=num.length();
	fin.close();

	fstream fin2("dict.txt",ios::in);

	m=0;
	while(1)
	{
		fin2>>dict[m];
		if(fin2.eof()) break;
		m++;
	}

	string cur(n,'A');
	dfs(0,cur);

	if(idx)
		for(int i=0;i<idx;i++)
			fout<<ans[i]<<endl;
	else
		fout<<"NONE"<<endl;
	
	fin2.close();
	fout.close();
	return 0;
}
