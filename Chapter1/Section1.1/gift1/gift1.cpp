/*
ID: suzyzha1
PROG: gift1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int maxn = 12;
int n;
string names[maxn];
int num_of_friends[12],friends[12][12];
int money[12],receive[12];

int main()
{
	fstream fin("gift1.in",ios::in);
	fstream fout("gift1.out",ios::out);

	fin>>n;
	for(int i=0;i<n;i++) fin>>names[i];

	string cur;
	int j,p;
	for(int i=0;i<n;i++)
	{
		fin>>cur;
		for(j=0;j<n;j++)
			if(cur==names[j]) break;

		fin>>money[j]>>num_of_friends[j];
		for(int k=0;k<num_of_friends[j];k++)
		{
			fin>>cur;
			for(p=0;p<n;p++)
				if(cur==names[p]) break;

			friends[j][k]=p;
		}
	}

	for(int i=0;i<n;i++)
		if(num_of_friends[i]>0)
		{
			int tmp=money[i]/num_of_friends[i];
			money[i]=tmp*num_of_friends[i];
			for(int j=0;j<num_of_friends[i];j++)
				receive[friends[i][j]]+=tmp;
		}

	for(int i=0;i<n;i++)
		fout<<names[i]<<" "<<receive[i]-money[i]<<endl;

	fin.close();
	fout.close();
	return 0;
}
