/*
ID: suzyzha1
PROG: agrinet 
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;

int n;
int dist[102][102],d[102];
bool vis[102];

int prim()
{
	for(int i=0;i<n;i++) d[i]=dist[0][i];

	int mind,k,ans=0;
	for(int i=0;i<n;i++)
	{
		mind=INT_MAX;
		for(int j=0;j<n;j++)
			if(!vis[j] && d[j]<mind)
			{
				mind=d[j];
				k=j;
			}

		if(mind==INT_MAX) break;

		vis[k]=true;
		ans+=mind;
		for(int j=0;j<n;j++)
			if(!vis[j] && d[j]>dist[k][j])
				d[j]=dist[k][j];
	}
	return ans;
}

int main()
{
	fstream fin("agrinet.in",ios::in);
	fstream fout("agrinet.out",ios::out);

	fin>>n;

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			fin>>dist[i][j];

	fout<<prim()<<endl;

	fin.close();
	fout.close();
	return 0;
}