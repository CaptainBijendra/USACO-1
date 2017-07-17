/*
ID: suzyzha1
PROG: prefix
LANG: C++
*/

/* This solution uses Trie tree to store the dictionary of primitives. */

#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <climits>

using namespace std;

int n=0;
struct TrieNode
{
	bool is_word;
	struct TrieNode *next[26];	
};

TrieNode dict;

string s;
bool available[200002];

void print(TrieNode *p,string cur)
{
	if(p==NULL)
		return;
	if(p->is_word)
		cout<<cur<<endl;

	for(int i=0;i<26;i++)
		if(p->next[i]!=NULL)
			print(p->next[i],cur+(char)(i+'A'));

}

int main()
{
	fstream fin("prefix.in",ios::in);
	fstream fout("prefix.out",ios::out);

	string tmp;
	TrieNode *p;
	while(true)
	{
		fin>>tmp;
		if(tmp.compare(".")==0) break;

		p=&dict;
		for(int i=0;i<tmp.length();i++)
		{
			if(p->next[tmp[i]-'A']==NULL)
			{
				p->next[tmp[i]-'A']=new TrieNode;
				p=p->next[tmp[i]-'A'];
				memset(p->next,0,sizeof(p->next));
			}
			else
				p=p->next[tmp[i]-'A'];
		}
		p->is_word=true;
	}

	while(true)
	{
		fin>>tmp;
		if(fin.eof()) break;

		s+=tmp;
	}
	fin.close();

	//print(&dict,"");

	int len=s.length();
	int cur_max=-1,j;
	for(int i=-1;i<len-1 && i<=cur_max;i++)
	{
		if(i>-1 && !available[i]) continue;

		p=&dict;
		j=i+1;
		while(j<len && p->next[s[j]-'A']!=NULL)
		{
			p=p->next[s[j]-'A'];
			if(p->is_word)
			{
				available[j]=true;
				cur_max=j>cur_max ? j:cur_max;
			}
			j++;
		}
	}

	fout<<cur_max+1<<endl;

	fout.close();
	return 0;
}
