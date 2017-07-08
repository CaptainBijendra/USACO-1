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

bool transform6()
{
	for(int i=0;i<n;i++)
		if(before[i]!=after[i])
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

	if(transform1()) fout<<1<<endl;
	else
	if(transform2()) fout<<2<<endl;
	else
	if(transform3()) fout<<3<<endl;
	else
	if(transform4()) fout<<4<<endl;
	else
	if(transform5()) fout<<5<<endl;
	else
	if(transform6()) fout<<6<<endl;
	else fout<<7<<endl;

	fin.close();
	fout.close();
	return 0;
}
