/*
ID: suzyzha1
PROG: friday
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int start_year = 1900;
const int months[] = {31,28,31,30,31,30,31,31,30,31,30,31};

int n;
int week[7];

int main()
{
	fstream fin("friday.in",ios::in);
	fstream fout("friday.out",ios::out);

	fin>>n;
	int cur=0,tmp;
	bool flag;
	for(int i=0;i<n;i++)
	{
		int tmp=i+start_year;
		if(tmp%400==0 || (tmp%4==0 && tmp%100!=0))
			flag=true;
		else
			flag=false;

		for(int j=0;j<12;j++)
		{
			week[cur]++;
			cur+=months[j];
			if(flag && j==1) cur++;
			cur%=7;
		}
	}
	
	for(int i=0;i<7;i++)
	{
		if(i) fout<<" ";
		fout<<week[i];
	}
	fout<<endl;

	fin.close();
	fout.close();
	return 0;
}
