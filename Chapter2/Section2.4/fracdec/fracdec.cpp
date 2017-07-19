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

const int maxd = 100002;

int n,d;
int first_pos[maxd];
int idx=0,ans[maxd];

int main()
{
	fstream fin("fracdec.in",ios::in);
	fstream fout("fracdec.out",ios::out);

	fin>>n>>d;
	fin.close();
	fout<<n/d<<".";

	if(n%d==0)
	{
		fout<<"0"<<endl;
		fin.close();
		fout.close();
		return 0;
	}

	int rem=n%d,next,st;
	int bits=2;
	if(n>=d) bits+=(int)log10(n/d); 
	bool repeat=false;

	idx=1;
	while(rem!=0)
	{
		first_pos[rem]=idx;
		ans[idx]=10*rem/d;
		idx++;

		rem=10*rem%d;
		if(first_pos[rem]>0)
		{
			repeat=true;
			st=first_pos[rem];
			break;
		}
	}
	
	for(int i=1;i<idx;i++)
	{
		if(repeat && st==i)
		{
			fout<<"(";
			bits++;
			if(bits==76)
			{
				bits=0;
				fout<<endl;
			}
		}
		fout<<ans[i];
		bits++;
		if(bits==76)
		{
			bits=0;
			fout<<endl;
		}
	}

	if(repeat)
	{
		fout<<")";
		bits++;
	}
	if(bits>0)
		fout<<endl;

	fout.close();
	return 0;
}