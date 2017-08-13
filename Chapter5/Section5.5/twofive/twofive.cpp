/*
ID: suzyzha1
PROG: twofive
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;
const int maxn = 6;
const int tot = 25;
int n;
char ch[30],s[30];
int f[maxn][maxn][maxn][maxn][maxn];

bool check(int pos,int depth)
{
	if(s[pos]==0 || s[pos]==depth+'A') return true;
	else return false;
}

int calc(int a,int b,int c,int d,int e,int depth)
{
	if(depth==tot) return 1;

	int &res=f[a][b][c][d][e];
	if(res) return res;

	if(a<5 && check(a,depth)) res+=calc(a+1,b,c,d,e,depth+1);
	if(b<a && check(b+5,depth)) res+=calc(a,b+1,c,d,e,depth+1);
	if(c<b && check(c+10,depth)) res+=calc(a,b,c+1,d,e,depth+1);
	if(d<c && check(d+15,depth)) res+=calc(a,b,c,d+1,e,depth+1);
	if(e<d && check(e+20,depth)) res+=calc(a,b,c,d,e+1,depth+1);

	return res;
}

int main()
{
	fstream fin("twofive.in",ios::in);
	fstream fout("twofive.out",ios::out);

	char t;
	fin>>t;
	if(t=='N')
	{
		fin>>n;
		n--;
		for(int i=0;i<tot;i++)
			for(char j='A';j<'Z';j++)
			{
				s[i]=j;
				memset(f,0,sizeof(f));
				int tmp=calc(0,0,0,0,0,0);
				if(tmp>n)
					break;
				else
					n-=tmp;
			}
		
		fout<<s<<endl;
	}
	else
	{
		fin>>ch;
		n=0;
		for(int i=0;i<tot;i++)
		{
			for(char j='A';j<ch[i];j++)
			{
				s[i]=j;
				memset(f,0,sizeof(f));
				n+=calc(0,0,0,0,0,0);
			}	
			s[i]=ch[i];		
		}

		n++;
		fout<<n<<endl;
	}

	fin.close();
	fout.close();
	return 0;
}