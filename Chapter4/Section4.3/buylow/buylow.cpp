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
const int base = 10;

int n,price[maxn],f[maxn];
int best_len=0;

class BigNumber
{
public:
	int len;
	int d[200];
	BigNumber() { len=1; d[1]=0; }
	void clear() { len=1; d[1]=0; }
	void print(fstream *fout);
	
	void operator += (const BigNumber &b);
	void operator = (const BigNumber &b);
} g[maxn],sum;

void BigNumber::operator += (const BigNumber &b)
{
	int l=max(this->len,b.len),i,tmp,rem;

	i=1; rem=0;
	while(i<=l || rem!=0)
	{
		tmp=rem;
		if(i<=this->len) tmp+=this->d[i];
		if(i<=b.len) tmp+=b.d[i];

		this->d[i]=tmp%base;
		rem=tmp/base;
		i++;
	}

	if(i-1>this->len) this->len=i-1;
}

void BigNumber::operator = (const BigNumber &b)
{
	this->len=b.len;
	for(int i=1;i<=b.len;i++)
		this->d[i]=b.d[i];
}

void BigNumber::print(fstream *fout)
{
	for(int i=len;i>=1;i--)
		*fout<<d[i];
	*fout<<endl;
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
	{
		if(f[i]==1)
			g[i].len=g[i].d[1]=1;
		else
		{
			g[i].clear();
			int goal = f[i]-1;
			int last = -1;
			for(int j=i-1;j>=1;j--)
				if(price[j]>price[i] && f[j]==goal && price[j]!=last)
				{
					g[i]+=g[j];
					last=price[j];
				}
		}
	}

	int last = -1;
	sum.clear();
	for(int i=n;i>=1;i--)
		if(f[i]==best_len && price[i]!=last)
		{
			sum+=g[i];
			last=price[i];
		}

	fout<<best_len<<" ";
	sum.print(&fout);

	fin.close();
	fout.close();
	return 0;
}