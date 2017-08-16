/*
ID: suzyzha0
PROG: prime2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int sum,ans_count=0;
struct Square
{
	int d[5][5];
} sq,ans[1000];

int row_count[5],col_count[5];

const int order[][2] = 	{ {0,1},{0,2},{0,3},{0,4},
					{1,0},{1,1},{1,2},{1,3},{1,4},
					{2,0},{2,1},{2,2},{2,3},{2,4},
					{3,0},{3,1},{3,2},{3,3},{3,4},
					{4,0},{4,1},{4,2},{4,3},{4,4}};

const int pos[2][5][2] = {{ {0,0},{1,1},{2,2},{3,3},{4,4} },
						  { {4,0},{3,1},{2,2},{1,3},{0,4} }};

bool is_prime(int d)
{
	if((d&1)==0) return false;
	
}

bool check_row(int cur)
{
	if(row_count[cur]!=sum) return false;
	if(!is_prime(row[cur])) return false;

	return true;
}

bool check_col(int cur)
{
	if(col_count[cur]!=sum) return false;
	if(!is_prime(col[cur])) return false;

	return true;
}

bool check_diag()
{
	int s,d;
	for(int i=0;i<2;i++)
	{
		s=0;
		for(int j=0;j<5;j++)
		{
			s+=sq.d[pos[i][j][0]][pos[i][j][1]];
			d=10*d+sq.d[pos[i][j][0]][pos[i][j][1]];
		}

		if(s!=sum || !is_prime(d)) return false;
	}
	return true;
}

void dfs(int cur)
{
	if(cur>=24)
	{
		if(check_diag())
		{
			ans[ans_count]=sq;
			ans_count++;
		}
		return;
	}

	int x=order[i][0],y=order[i][1];

	for(int i=0;i<10;i++)
	{
		if(i>sum) break;
		if((x==0 || y==0) && i==0) continue;
		if((x==4 || y==4) && i%2==0) continue;

		sq[x][y]=i;
		flag=true;

		row_count[x]+=i;
		col_count[y]+=i;
		row[x]=10*row[x]+i;
		col[y]=10*col[y]+i;
		if(y==4) flag=check_row(x);
		if(x==4) flag=check_col(y);

		if(flag) dfs(cur+1);

		row_count[x]-=i;
		col_count[y]-=i;
		row[x]=(row[x]-i)/10;
		col[y]=(row[x]-i)/10;
	}
}

int main()
{
	fstream fin("prime2.in",ios::in);
	fstream fout("prime2.out",ios::out);

	fin>>sum>>sq.d[0][0];

	row_count[0]=col_count[0]=row[0]=col[0]=sq.d[0][0];

	dfs(0);

	if(ans_count==0)
		fout<<"NONE"<<endl;
	else
		for(int i=0;i<ans_count;i++)
		{
			if(i>0) fout<<endl;
			for(int j=0;j<5;j++)
			{
				for(int k=0;k<5;k++)
					fout<<ans[cur].d[j][k];
				fout<<endl;
			}
		}

	fin.close();
	fout.close();
	return 0;
}
