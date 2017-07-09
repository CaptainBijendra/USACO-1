/*
ID: suzyzha1
PROG: transform
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int maxn = 12;
int n;
string before[maxn],after[maxn];

bool transform1(string (*a)[maxn],string (*b)[maxn])
{
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if((*a)[i][j]!=(*b)[j][n-1-i])
				return false;

	return true;
}

bool transform2(string (*a)[maxn],string (*b)[maxn])
{
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if((*a)[i][j]!=(*b)[n-1-i][n-1-j])
				return false;

	return true;
}

bool transform3(string (*a)[maxn],string (*b)[maxn])
{
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if((*a)[i][j]!=(*b)[n-1-j][i])
				return false;

	return true;
}

bool transform4(string (*a)[maxn],string (*b)[maxn])
{
	for(int i=0;i<n;i++)
		for(int j=0;j<=(n/2);j++)
			if((*a)[i][j]!=(*b)[i][n-1-j])
				return false;

	return true;
}

bool transform5(string (*a)[maxn],string (*b)[maxn])
{
	string c[maxn];
	for(int i=0;i<n;i++) c[i].assign((*a)[i].rbegin(),(*a)[i].rend());

	return (transform1(&c,b) || transform2(&c,b) || transform3(&c,b));
}

bool transform6(string (*a)[maxn],string (*b)[maxn])
{
	for(int i=0;i<n;i++)
		if((*a)[i]!=(*b)[i])
			return false;
	return true;
}


int main()
{
	fstream fin("transform.in",ios::in);
	fstream fout("transform.out",ios::out);

	fin>>n;

	for(int i=0;i<n;i++) fin>>before[i];
	for(int i=0;i<n;i++) fin>>after[i];

	if(transform1(&before,&after)) fout<<1<<endl;
	else
	if(transform2(&before,&after)) fout<<2<<endl;
	else
	if(transform3(&before,&after)) fout<<3<<endl;
	else
	if(transform4(&before,&after)) fout<<4<<endl;
	else
	if(transform5(&before,&after)) fout<<5<<endl;
	else
	if(transform6(&before,&after)) fout<<6<<endl;
	else fout<<7<<endl;

	fin.close();
	fout.close();
	return 0;
}
