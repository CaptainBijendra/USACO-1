/*
ID: suzyzha1
PROG: cryptcow
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int maxn = 76;
const char t[] = "Begin the Escape execution at the Break of Dawn";
char s[maxn],backup[maxn],tmp1[maxn],tmp2[maxn];

int n,s_count[260],t_count[260];
bool match;

void swap_s(int a,int b,int c,int len)
{
	memcpy(tmp1,s+a+1,b-1-a);
	memcpy(tmp2,s+b+1,c-1-b);

	memcpy(s+a,tmp2,c-1-b);
	memcpy(s+a+c-1-b,tmp1,b-1-a);
	memcpy(s+c-2,s+c+1,len-c-1);
	s[len-3]=0;
}

void dfs(int len,int num)
{
	if(match || len<47) return;
	if(num==0)
	{
		if(strcmp(s,t)==0)
			match=true;
		
		return;
	}

	char backup[maxn];
	
	for(int i=0;i<len;i++)
		if(s[i]=='C')
		{
			for(int j=i+1;j<len;j++)
				if(s[j]=='O')
				{
					for(int k=j+1;k<len;k++)
						if(s[k]=='W')
						{
							memcpy(backup,s,n+1);
							swap_s(i,j,k,len);
							dfs(len-3,num-1);
							if(match) return;

							memcpy(s,backup,n+1);
						}
				}

			break;
		}
}

int main()
{
	fstream fin("cryptcow.in",ios::in);
	fstream fout("cryptcow.out",ios::out);

	string s1;
	getline(fin,s1);
	fin.close();

	int n=s1.length();
	for(int i=0;i<n;i++)
		s[i]=s1[i];
	s[n]=0;

	for(int i=0;i<n;i++)
		s_count[s[i]]++;

	if(s_count['C']!=s_count['O'] || s_count['O']!=s_count['W'] || s_count['C']!=s_count['W'] || n-3*s_count['C']!=47)
	{
		fout<<"0 0"<<endl;
		fout.close();
		return 0;
	}

	if(s_count['C']==0)
	{
		if(strcmp(s,t)==0)
			fout<<"1 0"<<endl;
		else
			fout<<"0 0"<<endl;
		fout.close();
		return 0;		
	}

	for(int i=0;i<47;i++) t_count[t[i]]++;

	bool flag=true;
	for(int i=0;i<255;i++)
	{
		if(i=='C' || i=='O' || i=='W')
			continue;
		if(s_count[i]!=t_count[i])
		{
			flag=false;
			break;
		}
	}
		

	if(flag)
		dfs(n,s_count['C']);

	if(match)
		fout<<"1 "<<s_count['C']<<endl;
	else
		fout<<"0 0"<<endl;

	fout.close();
	return 0;
}