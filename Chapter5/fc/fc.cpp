/*
ID: suzyzha1
PROG: fc
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <iomanip>

using namespace std;
const int maxn = 10002;


int main()
{
	fstream fin("fc.in",ios::in);
	fstream fout("fc.out",ios::out);

	fin>>n;
	for(int i=1;i<=n;i++)
		fin>>spot[i].x>>spot[i].y;

		
	
	fout<<setprecision(6)<<ans<<endl;
	fin.close();
	fout.close();
	return 0;
}