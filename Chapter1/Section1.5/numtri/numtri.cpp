/*
ID: suzyzha1
PROG: numtri
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int maxn = 1010;

int n;
int tri[maxn][maxn];

int max_sum[maxn][maxn];

void dfs(int row,int col)
{
	if(max_sum[row][col]>=0) return;

	if(row==n-1)
	{
		max_sum[row][col]=tri[row][col];
		return;
	}

	dfs(row+1,col);
	dfs(row+1,col+1);
	if(max_sum[row+1][col]>max_sum[row+1][col+1])
		max_sum[row][col]=tri[row][col]+max_sum[row+1][col];
	else
		max_sum[row][col]=tri[row][col]+max_sum[row+1][col+1];
}

int main()
{
	fstream fin("numtri.in",ios::in);
	fstream fout("numtri.out",ios::out);

	fin>>n;
	for(int i=0;i<n;i++)
		for(int j=0;j<=i;j++)
			fin>>tri[i][j];

	memset(max_sum,-1,sizeof(max_sum));
	dfs(0,0);
	fout<<max_sum[0][0]<<endl;

	fin.close();
	fout.close();
	return 0;
}
