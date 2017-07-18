/*
ID: suzyzha1
PROG: comehome
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int n = 26;
const int maxd = 100000;

int idx[130];
int dist[60][60],d[60];
bool vis[60];

void dijkstra()
{
	memset(vis,0,sizeof(vis));
	memset(d,-1,sizeof(d));

	d[idx['Z']]=0;
	int best,k;
	for(int i=0;i<2*n;i++)
	{
		best=maxd;
		for(int j=0;j<2*n;j++)
			if(!vis[j] && d[j]>=0 && d[j]<best)
			{
				best=d[j];
				k=j;
			}

		if(best==maxd) break;
		vis[k]=true;

		for(int j=0;j<2*n;j++)
			if(!vis[j] && dist[k][j]>=0 && (d[j]==-1 || d[j]>d[k]+dist[k][j]))
			{
				d[j]=d[k]+dist[k][j];
			}
	}
}

int main()
{
	fstream fin("comehome.in",ios::in);
	fstream fout("comehome.out",ios::out);

	int p,w;
	char st,en;
	fin>>p;
	memset(dist,-1,sizeof(dist));
	for(int i=0;i<n;i++)
	{
		idx[i+'A']=i;
		idx[i+'a']=i+n;
		dist[i][i]=dist[i+n][i+n]=0;
	}

	for(int i=0;i<p;i++)
	{
		fin>>st>>en>>w;
		if(st==en) continue;
		if(dist[idx[st]][idx[en]]<0 || w<dist[idx[st]][idx[en]])
			dist[idx[st]][idx[en]]=dist[idx[en]][idx[st]]=w;
	}
	
	dijkstra();

	int k=0;
	for(int i=1;i<n-1;i++)
		if(d[i]!=-1)
			if(d[k]==-1 || d[i]<d[k])
				k=i;

	fout<<(char)(k+'A')<<" "<<d[k]<<endl;

	fin.close();
	fout.close();
	return 0;
}