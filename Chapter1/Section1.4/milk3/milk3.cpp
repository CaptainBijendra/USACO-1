/*
ID: suzyzha1
PROG: milk3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int ca,cb,cc; /* capacity of bucket a,b,c */

bool vis[21][21][21];

bool ans[21];

void dfs(int a,int b,int c)
{
	if(vis[a][b][c]) return;
	vis[a][b][c]=true;

	if(a==0) ans[c]=true;

	if(a>0)
	{
		if(b<cb)
		{
			if(a+b<=cb) dfs(0,a+b,c);
			else dfs(a-cb+b,cb,c);
		}
		if(c<cc)
		{
			if(a+c<=cc) dfs(0,b,a+c);
			else dfs(a-cc+c,b,cc);
		}
	}
	if(b>0)
	{
		if(a<ca)
		{
			if(a+b<=ca) dfs(a+b,0,c);
			else dfs(ca,b-ca+a,c);
		}
		if(c<cc)
		{
			if(c+b<=cc) dfs(a,0,b+c);
			else dfs(a,b-cc+c,cc);
		}
	}
	if(c>0)
	{
		if(a<ca)
		{
			if(a+c<=ca) dfs(a+c,b,0);
			else dfs(ca,b,c-ca+a);
		}
		if(b<cb)
		{
			if(b+c<=cb) dfs(a,b+c,0);
			else dfs(a,cb,c-cb+b);
		}
	}
}

int main()
{
	fstream fin("milk3.in",ios::in);
	fstream fout("milk3.out",ios::out);

	fin>>ca>>cb>>cc;
	fin.close();

	dfs(0,0,cc);

	for(int i=0;i<cc;i++)
		if(ans[i])
			fout<<i<<" ";
	fout<<cc<<endl;

	fout.close();
	return 0;
}
