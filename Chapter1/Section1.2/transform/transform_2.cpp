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

struct Board
{
	string c[maxn];
};

Board before,after;

Board rotate(Board a)
{
	Board b;
	for(int i=0;i<n;i++) b.c[i]=a.c[i];

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			b.c[j][n-1-i]=a.c[i][j];

	return b;
}

Board reflect(Board a)
{
	Board b;
	for(int i=0;i<n;i++) b.c[i]=a.c[i];

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			b.c[i][j]=a.c[i][n-1-j];

	return b;
}

bool identical(Board a,Board b)
{
	for(int i=0;i<n;i++)
		if(a.c[i]!=b.c[i])
			return false;
	return true;
}


int main()
{
	fstream fin("transform.in",ios::in);
	fstream fout("transform.out",ios::out);

	fin>>n;

	for(int i=0;i<n;i++) fin>>before.c[i];
	for(int i=0;i<n;i++) fin>>after.c[i];

	if(identical(after,rotate(before))) fout<<1<<endl;
	else
	if(identical(after,rotate(rotate(before)))) fout<<2<<endl;
	else
	if(identical(after,rotate(rotate(rotate(before))))) fout<<3<<endl;
	else
	if(identical(after,reflect(before))) fout<<4<<endl;
	else
	if(identical(after,rotate(reflect(before)))
		|| identical(after,rotate(rotate(reflect(before))))
		|| identical(after,rotate(rotate(rotate(reflect(before))))))
		 fout<<5<<endl;
	else
	if(identical(before,after)) fout<<6<<endl;
	else fout<<7<<endl;

	fin.close();
	fout.close();
	return 0;
}
