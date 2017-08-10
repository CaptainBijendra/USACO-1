/*
ID: suzyzha1
PROG: charrec
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;
const int maxn = 5010;

int n;
class Node
{
public:
	int left,right;
	bool covered;

	Node(){ left=right=0; covered=false; }
	~Node();
};

struct Segment
{
	bool is_start;
	int st,en,key;

	Segment(int _st,int _en,int _key,bool _is_start):
		st(_st), en(_en), key(_key), is_start(_is_start) {}
} horizontal[maxn<<1],vertical[maxn<<1];

int main()
{
	fstream fin("picture.in",ios::in);
	fstream fout("picture.out",ios::out);

	int a,b,c,d;
	fin>>n;
	for(int i=0;i<n;i++)
	{
		fin>>a>>b>>c>>d;
		horizontal[(i<<1)]=Segment(a,c,b,true);
		horizontal[(i<<1)+1]=Segment(a,c,d,false);
		vertical[(i<<1)]=Segment(b,d,a,true);
		vertical[(i<<1)+1]=Segment(b,d,c,false);
	}

	sort(horizontal,horizontal+(n<<1),cmp1);
	sort(vertical,vertical+(n<<1),cmp2);

	for(int i=0;i<(n<<1);i++)
		tree.add(horizontal[i])

	fin.close();
	fout.close();
	return 0;
}