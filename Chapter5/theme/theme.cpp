/*
ID: suzyzha1
PROG: theme
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;
const int maxn = 5002;

int n,diff[maxn];
int f[maxn];

int main()
{
	fstream fin("theme.in",ios::in);
	fstream fout("theme.out",ios::out);

	fin>>n;
	int pre=0,cur=0;
	for(int i=1;i<=n;i++)
	{
		fin>>cur;
		diff[i]=cur-pre;
		pre=cur;
	}

	int ans=0;
	for(int j=3;j<=n;j++)
		f[j]=(diff[j]==diff[2]);

	for(int i=3;i<=n;i++)
	{
		for(int j=n;j>=i+2;j--)
		{
			if(diff[i]==diff[j])
			{
				if(f[j-1]<=j-i-2)
					f[j]=f[j-1]+1;
				else
					f[j]=f[j-1];
			}
			else
				f[j]=0;

			ans=ans>f[j] ? ans:f[j];
		}
	}
	
	ans++;
	if(ans<5) ans=0;
	fout<<ans<<endl;

	fin.close();
	fout.close();
	return 0;
}