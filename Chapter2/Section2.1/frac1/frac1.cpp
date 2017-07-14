/*
ID: suzyzha1
PROG: frac1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

int n;

struct Fraction
{
	int denominator,numerator;
	double value;
};

int num=0;
Fraction fracs[13000];

bool cmp(Fraction a,Fraction b)
{
	return a.value<b.value;
}

int gcd(int a,int b)
{
	if(a%b==0) return b;
	return gcd(b,a%b);
}

int main()
{
	fstream fin("frac1.in",ios::in);
	fstream fout("frac1.out",ios::out);

	fin>>n;
	fin.close();

	num=2;
	fracs[0].denominator=fracs[1].denominator=fracs[1].numerator=fracs[1].value=1;
	fracs[0].numerator=fracs[0].value=0;
	for(int i=2;i<=n;i++)
		for(int j=1;j<i;j++)
			if(gcd(i,j)==1)
			{
				fracs[num].denominator=i;
				fracs[num].numerator=j;
				fracs[num].value=1.0*j/i;
				num++;
			}

	sort(fracs,fracs+num,cmp);

	for(int i=0;i<num;i++)
		fout<<fracs[i].numerator<<"/"<<fracs[i].denominator<<endl;
	
	fout.close();
	return 0;
}
