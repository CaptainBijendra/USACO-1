/*
ID: suzyzha1
PROG: preface
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int n;
int letter_count[10];

const char roman[] = {'I','V','X','L','C','D','M'};

int letter_index[100];

void get_roman(int num)
{
	if(num>=1000)
	{
		letter_count[letter_index['M']]+=num/1000;
		num%=1000;
	}

	if(num>=900)
	{
		letter_count[letter_index['M']]++;
		letter_count[letter_index['C']]++;
		num-=900;
	}
	else
	if(num>=500)
	{
		letter_count[letter_index['D']]++;
		letter_count[letter_index['C']]+=(num-500)/100;
		num%=100;
	}
	else
	if(num>=400)
	{
		letter_count[letter_index['D']]++;
		letter_count[letter_index['C']]++;
		num%=100;
	}
	else
	if(num>=100)
	{
		letter_count[letter_index['C']]+=num/100;
		num%=100;
	}

	if(num>=90)
	{
		letter_count[letter_index['C']]++;
		letter_count[letter_index['X']]++;
		num%=10;
	}
	else
	if(num>=50)
	{
		letter_count[letter_index['L']]++;
		letter_count[letter_index['X']]+=(num-50)/10;
		num%=10;
	}
	else
	if(num>=40)
	{
		letter_count[letter_index['L']]++;
		letter_count[letter_index['X']]++;
		num%=10;
	}
	else
	if(num>=10)
	{
		letter_count[letter_index['X']]+=num/10;
		num%=10;
	}

	if(num==9)
	{
		letter_count[letter_index['X']]++;
		letter_count[letter_index['I']]++;
	}
	else
	if(num>=4)
	{
		letter_count[letter_index['V']]++;
		letter_count[letter_index['I']]+=abs(num-5);
	}
	else
		letter_count[letter_index['I']]+=num;
}

int main()
{
	fstream fin("preface.in",ios::in);
	fstream fout("preface.out",ios::out);

	fin>>n;
	fin.close();

	for(int i=0;i<7;i++)
		letter_index[roman[i]]=i;

	for(int i=1;i<=n;i++)
		get_roman(i);

	for(int i=0;i<7;i++)
		if(letter_count[i])
			fout<<roman[i]<<" "<<letter_count[i]<<endl;
	
	fout.close();
	return 0;
}
