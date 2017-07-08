/*
ID: suzyzha1
PROG: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int maxn = 5010;
int n,milk_time,no_milk_time;
int st[maxn],en[maxn];

int main()
{
	fstream fin("milk2.in",ios::in);
	fstream fout("milk2.out",ios::out);

	fin>>n;

	for(int i=0;i<n;i++)
		fin>>st[i]>>en[i];

	int tmp;
	for(int i=0;i<n-1;i++)
	{
		for(int j=0;j<n-1-i;j++)
			if(st[j]>st[j+1] || (st[j]==st[j+1] && en[j]>en[j+1]))
			{
				tmp=st[j]; st[j]=st[j+1]; st[j+1]=tmp;
				tmp=en[j]; en[j]=en[j+1]; en[j+1]=tmp;
			}	
	}

	milk_time=tmp=en[0]-st[0];
	no_milk_time=0;

	int cur_en=en[0];
	for(int i=1;i<n;i++)
	{
		if(st[i]<=cur_en)
		{
			if(en[i]<=cur_en) continue;
			tmp+=en[i]-cur_en;
			cur_en=en[i];
		}
		else
		{
			milk_time=tmp>milk_time ? tmp:milk_time;
			no_milk_time=st[i]-cur_en>no_milk_time ? st[i]-cur_en:no_milk_time;
			
			tmp=en[i]-st[i];
			cur_en=en[i];
		}
	}

	fout<<milk_time<<" "<<no_milk_time<<endl;

	fin.close();
	fout.close();
	return 0;
}
