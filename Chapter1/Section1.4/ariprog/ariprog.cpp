/*
ID: suzyzha1
PROG: ariprog
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int n,m;
bool available[126000];
int bi=0,bisquare[32000];

struct Sequence
{
	int st,diff;
};

int num=0;
Sequence ans[10020];

bool my_cmp(Sequence a,Sequence b)
{
	return a.diff<b.diff;
}

int main()
{
	fstream fin("ariprog.in",ios::in);
	fstream fout("ariprog.out",ios::out);

	fin>>n>>m;
	fin.close();

	int tmp;
	for(int i=0;i<=m;i++)
		for(int j=i;j<=m;j++)
		{
			tmp=i*i+j*j;
			available[tmp]=true;
			bi++;
			bisquare[bi]=tmp;
		}
	
	sort(bisquare+1,bisquare+bi+1);
	
	int diff;
	bool flag;
	int max_bisquare=2*m*m;

	for(int i=1;i<=bi-n+1;i++)
	if(i==1 || bisquare[i]!=bisquare[i-1])
	{
		for(int j=i+1;j<=bi-n+2;j++)
		if(bisquare[j]!=bisquare[j-1])
		{
			tmp=bisquare[j];
			diff=bisquare[j]-bisquare[i];
			flag=true;
			for(int k=2;k<n;k++)
			{
				tmp+=diff;
				if(tmp>max_bisquare || !available[tmp])
				{
					flag=false;
					break;
				}
			}

			if(flag)
			{
				num++;
				ans[num].st=bisquare[i];
				ans[num].diff=diff;
			}
		}
	}
	
	if(num==0)
		fout<<"NONE"<<endl;
	else
	{
		sort(ans+1,ans+num+1,my_cmp);
		for(int i=1;i<=num;i++)
			fout<<ans[i].st<<" "<<ans[i].diff<<endl;
	}

	fout.close();
	return 0;
}
