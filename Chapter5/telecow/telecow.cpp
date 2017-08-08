/*
ID: suzyzha1
PROG: telecow
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
const int maxn = 102;

int n,m;


int main()
{
	fstream fin("telecow.in",ios::in);
	fstream fout("telecow.out",ios::out);

	fin>>n>>m;

	fout<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}