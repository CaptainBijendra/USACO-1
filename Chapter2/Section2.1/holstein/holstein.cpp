/*
ID: suzyzha1
PROG: holstein
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int v,g;
int req[26],contain[16][26];

int ans;
bool now[16],best[16];

void dfs(int cur)
{
	if(cur>=g)
	{
		for(int i=0;i<v;i++)
			if(req[i]>0)
				return;

		int scoops=0;
		for(int i=0;i<g;i++)
			if(now[i])
				scoops++;

		if(scoops<ans)
		{
			ans=scoops;
			for(int i=0;i<g;i++) best[i]=now[i];
		}

		return;
	}

	for(int i=0;i<v;i++)
		req[i]-=contain[cur][i];

	now[cur]=true;
	dfs(cur+1);
	now[cur]=false;
	for(int i=0;i<v;i++)
		req[i]+=contain[cur][i];

	dfs(cur+1);
}

int main()
{
	fstream fin("holstein.in",ios::in);
	fstream fout("holstein.out",ios::out);

	fin>>v;
	for(int i=0;i<v;i++)
		fin>>req[i];

	fin>>g;
	for(int i=0;i<g;i++)
		for(int j=0;j<v;j++)
			fin>>contain[i][j];

	ans=g+1;
	dfs(0);
	
	fout<<ans;
	for(int i=0;i<g;i++)
		if(best[i])
			fout<<" "<<i+1;

	fout<<endl;

	fin.close();
	fout.close();
	return 0;
}
