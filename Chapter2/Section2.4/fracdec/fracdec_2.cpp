/*
ID: suzyzha1
PROG: fracdec 
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

int bit_count=0;
fstream fout("fracdec.out",ios::out);

int num_before_repeat(int n,int d)
{
	int c2=0,c5=0;
	while(d%2==0){ d/=2; c2++; }
	while(d%5==0){ d/=5; c5++; }
	while(n%2==0){ n/=2; c2--; }
	while(n%5==0){ n/=5; c5--; }

	int m=c2>c5 ? c2:c5;
	return (m>0 ? m:0);
}

void print(char c)
{
	fout<<c;
	bit_count++;
	if(bit_count==76)
	{
		bit_count=0;
		fout<<endl;
	}
}

void print(int num)
{
	if(num>9) print(num/10);
	print((char)('0'+num%10));
}
int main()
{
	fstream fin("fracdec.in",ios::in);

	int n,d;
	fin>>n>>d;
	fin.close();
	print(n/d);
	print('.');

	if(n%d==0)
	{
		fout<<"0"<<endl;
		fin.close();
		fout.close();
		return 0;
	}

	n%=d;
	int m=num_before_repeat(n,d);
	
	for(int i=0;i<m;i++)
	{
		n*=10;
		print(n/d);
		n%=d;
	}

	int r=n;
	if(r>0)
	{
		print('(');
		do{
			n*=10;
			print(n/d);
			n%=d;
		}while(n!=r);
		print(')');
	}
	if(bit_count!=0) fout<<endl;

	fout.close();
	return 0;
}