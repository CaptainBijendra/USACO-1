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

int change[12];
bool is_prime[maxp+20];
int next_digit[maxp+20];

int sum,ans_count=0;
struct Square
{
	int d[5][5];
} sq,ans[1000];

int row[5],col[5],diag[2];

int get_sum(int cur)
{
	int res=0;
	while(cur>0)
	{
		res+=cur%10;
		cur/=10;
	}
	return res;
}

void get_primes()
{
	for(int i=3;i<maxp;i+=2) is_prime[i]=true;

	int tmp;
	for(int i=3;i<maxp;i+=2)
		if(is_prime[i])
		{
			tmp=i<<1;
			if(tmp>=maxp) break;
			while(tmp<maxp)
			{
				is_prime[tmp]=false;
				tmp+=i;
			}
		}

	for(int i=10001;i<maxp;i+=2)
		if(is_prime[i] && get_sum(i)==sum)
			next_digit[i]=1;

	int st=1000,en=10000;
	for(int i=3;i>=0;i--)
	{
		for(int j=st;j<en;j++)
			for(int k=0;k<10;k++)
				if(next_digit[j*10+k]!=0)
					next_digit[j]|=(1<<k);
		st/=10;
		en/=10;
	}
}

void record()
{
	for(int i=0;i<4;i++)
	{
		int x=0;
		for(int j=0;j<4;j++)
			x+=sq.d[i][j];

		sq.d[i][4]=sum-x;
	}

	for(int j=0;j<5;j++)
	{
		int x=0;
		for(int i=0;i<5;i++)
			x+=sq.d[i][j];

		sq.d[4][j]=sum-x;
	}

	ans[ans_count]=sq;
	ans_count++;
}

void dfs(int x,int y)
{
	//printf("%d %d\n", x,y);
	if(x>3)
	{
		record();
		return;
	}
	int hash=full,hash1=full,hash2=full;

	if(y==0) /* row x-1 has been searched, so calculate (x-1,4) */
	{
		sq.d[x-1][4]=change[next_digit[row[x-1]]];
		col[4]=10*col[4]+sq.d[x-1][4];
	}
	else
	{
		hash &= next_digit[row[x]];
		if(x==3) /* calculate (4,y-1) */
		{
			//sq.d[4][y-1]=change[next_digit[col[y-1]]];
			row[4]=10*row[4]+change[next_digit[col[y-1]]];
			hash1 &= next_digit[row[4]];
		}
	}

	if(x>0)
	{
		hash &= next_digit[col[y]]; /* this column */
		if(y==3) hash2 &= next_digit[col[4]]; /* next column ?? */
	}

	if(x==y)
	{
		hash &= next_digit[diag[0]];
		//diag[0]*=10;
	}

	if(x==1 && y==0)
		diag[1]=change[next_digit[row[0]]];

	if(x+y==4)
	{
		hash &= next_digit[diag[1]];
		//diag[1]*=10;
	}

	// row[x]*=10;
	// col[y]*=10;

	while(hash!=0)
	{
		int cur=hash&(-hash);
		int i=change[cur];
		printf("cur:%d i:%d\n",cur,i);

		if((hash1 & next_digit[col[y]+i]) && (hash2 & next_digit[row[x]+i]))
		{
			sq.d[x][y]=i;

			row[x]=10*row[x]+i;
			col[y]=10*col[y]+i;
			if(x==y) diag[0]=10*diag[0]+i;
			if(x+y==4) diag[1]=10*diag[1]+i;

			// row[x]+=i;
			// col[y]+=i;
			// if(x==y) diag[0]+=i;
			// if(x+y==4) diag[1]-=i;

			if(y<3)
				dfs(x,y+1);
			else
				dfs(x+1,0);

			row[x]/=10;
			col[y]/=10;
			if(x==y) diag[0]/=10;
			if(x+y==4) diag[1]/=10;

			// row[x]-=i;
			// col[y]-=i;
			// if(x==y) diag[0]-=i;
			// if(x+y==4) diag[1]-=i;
		}

		hash-=cur;
	}
	// row[x]/=10;
	// col[y]/=10;
	// if(x==y) diag[0]/=10;
	if(y==0) col[4]/=10;
	if(x==3) row[4]/=10;
	// if(x+y==4) diag[1]/=10;
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

	get_primes();

	diag[1]=0;
	row[0]=col[0]=diag[0]=sq.d[0][0];

	for(int i=0;i<10;i++)
		change[1<<i]=i;

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
	printf("%d\n", ans_count);
	printf("time:%lu\n", (en-begin)*1000/CLOCKS_PER_SEC);
	return 0;
}
