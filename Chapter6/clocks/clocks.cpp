/*
ID: suzyzha1
PROG: clocks
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

bool moves[9][9];
int total = 0,num[9];
int status[9],backup[9];

int ans = 28, best[9];

void dfs(int cur,int sum)
{
	if(sum==0)
	{
		if(total<ans)
		{
			ans=total;
			for(int i=0;i<9;i++)
				best[i]=num[i];
		}
		return;
	}
	if(cur>8) return;

	int tmp,sum2;
	for(int i=3;i>=0;i--)
	if(total+i<=ans)
	{
		num[cur]=i;
		total+=i;

		sum2=sum;
		if(i>0)
		{
			memcpy(backup,status,sizeof(status));
			for(int j=0;j<9;j++)
				if(moves[cur][j])
				{
					tmp=(status[j]+i)%4;
					sum2=sum2-status[j]+tmp;
					status[j]=tmp;
				}
		}
		
		dfs(cur+1,sum2);

		total-=i;
		if(i>0)
			memcpy(status,backup,sizeof(status));
	}
}

int main()
{
	fstream fin("clocks.in",ios::in);
	fstream fout("clocks.out",ios::out);

	int tmp,tmp2=0;
	for(int i=0;i<9;i++)
	{
		fin>>tmp;
		
		status[i]=tmp/3%4;
		tmp2+=status[i];
	}

	moves[0][0]=moves[0][1]=moves[0][3]=moves[0][4]=true;
	moves[1][0]=moves[1][1]=moves[1][2]=true;
	moves[2][1]=moves[2][2]=moves[2][4]=moves[2][5]=true;
	moves[3][0]=moves[3][3]=moves[3][6]=true;
	moves[4][1]=moves[4][3]=moves[2][4]=moves[4][5]=moves[4][7]=true;
	moves[5][2]=moves[5][5]=moves[5][8]=true;
	moves[6][3]=moves[6][4]=moves[6][6]=moves[6][7]=true;
	moves[7][6]=moves[7][7]=moves[7][8]=true;
	moves[8][4]=moves[8][5]=moves[8][7]=moves[8][8]=true;

	dfs(1,tmp2);

	bool fisrt=true;
	for(int i=0;i<9;i++)
		for(int j=0;j<best[i];j++)
			if(fisrt)
			{
				fisrt=false;
				fout<<i+1;
			}
			else
				fout<<" "<<i+1;

	fout<<endl;
	fin.close();
	fout.close();
	return 0;
}