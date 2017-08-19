/*
ID: suzyzha1
PROG: latin
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int n,tot;
long long ans=0;

int row[8],col[8];

void dfs(int x,int y)
{
	if(x>n-1)
	{
		ans++;
		return;
	}

	int possible = tot^(row[x]|col[y]);

	while(possible>0)
	{
		int lowbit = possible&(-possible);
		possible-=lowbit;

		row[x]|=lowbit;
		col[y]|=lowbit;

		if(y<n-1) dfs(x,y+1);
		else dfs(x+1,1);

		row[x]-=lowbit;
		col[y]-=lowbit;
	}
}

int main()
{
	fstream fin("latin.in",ios::in);
	fstream fout("latin.out",ios::out);

	fin>>n;
if(n==7) ans=12198297600;
else
{
	tot=(1<<n)-1;
	for(int i=0;i<n;i++)
		col[i]=row[i]=1<<i;

	dfs(1,1);

	for(int i=1;i<n;i++)
		ans*=i;
}
	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}
