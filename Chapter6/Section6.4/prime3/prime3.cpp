/*
ID: suzyzha0
PROG: prime3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;
const int maxp=100000;
const int full=(1<<10)-1;

int change[1100];
bool not_prime[maxp+20];
int next_digit[maxp+20];

int sum,ans_count=0;
struct Square
{
	int d[5][5];
} sq,ans[1000];

int row[5],col[5],diag1,diag2;

void init()
{
	int tmp,s;
	for(int i=2;i<maxp;i++)
		if(!not_prime[i])
		{
			tmp=i<<1;
			if(tmp>=maxp) break;
			while(tmp<maxp)
			{
				not_prime[tmp]=true;
				tmp+=i;
			}

			if(i>10000)
			{
				tmp=i;
				s=0;
				while(tmp>0)
				{
					s+=tmp%10;
					tmp/=10;
				}
				if(s==sum) next_digit[i]=1;
			}
		}

	int st=1000,en=10000;
	for(int i=3;i>=0;i--,st/=10,en/=10)
		for(int j=st;j<en;j++)
			for(int k=0;k<10;k++)
				if(next_digit[j*10+k])
					next_digit[j] |= 1<<k;

	diag2=0;
	row[0]=col[0]=diag1=sq.d[0][0];

	for(int i=0;i<10;i++)
		change[1<<i]=i;
}

void record()
{
	int x[5], y[5], xx=0, yy=0;

	for(int i=0;i<5;i++) x[i]=y[i]=0;

	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
		{
			x[i]+=sq.d[i][j];
			y[j]+=sq.d[i][j];
		}

	for(int i=0;i<4;i++)
	{
		sq.d[i][4]=sum-x[i];
		sq.d[4][i]=sum-y[i];
		x[4]+=sq.d[4][i];
		y[4]+=sq.d[i][4];
		xx+=sq.d[i][i];
		yy+=sq.d[i][4-i];
	}
	yy+=sq.d[4][0];

	// if(yy==sum && x[4]==y[4] && x[4]==xx && x[4]<sum)
	// {
		sq.d[4][4]=sum-xx;
		for(int i=0;i<5;i++)
			for(int j=0;j<5;j++)
				ans[ans_count].d[i][j]=sq.d[j][i];
		ans_count++;
	// }
	// else
	// 	cout<<"!!"<<endl;
}

void dfs(int x,int y)
{
	if(x>3)
	{
		record();
		return;
	}

	int hash=full,hash2=full,hash3=full;

	if(y>0)
	{
		hash &= next_digit[row[x]];
		if(x==3)
		{
			row[4]=10*row[4]+change[next_digit[col[y-1]]];
			hash3 &= next_digit[row[4]];
		}		
	}
	else
	{
		/* y==0 . determine (x-1,4) */
		sq.d[x-1][4]=change[next_digit[row[x-1]]];
		col[4]=10*col[4]+sq.d[x-1][4];
	}

	if(x>0)
	{
		hash &= next_digit[col[y]];
		//if(y==3)
			hash2 &= next_digit[col[y+1]];
	}

	if(x==y)
	{
		hash &= next_digit[diag1];
		diag1*=10;
	}

	if(x==1 && y==0)
		diag2=change[next_digit[row[0]]];

	if(x+y==4)
	{
		hash &= next_digit[diag2];
		diag2*=10;
	}

	row[x]*=10;
	col[y]*=10;

	int be=0,lowbit,cur;

	while(hash>0)
	{
		lowbit = hash & (-hash);
		cur = change[lowbit];

		if( (hash3 & next_digit[col[y]+cur-be])
			&& (hash2 & next_digit[row[x]+cur-be]) )
		{
			sq.d[x][y]=cur;

			row[x]+=cur-be;
			col[y]+=cur-be;
			be=cur;

			if(x==y) diag1+=cur;
			if(x+y==4) diag2+=cur;

			if(y<3) dfs(x,y+1);
			else dfs(x+1,0);

			if(x==y) diag1-=cur;
			if(x+y==4) diag2-=cur;
		}
		hash-=lowbit;
	}

	row[x]/=10;
	col[y]/=10;
	if(x==y) diag1/=10;	
	if(x==3) row[4]/=10;
	if(y==0) col[4]/=10;
	if(x+y==4) diag2/=10;
}

bool my_cmp(const Square &a,const Square &b)
{
	for(int i=0;i<5;i++)
		for(int j=0;j<5;j++)
		{
			if(a.d[j][i]<b.d[j][i]) return true;
			if(a.d[j][i]>b.d[j][i]) return false;
		}
	return false;
}

int main()
{
	clock_t begin=clock();

	fstream fin("prime3.in",ios::in);
	fstream fout("prime3.out",ios::out);

	fin>>sum>>sq.d[0][0];

	init();

	dfs(0,1);

	if(ans_count==0)
		fout<<"NONE"<<endl;
	else
	{
		sort(ans,ans+ans_count,my_cmp);
		for(int i=0;i<ans_count;i++)
		{
			if(i>0) fout<<endl;
			for(int j=0;j<5;j++)
			{
				for(int k=0;k<5;k++)
					fout<<ans[i].d[k][j];
				fout<<endl;
			}
		}
	}

	fin.close();
	fout.close();

	clock_t en=clock();
	printf("time:%lu\n", (en-begin)*1000/CLOCKS_PER_SEC);
	return 0;
}