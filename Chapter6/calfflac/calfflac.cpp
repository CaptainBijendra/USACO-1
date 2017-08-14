/*
ID: suzyzha1
PROG: calfflac
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;
const int maxn = 20002;

char s[maxn];


int main()
{
	fstream fin("calfflac.in",ios::in);
	fstream fout("calfflac.out",ios::out);

	fin>>n;


	fin.close();
	fout.close();
	return 0;
}