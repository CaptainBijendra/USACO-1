/*
ID: suzyzha1
PROG: cryptcow
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int maxn = 100;
const char t[] = "Begin the Escape execution at the Break of Dawn";
char s[maxn],backup[maxn],tmp1[maxn],tmp2[maxn];

int n,s_count[300],t_count[300];
bool match;

void swap_s(int a,int b,int c,int len)
{
	memmove(tmp1,s+a+1,b-1-a);
	memmove(tmp2,s+b+1,c-1-b);

	memmove(s+a,tmp2,c-1-b);
	memmove(s+a+c-1-b,tmp1,b-1-a);
	memmove(s+c-2,s+c+1,len-c-1);
	s[len-3]=0;
}

bool my_strstr(char *p,int l)
{
	bool flag;
	for(int i=0;i<47;i++)
		if(t[i]==p[0])
		{
			flag=true;
			for(int j=0;j<l;j++)
				if(t[i+j]!=p[j])
				{
					flag=false;
					break;
				}
			if(flag) return true;
		}

	return false;
}

void dfs(int len,int num)
{
	//printf("s:%s len:%d num:%d\n",s,len,num );
	if(match || len<47) return;
	if(num==0)
	{
		if(strcmp(s,t)==0)
			match=true;
		
		return;
	}

	int pos[3][10],idx[30];
	pos[0][0]=pos[1][0]=pos[2][0]=idx[0]=0;
	for(int i=0;i<len;i++)
		if(s[i]=='O')
		{
			pos[0][0]++;
			pos[0][pos[0][0]]=i;
			idx[0]++;
			idx[idx[0]]=i;
		}
		else
		if(s[i]=='C')
		{
			pos[1][0]++;
			pos[1][pos[1][0]]=i;
			idx[0]++;
			idx[idx[0]]=i;
		}
		else
		if(s[i]=='W')
		{
			pos[2][0]++;
			pos[2][pos[2][0]]=i;
			idx[0]++;
			idx[idx[0]]=i;
		}

	if(pos[1][1]>pos[0][1] || pos[1][1]>pos[2][1] || pos[2][num]<pos[0][1])
		return;

	if(pos[1][1]>0 && strncmp(s,t,pos[1][1])!=0) /* first segment */
		return;

	if(pos[2][1]<len && strcmp(s+pos[2][num]+1,t+48-len+pos[2][num])!=0) /* last segment */
		return;

	for(int i=0;i<idx[0];i++)
		if(idx[i]+1<idx[i+1])
		{
			if(!my_strstr(s+idx[i]+1,idx[i+1]-idx[i]-1))
				return;
		}

	char backup[maxn];
	memcpy(backup,s,n+1);
	
	for(int i=1;i<=num;i++)
		for(int j=1;j<=num;j++)
			if(pos[0][i]>pos[1][j])
				for(int k=num;k>=1;k--)
				{
					if(pos[2][k]<=pos[0][i]) break;

					swap_s(pos[1][j],pos[0][i],pos[2][k],len);
					dfs(len-3,num-1);

					memcpy(s,backup,n+1);
				}
}

int main()
{
	fstream fin("cryptcow.in",ios::in);
	fstream fout("cryptcow.out",ios::out);

	string s1;
	getline(fin,s1);
	fin.close();

	n=s1.length();
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