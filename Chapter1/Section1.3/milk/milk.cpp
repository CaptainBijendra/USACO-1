/*
ID: suzyzha1
PROG: milk
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

const int maxm = 5010;

int n,m,ans=0;

struct Farmer
{
	int price;
	int amount;
};
Farmer farmers[maxm];

void qs(int l,int r)
{
	if(l>=r) return;
	if(l+1==r)
	{
		Farmer tmp;
		if(farmers[l].price>farmers[r].price)
		{
			tmp=farmers[l]; farmers[l]=farmers[r]; farmers[r]=tmp;
		}
		return;
	}

	int idx=l;
	Farmer tmp;
	for(int i=l;i<r;i++)
		if(farmers[i].price<=farmers[r].price)
		{
			if(i!=idx)
			{
				tmp=farmers[i]; farmers[i]=farmers[idx]; farmers[idx]=tmp;
			}
			idx++;
		}

	if(idx<r)
	{
		tmp=farmers[r]; farmers[r]=farmers[idx]; farmers[idx]=tmp;
	}

	qs(l,idx-1);
	qs(idx+1,r);
}

int main()
{
	fstream fin("milk.in",ios::in);
	fstream fout("milk.out",ios::out);

	fin>>n>>m;

	for(int i=0;i<m;i++)
		fin>>farmers[i].price>>farmers[i].amount;

	qs(0,m-1);
	
	ans=0;
	for(int i=0;i<m;i++)
		if(farmers[i].amount<=n)
		{
			n-=farmers[i].amount;
			ans+=farmers[i].amount*farmers[i].price;
		}
		else
		{
			ans+=n*farmers[i].price;
			break;
		}

	fout<<ans<<endl;
	
	fin.close();
	fout.close();
	return 0;
}
