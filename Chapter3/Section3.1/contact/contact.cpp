/*
ID: suzyzha1
PROG: contact
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

int n,st,en;
string s;
int freq[13][4100];

int num=0;
struct Pattern
{
	int len,val,frequncy;
} patterns[49500];

int print_count=0;

bool cmp(Pattern a,Pattern b)
{
	if(a.frequncy>b.frequncy) return true;
	if(a.frequncy<b.frequncy) return false;

	if(a.len<b.len) return true;
	if(a.len>b.len) return false;

	if(a.val<b.val) return true;
	return false;
}

void print(int l,int v,fstream *f)
{
	for(int i=l-1;i>=0;i--)
		if(v&(1<<i))
			*f<<'1';
		else
			*f<<'0';

	print_count++;
	if(print_count==6)
	{
		*f<<endl;
		print_count=0;
	}
}

int main()
{
	fstream fin("contact.in",ios::in);
	fstream fout("contact.out",ios::out);

	fin>>st>>en>>n;

	string stmp;
	while(true)
	{
		fin>>stmp;
		if(fin.eof()) break;
		s+=stmp;
	}

	int sl=s.length(),tmp;
	for(int i=0;i<=sl-st;i++)
	{
		tmp=0;
		for(int j=0;j<st;j++)
			tmp=(tmp<<1)+s[i+j]-'0';

		for(int j=st;j<=en;j++)
		{
			if(i+j-1>=sl) break;

			freq[j][tmp]++;

			if(j==en) break;
			tmp=(tmp<<1)+s[i+j]-'0';
		}
	}

	for(int i=st;i<=en;i++)
		for(int j=0;j<(1<<i);j++)
			if(freq[i][j])
			{
				patterns[num].len=i;
				patterns[num].val=j;
				patterns[num].frequncy=freq[i][j];
				num++;
			}

	sort(patterns,patterns+num,cmp);

	int j=0;
	for(int i=0;i<n && j<num;i++)
	{
		print_count=0;
		fout<<patterns[j].frequncy<<endl;
		print(patterns[j].len,patterns[j].val,&fout);
		j++;
		while(j<num && patterns[j].frequncy==patterns[j-1].frequncy)
		{
			if(print_count>0) fout<<" ";
			print(patterns[j].len,patterns[j].val,&fout);
			j++;
		}
		if(print_count>0)
			fout<<endl;
	}
	
	fin.close();
	fout.close();
	return 0;
}