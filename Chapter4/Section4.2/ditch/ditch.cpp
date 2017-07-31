/*
ID: suzyzha1
PROG: ditch
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;

const int maxm = 202;
const int maxf = 10000000;

int n,m;
int cap[maxm][maxm];

int tot_flow=0;
int vis[maxm],flow[maxm],pre[maxm];

void get_max_flow()
{
	while(true)
	{
		memset(vis,0,sizeof(vis));
		memset(flow,0,sizeof(flow));
		flow[1]=maxf;

		while(true)
		{
			int max_flow=0;
			int max_loc=0;
			for(int i=1;i<=m;i++)
				if(!vis[i] && flow[i]>max_flow)
				{
					max_flow=flow[i];
					max_loc=i;
				}

			if(max_loc==0)
				break;

			vis[max_loc]=true;
			for(int i=1;i<=m;i++)
				if(!vis[i])
				{
					int tmp=min(max_flow,cap[max_loc][i]);
					if(flow[i]<tmp)
					{
						flow[i]=tmp;
						pre[i]=max_loc;
					}
				}
		}

		if(flow[m]==0) break;

		tot_flow+=flow[m];

		int i=m;
		while(i!=1)
		{
			int p=pre[i];
			cap[p][i]-=flow[m];
			cap[i][p]+=flow[m];
			i=p;
		}
	}
}

int main()
{
	fstream fin("ditch.in",ios::in);
	fstream fout("ditch.out",ios::out);

	fin>>n>>m;

	int s,e,c;
	for(int i=1;i<=n;i++)
	{
		fin>>s>>e>>c;
		cap[s][e]+=c;
	}

	get_max_flow();
	
	fout<<tot_flow<<endl;
	fin.close();
	fout.close();
	return 0;
}