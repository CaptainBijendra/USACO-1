/*
ID: suzyzha1
PROG: calfflac
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;
const int maxn = 20002;

int n,ans,ans_st,ans_en;
int f[3][maxn];
string s1;
char s[maxn];

bool is_letter(char c)
{
	if(c>='a' && c<='z') return true;
	if(c>='A' && c<='Z') return true;
	return false;
}

bool same_letter(char a,char b)
{
	if(a==b) return true;
	if(a<='Z' && b==a+'a'-'A') return true;
	if(b<='Z' && a==b+'a'-'A') return true;
	return false;
}

int main()
{
	fstream fin("calfflac.in",ios::in);
	fstream fout("calfflac.out",ios::out);

	string tmp;
	while(!fin.eof())
	{
		std::getline(fin,tmp);
		if(fin.eof()) break;
		s1+=tmp;
		s1+="\n";
	}
	n=s1.length();
	for(int i=0;i<n;i++) s[i]=s1[i];

	ans=1; ans_st=ans_en=0;

	int k,st,en;
	for(int i=0;i<n;i++)
	{
		if(is_letter(s[i]))
			k=1;
		else
			k=0;
		st=i-1; en=i+1;
		while(st>=0 && en<n)
		{
			if(!is_letter(s[st]) && !is_letter(s[en]))
			{
				st--;
				en++;				
			}
			else
			if(!is_letter(s[st]))
				st--;
			else
			if(!is_letter(s[en]))
				en++;
			else
			{
				if(same_letter(s[st],s[en]))
				{
					k+=2;
					st--;
					en++;
				}
				else
					break;
			}
		}
		st++;
		en--;

		if(k>ans || (k==ans && st<ans_st))
		{
			ans=k;
			ans_st=st;
			ans_en=en;
		}

		k=0;
		st=i; en=i+1;
		while(st>=0 && en<n)
		{
			if(!is_letter(s[st]) && !is_letter(s[en]))
			{
				st--;
				en++;
			}
			else
			if(!is_letter(s[st]))
				st--;
			else
			if(!is_letter(s[en]))
				en++;
			else
			{
				if(same_letter(s[st],s[en]))
				{
					k+=2;
					st--;
					en++;
				}
				else
					break;
			}
		}
		
		st++;
		en--;
		if(k>ans || (k==ans && st<ans_st))
		{
			ans=k;
			ans_st=st;
			ans_en=en;
		}
	}

	fout<<ans<<endl;
	while(!is_letter(s[ans_st]) && ans_st<ans_en) ans_st++;
	while(!is_letter(s[ans_en]) && ans_st<ans_en) ans_en--;
	for(int i=ans_st;i<=ans_en;i++)
		fout<<s[i];
	fout<<endl;

	fin.close();
	fout.close();
	return 0;
}