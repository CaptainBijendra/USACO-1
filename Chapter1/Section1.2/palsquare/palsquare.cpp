/*
ID: suzyzha1
PROG: palsquare
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const int maxn = 300;

int base;
		
string transform(int cur)
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
	fstream fin("palsquare.in",ios::in);
	fstream fout("palsquare.out",ios::out);

	fin>>base;
	fin.close();

	fout<<"1 1"<<endl;

	string square;
	for(int i=2;i<=maxn;i++)
	{
		square=transform(i*i);
		if(is_pal(square))
			fout<<transform(i)<<" "<<square<<endl;
	}

	fout.close();
	return 0;
}
