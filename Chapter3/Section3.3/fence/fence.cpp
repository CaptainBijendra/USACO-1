/*
ID: suzyzha1
PROG: fence
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;

const int maxf = 1030;

int f;
int st[maxf],en[maxf];

int main()
{
	fstream fin("fence.in",ios::in);
	fstream fout("fence.out",ios::out);

	fin>>f;
	for(int i=0;i<f;i++) fin>>st[i]>>en[i];
	
	fin.close();
	fout.close();
	return 0;
}