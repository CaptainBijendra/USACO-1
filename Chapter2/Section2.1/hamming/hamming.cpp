/*
ID: suzyzha1
PROG: hamming
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int n,b,d;

int idx=0;
int codewords[300];

int hamming_dist(int w1,int w2)
{
	int dist=0,tmp=(w1^w2)&((1<<b)-1);
	for(int i=0;i<b;i++)
		if(tmp&(1<<i))
			dist++;
	return dist;
}

bool check_dist(int num)
{
	for(int i=1;i<=idx;i++)
		if(hamming_dist(num,codewords[i])<d)
			return false;
	return true;
}

void dfs(int cur_digit,int num)
{
	if(idx>=n) return;

	if(cur_digit<0)
	{
		if(check_dist(num))
		{
			idx++;
			codewords[idx]=num;
		}
		return;
	}
	dfs(cur_digit-1,num);
	dfs(cur_digit-1,num|(1<<cur_digit));
}

int main()
{
	fstream fin("hamming.in",ios::in);
	fstream fout("hamming.out",ios::out);

	fin>>n>>b>>d;

	dfs(b-1,0);

	int count=0;
	for(int i=1;i<=idx;i++)
	{
		if(count) fout<<" ";
		fout<<codewords[i];
		count++;
		if(count==10)
		{
			fout<<endl;
			count=0;
		}
	}
	if(count) fout<<endl;

	fin.close();
	fout.close();
	return 0;
}
