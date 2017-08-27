/*
ID: suzyzha1
PROG: vans
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;
const int maxn = 1002;

int n;

struct BigNum
{
	int len,d[1000];

	void init(int a) { len=1; d[1]=a; }
	void add(BigNum &a,BigNum &b); /* a+=b; */
	void subtract(BigNum &a,BigNum &b); /* a-=b; ( suppose a>=b )*/
} f[maxn],g[maxn];

void add(BigNum &a,const BigNum &b)
{
	int l = a.len>b.len ? a.len:b.len, rem = 0;

	for(int i=1;i<=l;i++)
	{
		a.d[i]+=b.d[i]+rem;
		rem=a.d[i]/10;
		a.d[i]%=10;
	}

	if(a.len<l) a.len=l;

	if(rem>0)
	{
		a.len++;
		a.d[a.len]=rem;
	}
}

void subtract(BigNum &a,BigNum &b)
{
	for(int i=1;i<=b.len;i++)
	{
		a.d[i]-=b.d[i];
		if(a.d[i]<0)
		{
			a.d[i+1]--;
			a.d[i]+=10;
		}
	}

	int i=a.len;
	while(a.d[i]==0 && i>1)
		i--;
	
	a.len=i;
}

int main()
{
	fstream fin("vans.in",ios::in);
	fstream fout("vans.out",ios::out);

	fin>>n;

	f[1].init(0);
	f[2].init(2);
	f[3].init(4);

	g[1].init(2);
	g[2].init(2);
	g[3].init(8);
	for(int i=4;i<=n;i++)
	{
		g[i]=f[i-1];
		add(g[i],f[i-1]);
		add(g[i],g[i-1]);
		add(g[i],g[i-2]);
		subtract(g[i],g[i-3]);

		f[i]=f[i-1];
		add(f[i],g[i-1]);
	}

	for(int i=f[n].len;i>=1;i--)
		fout<<f[n].d[i];
	fout<<endl;
	fin.close();
	fout.close();
	return 0;
}