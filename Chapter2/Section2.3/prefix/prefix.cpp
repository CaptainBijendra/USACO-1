/*
ID: suzyzha1
PROG: prefix
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

int n=0,l[210];
string prim[210];

string s;
bool available[200002];

int main()
{
	fstream fin("prefix.in",ios::in);
	fstream fout("prefix.out",ios::out);

	string tmp;
	while(true)
	{
		fin>>tmp;
		if(tmp.compare(".")==0) break;

		n++;
		prim[n]=tmp;
	}

	while(true)
	{
		fin>>tmp;
		if(fin.eof()) break;

		s+=tmp;
	}
	fin.close();

	//sort(prim+1,prim+n+1);

	for(int i=1;i<=n;i++)
		l[i]=prim[i].length();


	int len=s.length();
	int cur_max=-1;
	for(int i=-1;i<len-1 && i<=cur_max;i++)
	{
		if(i>=0 && !available[i]) continue;

		for(int j=1;j<=n;j++)
		{
			if(i+l[j]<len && !available[i+l[j]])
				if(s.compare(i+1,l[j],prim[j])==0)
				{
					available[i+l[j]]=true;
					cur_max=i+l[j]>cur_max ? i+l[j]:cur_max;
				}
		}
	}

	fout<<cur_max+1<<endl;

	fout.close();
	return 0;
}
