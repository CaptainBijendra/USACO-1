/*
ID: suzyzha1
PROG: ride
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	fstream fin("ride.in",ios::in);
	fstream fout("ride.out",ios::out);

	string comet,group;

	fin>>comet>>group;

	int t1=1,t2=1;
	for(int i=0;i<comet.length();i++)
		t1=(t1*(comet[i]-'A'+1))%47;

	for(int i=0;i<group.length();i++)
		t2=(t2*(group[i]-'A'+1))%47;

	if(t1==t2) fout<<"GO"<<endl;
	else fout<<"STAY"<<endl;

	fin.close();
	fout.close();
	return 0;
}
