/*
ID: suzyzha1
PROG: humble
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <climits>
#include <cmath>

using namespace std;

const int maxn = 100002;

int m,n;
int p[102],idx[102];
int humble[maxn];

int main()
{
	fstream fin("humble.in",ios::in);
	fstream fout("humble.out",ios::out);

	fin>>m>>n;
	for(int i=1;i<=m;i++)
		fin>>p[i];

	int min_num,k=0;
	humble[0]=1;
	for(int i=1;i<=n;i++)
	{
		min_num=INT_MAX;
		for(int j=1;j<=m;j++)
		{
			while((double)humble[idx[j]]*p[j]<=humble[i-1])
				idx[j]++;

			if((double)humble[idx[j]]*p[j]<min_num)
			{
				min_num=humble[idx[j]]*p[j];
				k=j;
			}
		}
		humble[i]=min_num;
		idx[k]++;
	}

	fout<<humble[n]<<endl;
	fin.close();
	fout.close();
	return 0;
}