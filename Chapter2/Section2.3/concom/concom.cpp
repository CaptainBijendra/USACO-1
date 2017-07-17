/*
ID: suzyzha1
PROG: concom
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>

using namespace std;

int n,m=0;
bool appeared[102];
int company[102],percent[102][102];
bool control[102][102];

void bfs(int st)
{
	int p[102];
	memset(p,0,sizeof(p));

	queue<int> qu;
	qu.push(st);
	control[st][st]=true;

	int cur;
	while(!qu.empty())
	{
		cur=qu.front();
		qu.pop();
		for(int i=1;i<=m;i++)
			if(!control[st][company[i]])
			{
				p[company[i]]+=percent[cur][company[i]];
				if(p[company[i]]>50)
				{
					qu.push(company[i]);
					control[st][company[i]]=true;
				}
			}
	}	
}

int main()
{
	fstream fin("concom.in",ios::in);
	fstream fout("concom.out",ios::out);

	fin>>n;
	int a,b,c;
	for(int i=0;i<n;i++)
	{
		fin>>a>>b>>c;
		percent[a][b]=c;
		appeared[a]=appeared[b]=true;
	}

	for(int i=1;i<=100;i++)
		if(appeared[i])
		{
			m++;
			company[m]=i;
		}

	for(int i=1;i<=m;i++)
	{
		bfs(company[i]);

		for(int j=1;j<=m;j++)
			if(j!=i && control[company[i]][company[j]])
				fout<<company[i]<<" "<<company[j]<<endl;
	}

	fin.close();
	fout.close();
	return 0;
}