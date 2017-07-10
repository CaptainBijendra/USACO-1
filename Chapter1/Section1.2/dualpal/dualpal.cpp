/*
ID: suzyzha1
PROG: dualpal
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

string transform(int cur,int base)
{
	string s;
	int i=cur;
	int tmp;
	while(i>0)
	{
		tmp=i%base;
		if(tmp>=10)
			tmp=tmp-10+'A';
		else
			tmp+='0';

		s.push_back(tmp);
		i/=base;
	}
	std::reverse(s.begin(),s.end());
	return s;
}

bool is_pal(string s)
{
	int i=0,j=s.length()-1;
	while(i<j)
	{
		if(s[i]!=s[j]) return false;
		i++;
		j--;
	}
	return true;
}

int main()
{
	fstream fin("dualpal.in",ios::in);
	fstream fout("dualpal.out",ios::out);

	int n,start;
	fin>>n>>start;
	fin.close();

	int i=start+1,sum=0,tmp=0;
	while(i<INT_MAX)
	{
		tmp=0;
		for(int j=2;j<=10;j++)
			if(is_pal(transform(i,j)))
			{
				tmp++;
				if(tmp>=2) break;
			}

		if(tmp>=2)
		{
			sum++;
			fout<<i<<endl;
			if(sum>=n) break;
		}
		i++;
	}

	fout.close();
	return 0;
}
