/*
ID: suzyzha1
PROG: sprime
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

int n;

bool is_prime(int cur)
{
	if(cur==1) return false;
	if(cur==2) return true;

	int lim=sqrt(cur)+1;
	for(int i=2;i<=lim;i++)
		if(cur%i==0)
			return false;
	return true;
}

void generate_sprime(int cur,int num,fstream *fout)
{
	if(cur>n)
	{
		*fout<<num<<endl;
		return;
	}

	for(int i=1;i<=9;i++)
		if(is_prime(num*10+i))
			generate_sprime(cur+1,num*10+i,fout);
}

int main()
{
	fstream fin("sprime.in",ios::in);
	fstream fout("sprime.out",ios::out);


	fin>>n;

	generate_sprime(1,0,&fout);

	fin.close();
	fout.close();
	return 0;
}
