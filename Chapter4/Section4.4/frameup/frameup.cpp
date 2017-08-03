/*
ID: suzyzha1
PROG: frameup
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

const int maxn = 32;

int n,m,num;
char board[maxn][maxn];
bool g[maxn][maxn],used[maxn];
int under[maxn],now[maxn];

class Frame
{
public:
	char ch;
	int top,bottom,left,right;
	void init(char c,int a,int b)
	{
		ch=c;
		top=bottom=a;
		left=right=b;
	}

	void update(int a,int b,int c,int d)
	{
		top=min(top,a);
		bottom=max(bottom,b);
		left=min(left,c);
		right=max(right,d);
	}
} frames[30];

bool cmp(const Frame &a,const Frame &b)
{
	return (a.ch<b.ch);
}

bool find(int a,int b) /* return true if Frame b is on top of Frame a */
{
	int x1=frames[a].top,x2=frames[a].bottom,tar=frames[b].ch;
	for(int j=frames[a].left;j<=frames[a].right;j++)
		if(board[x1][j]==tar || board[x2][j]==tar)
			return true;

	int y1=frames[a].left,y2=frames[a].right;
	for(int i=frames[a].top;i<=frames[a].bottom;i++)
		if(board[i][y1]==tar || board[i][y2]==tar)
			return true;

	return false;
}

void generate(int cur,fstream *fout)
{
	if(cur>num)
	{
		for(int i=1;i<=num;i++)
			(*fout)<<frames[now[i]].ch;
		(*fout)<<endl;

		return;
	}

	for(int i=1;i<=num;i++)
		if(under[i]==0 && !used[i])
		{
			now[cur]=i;
			used[i]=true;
			for(int j=1;j<=num;j++)
				if(g[i][j])
					under[j]--;

			generate(cur+1,fout);

			for(int j=1;j<=num;j++)
				if(g[i][j])
					under[j]++;
			used[i]=false;
		}
}

int main()
{
	fstream fin("frameup.in",ios::in);
	fstream fout("frameup.out",ios::out);

	fin>>n>>m;
	num=0;
	int idx;
	for(int i=0;i<n;i++)
	{
		fin>>board[i];
		for(int j=0;j<m;j++)
			if(board[i][j]!='.')
			{
				idx=0;
				for(int k=1;k<=num;k++)
					if(frames[k].ch==board[i][j])
					{
						idx=k;
						break;
					}

				if(idx==0)
				{
					num++;
					frames[num].init(board[i][j],i,j);
				}
				else
					frames[idx].update(i,i,j,j);
			}
	}

	sort(frames+1,frames+num+1,cmp);

	for(int i=1;i<=num;i++)
		for(int j=1;j<=num;j++)
			if(i!=j)
			{
				g[i][j]=find(i,j);
				under[j]+=g[i][j];
			}

	generate(1,&fout);

	fout.close();
	return 0;
}