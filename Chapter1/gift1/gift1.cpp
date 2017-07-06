/*
ID: suzyzha1
PROG: gift1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int n;
string friends[12];

int main()
{
	fstream fin("gift1.in",ios::in);
	fstream fout("gift1.out",ios::out);

	fin>>n;
	for(int i=0;i<n;i++) fin>>friends[i];

	string cur;
	for(int i=0;i<n;i++)
	{
		fin>>cur;
		
	}

	fin.close();
	fout.close();
	return 0;
}
