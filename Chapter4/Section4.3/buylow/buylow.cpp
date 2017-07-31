/*
ID: suzyzha1
PROG: buylow
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int maxn = 5002;

int n,price[maxn],f[maxn];
int best_len=0,sum=0;
int idx=0,sol[200][maxn];
int now[maxn];
bool invalid[maxn];

void dfs(int cur,int num)
{
	now[num]=cur;

	if(num==best_len)
	{
		idx++;
		for(int i=1;i<=best_len;i++)
			sol[idx][i]=now[i];
		return;
	}

	for(int i=cur-1;i>=1;i--)
		if(price[i]>price[cur] && f[i]==f[cur]-1)
			dfs(i,num+1);
}

int main()
{
	fstream fin("buylow.in",ios::in);
	fstream fout("buylow.out",ios::out);

	fin>>n;
	for(int i=1;i<=n;i++)
		fin>>price[i];

	for(int i=1;i<=n;i++)
	{
		f[i]=1;
		for(int j=i-1;j>=1;j--)
			if(price[j]>price[i] && f[j]+1>f[i])
				f[i]=f[j]+1;

		if(f[i]>best_len) best_len=f[i];
	}

	for(int i=1;i<=n;i++)
		if(f[i]==best_len)
			dfs(i,1);

	sum=idx;
	int k;
	for(int i=1;i<idx;i++)
		if(!invalid[i])
		{
			for(int j=i+1;j<=idx;j++)
				if(!invalid[j])
				{
					k=1;
					while(sol[i][k]==sol[j][k] && k<=best_len)
						k++;
					
					if(k==best_len+1)
					{
						sum--;
						invalid[j]=true;
					}
				}
		}

	for(int i=1;i<=idx;i++)
		if(!invalid[i])
		{
			printf("i:%d\n",i );
		}

	fout<<best_len<<" "<<sum<<endl;
	fin.close();
	fout.close();
	return 0;
}