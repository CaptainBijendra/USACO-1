/*
ID: suzyzha1
PROG: combo
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

int n;
int password[2][3];
int combination[3];

bool is_available(int cur)
{
	int dist,tmp;
	for(int j=0;j<3;j++)
	{
		tmp=abs(password[cur][j]-combination[j]);
		dist=min(tmp,n-tmp);
		if(dist>2) return false;
	}
	return true;
}

int main()
{
	fstream fin("combo.in",ios::in);
	fstream fout("combo.out",ios::out);

	fin>>n;

	if(n<=5)
	{
		fout<<n*n*n<<endl;
		fin.close();
		fout.close();
		return 0;		
	}

	for(int i=0;i<2;i++) 
		for(int j=0;j<3;j++)
			fin>>password[i][j];

	int ans=0;
	
	for(int i=1;i<=n;i++)
	{
		combination[0]=i;
		for(int j=1;j<=n;j++)
		{
			combination[1]=j;
			for(int k=1;k<=n;k++)
			{
				combination[2]=k;
				if(is_available(0) || is_available(1))
					ans++;
			}
		}
	}

	fout<<ans<<endl;

	fin.close();
	fout.close();
	return 0;
}
