/*
ID: suzyzha1
PROG: zerosum
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

int n;

struct Expression
{
	char s[10];
};

Expression cur_plan;

int idx=0;
Expression ans[6500];

int calc()
{
	int res=0,tmp=1,flag=1;
	for(int i=0;i<n-1;i++)
	{
		switch(cur_plan.s[i])
		{
			case ' ':
				tmp=tmp*10+i+2;
				break;
			case '+':
				res+=tmp*flag;
				flag=1;
				tmp=i+2;
				break;
			case '-':
				res+=tmp*flag;
				flag=-1;
				tmp=i+2;
				break;				
		}
	}
	if(tmp!=0)
		res+=tmp*flag;

	return res;
}

void dfs(int pos)
{
	if(pos>=n-1)
	{
		if(calc()==0)
		{
			ans[idx]=cur_plan;
			idx++;
		}
		return;
	}

	cur_plan.s[pos]=' ';
	dfs(pos+1);

	cur_plan.s[pos]='+';
	dfs(pos+1);

	cur_plan.s[pos]='-';
	dfs(pos+1);
}

int main()
{
	fstream fin("zerosum.in",ios::in);
	fstream fout("zerosum.out",ios::out);

	fin>>n;
	fin.close();

	dfs(0);

	for(int i=0;i<idx;i++)
	{
		fout<<1;
		for(int j=0;j<n-1;j++)
			fout<<ans[i].s[j]<<(j+2);
		fout<<endl;
	}

	fout.close();
	return 0;
}
