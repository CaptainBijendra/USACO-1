/*
ID: suzyzha1
PROG: fence8
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const int maxn = 52;
const int maxm = 1024;

int n,m,b[maxn],r[maxm];

int sum_b,sum[maxm];

bool dfs(int cur_b,int cur_r)
{
	if(cur_r<=0)
		return true;
	
	int s=0;
	for(int i=1;i<=n;i++)
		if(b[i]>=r[1])
			s+=b[i];

	if(s<sum[cur_r]) return false;

	int st=1;
	if(cur_r<m && r[cur_r]==r[cur_r+1])
		st=cur_b;

	bool tmp;
	for(int i=st;i<=n;i++)
		if(b[i]==r[cur_r])
		{
			b[i]=0;
			tmp=dfs(1,cur_r-1);
			b[i]=r[cur_r];

			return tmp;
		}

	for(int i=st;i<=n;i++)
		if(b[i]>=r[cur_r])
		{
			b[i]-=r[cur_r];
			tmp=dfs(i,cur_r-1);
			b[i]+=r[cur_r];
			if(tmp) return true;
		}

	return false;
}

int main()
{
	fstream fin("fence8.in",ios::in);
	fstream fout("fence8.out",ios::out);

	fin>>n;
	sum_b=0;
	for(int i=1;i<=n;i++)
	{
		fin>>b[i];
		sum_b+=b[i];
	}

	fin>>m;
	for(int i=1;i<=m;i++)
		fin>>r[i];

	/* bubble sort for b */
	int tmp;
	for(int i=1;i<n;i++)
		for(int j=1;j<=n-i;j++)
			if(b[j]>b[j+1])
			{
				tmp=b[j];
				b[j]=b[j+1];
				b[j+1]=tmp;
			}

	int idx=1;
	for(int i=1;i<=m;i++)
		if(r[i]<=b[n])
		{
			r[idx]=r[i];
			idx++;
		}
	m=idx-1;

	sort(r+1,r+m+1);

	for(int i=1;i<=m;i++)
	{
		sum[i]=sum[i-1]+r[i];
		if(sum[i]>sum_b)
		{
			m=i-1;
			break;
		}
	}

	int l=0,r=m,mid;
	while(l<r)
	{
		mid=((l+r)>>1)+1;

		if(dfs(1,mid))
			l=mid;
		else
			r=mid-1;
	}

	fout<<l<<endl;
	fin.close();
	fout.close();
	return 0;
}
