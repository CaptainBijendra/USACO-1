/*
ID: suzyzha1
PROG: runround
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

int n;
int digits[12],len;
bool vis[12],used[10];

bool runround(int cur)
{
	len=0;
	int i=cur;
	memset(used,0,sizeof(used));
	while(i>0)
	{
		len++;
		if(i%10==0 || used[i%10]) return false;
		digits[len]=i%10;
		used[i%10]=true;
		i/=10;
	}

	i=len;
	int tmp;
	memset(vis,0,sizeof(vis));
	while(1)
	{
		if(vis[i])
		{
			if(i!=len)
				return false;
			
			for(int j=1;j<len;j++)
				if(!vis[j])
					return false;

			return true;
		}
		vis[i]=true;
		tmp=i;
		i-=digits[i];
		while(i<=0) i+=len;
		if(digits[tmp]==digits[i]) return false;
	}
}

int main()
{
	fstream fin("runround.in",ios::in);
	fstream fout("runround.out",ios::out);

	fin>>n;
	fin.close();
	
	for(int i=n+1;i<=INT_MAX;i++)
		if(runround(i))
		{
			fout<<i<<endl;
			break;
		}
	
	fout.close();
	return 0;
}
