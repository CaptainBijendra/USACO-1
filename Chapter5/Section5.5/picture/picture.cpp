/*
ID: suzyzha1
PROG: picture
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;
const int maxn = 5010;
const int base = 10000;

int n,ans;
int level[2*base+10];

struct segment
{
	bool is_start;
	int st,en,key;

	segment() { st=en=key=0; is_start=false; }
	segment(int _st,int _en,int _key,bool _is_start)
	{ 	st=_st; en=_en; key=_key; is_start=_is_start; }

} horizontal[3*maxn],vertical[maxn*3];

bool cmp(const segment &a,const segment &b)
{
	if(a.key<b.key) return true;
	if(a.key>b.key) return false;
	if(a.is_start) return true;
	return false;
}

void heap_adjust(segment *d,int x,int max)
{
	int cur=x,l=x<<1;
	int r=l+1,best;
	segment tmp;

	while(l<=max)
	{
		if(cmp(d[cur],d[l])) best=l;
		else best=cur;

		if(r<=max)
			if(cmp(d[best],d[r])) best=r;

		if(cur==best) return;

		tmp=d[cur]; d[cur]=d[best]; d[best]=tmp;
		cur=best;
		l=cur<<1;
		r=l+1;
	}
}

void heap_sort(segment *d,int size)
{
	for(int i=(size>>1);i>=1;i--)
		heap_adjust(d,i,size);

	segment tmp;
	for(int i=size;i>1;i--)
	{
		tmp=d[1]; d[1]=d[i]; d[i]=tmp;
		heap_adjust(d,1,i-1);
	}
}

int main()
{
	fstream fin("picture.in",ios::in);
	fstream fout("picture.out",ios::out);

	int a,b,c,d;
	fin>>n;
	for(int i=1;i<=n;i++)
	{
		fin>>a>>b>>c>>d;
		horizontal[(i<<1)-1]=segment(a,c,b,true);
		horizontal[(i<<1)]=segment(a,c,d,false);
		vertical[(i<<1)-1]=segment(b,d,a,true);
		vertical[(i<<1)]=segment(b,d,c,false);
	}

	heap_sort(horizontal,n<<1);
	heap_sort(vertical,n<<1);

	for(int i=1;i<=(n<<1);i++)
		if(horizontal[i].is_start)
			for(int j=horizontal[i].st;j<horizontal[i].en;j++)
			{
				if(level[j+base]==0) ans++;
				level[j+base]++;
			}
		else
			for(int j=horizontal[i].st;j<horizontal[i].en;j++)
			{
				level[j+base]--;
				if(level[j+base]==0) ans++;
			}

	memset(level,0,sizeof(level));

	for(int i=1;i<=(n<<1);i++)
		if(vertical[i].is_start)
			for(int j=vertical[i].st;j<vertical[i].en;j++)
			{
				if(level[j+base]==0) ans++;
				level[j+base]++;
			}
		else
			for(int j=vertical[i].st;j<vertical[i].en;j++)
			{
				level[j+base]--;
				if(level[j+base]==0) ans++;
			}

	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}