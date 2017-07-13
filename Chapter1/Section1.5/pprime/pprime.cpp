/*
ID: suzyzha1
PROG: pprime
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

int st,en;
int digits[20];

bool is_prime(int cur)
{
	int lim=sqrt(cur)+1;
	for(int i=3;i<=lim;i++)
		if(cur%i==0)
			return false;
	return true;
}

void generate_palindrome(int cur,int num_of_digits,fstream *fout)
{
	if(cur>(1+num_of_digits)/2)
	{
		int w=1,sum=0;
		for(int i=1;i<=(num_of_digits+1)/2;i++)
		{
			sum+=w*digits[i];
			w*=10;
		}
		for(int i=num_of_digits/2;i>=1;i--)
		{
			sum+=w*digits[i];
			w*=10;
		}
		
		if(sum<st || sum>en) return;
		if(is_prime(sum)) (*fout)<<sum<<endl;
		return;
	}

	if(cur==1)
		for(int i=1;i<=9;i+=2)
		{
			digits[cur]=i;
			generate_palindrome(cur+1,num_of_digits,fout);
		}
	else
		for(int i=0;i<=9;i++)
		{
			digits[cur]=i;
			generate_palindrome(cur+1,num_of_digits,fout);
		}
}

int main()
{
	fstream fin("pprime.in",ios::in);
	fstream fout("pprime.out",ios::out);

	fin>>st>>en;
	if(st%2==0) st++;
	if(en%2==0) en--;

	int d1=0,d2=0;
	int t1=st,t2=en;
	while(t1>0)
	{
		d1++;
		t1/=10;
	}
	while(t2>0)
	{
		d2++;
		t2/=10;
	}

	for(int i=d1;i<=d2;i++)
		generate_palindrome(1,i,&fout);

	fin.close();
	fout.close();
	return 0;
}
