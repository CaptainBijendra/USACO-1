/*
ID: suzyzha1
PROG: milk4
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;
const int maxn = 102;
const int maxm = 20020;

int n,m,pail[maxn];

int ans;
bool avaliable[maxn];
int now[maxn],best[maxn];

void update(int new_ans)
{
	bool flag=false;

	if(ans<0)
	{
		ans=new_ans;
		flag=true;
	}

	if(!flag)
		for(int i=1;i<=ans;i++)
		{
			if(best[i]>now[i])
			{
				flag=true;
				break;
			}
			else
			if(best[i]<now[i])
				break;
		}

	if(flag)
		for(int i=1;i<=ans;i++)
			best[i]=now[i];
}

void dfs(int cur,int rest,int depth,int max_depth)
{
	if(depth>max_depth)
	{
		if(rest==0)
			update(max_depth);

		return;
	}

	if(cur>n || rest<pail[cur]) return;

	now[depth]=cur;
	for(int i=1;i<=rest/pail[cur];i++)
		dfs(cur+1,rest-i*pail[cur],depth+1,max_depth);

	dfs(cur+1,rest,depth,max_depth);
}

int main()
{
	fstream fin("milk4.in",ios::in);
	fstream fout("milk4.out",ios::out);

	fin>>m>>n;
	for(int i=1;i<=n;i++) fin>>pail[i];

	fin.close();

	for(int i=1;i<n;i++)
		for(int j=1;j<=n-i;j++)
			if(pail[j]>pail[j+1])
			{
				int tmp=pail[j];
				pail[j]=pail[j+1];
				pail[j+1]=tmp;
			}

	ans=-1;
	for(int lim=1;lim<=n;lim++)
	{
		dfs(1,m,1,lim);
		if(ans>0)
			break;
	}

	fout<<ans;
	for(int i=1;i<=ans;i++)
		fout<<" "<<pail[best[i]];
	fout<<endl;
	
	fout.close();
	return 0;
}