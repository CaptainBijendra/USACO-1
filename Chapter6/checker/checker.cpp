/*
ID: suzyzha1
PROG: checker
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
const int maxn = 16;
const int base = 13;

int n,ans=0;
bool row[maxn],col[maxn],diag1[2*maxn],diag2[2*maxn];
int plan[maxn],first[3][maxn];

void dfs(int cur)
{
	if(cur>n)
	{
		if(ans<3)
		{
			for(int i=1;i<=n;i++)
				first[ans][i]=plan[i];
		}
		ans++;
		return;
	}

	for(int i=1;i<=n;i++)
	{
		if(col[i] || diag1[cur-i+base] || diag2[i+cur])
			continue;
		
		if(ans<3) plan[cur]=i;
		col[i]=diag1[cur-i+base]=diag2[i+cur]=true;
		dfs(cur+1);
		col[i]=diag1[cur-i+base]=diag2[i+cur]=false;
	}
}

int main()
{
	fstream fin("checker.in",ios::in);
	fstream fout("checker.out",ios::out);

	fin>>n;
	
	dfs(1);
	
	for(int i=0;i<3;i++)
	{
		for(int j=1;j<=n;j++)
			if(j==1)
				fout<<first[i][j];
			else
				fout<<" "<<first[i][j];
		fout<<endl;
	}
	fout<<ans<<endl;

	fin.close();
	fout.close();
	return 0;
}