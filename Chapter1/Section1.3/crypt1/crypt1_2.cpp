/*
ID: suzyzha1
PROG: crypt1
LANG: C++
*/

#include <iostream>
#include <fstream>

using namespace std;

int n;
int digits[20];
bool available[10];

bool is_legal(int a)
{
	while(a>0)
	{
		if(!available[a%10]) return false;
		a/=10;
	}
	return true;
}

int main()
{
	fstream fin("crypt1.in",ios::in);
	fstream fout("crypt1.out",ios::out);

	fin>>n;

	for(int i=0;i<10;i++) available[i]=false;

	for(int i=0;i<n;i++)
	{
		fin>>digits[i];
		available[digits[i]]=true;
	} 

	int ans=0;
	int num1,num2,p1,p2,sum;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<n;k++)
			{
				num1=digits[i]+digits[j]*10+digits[k]*100;
				for(int s=0;s<n;s++)
				{
					p1=num1*digits[s];
					if(p1>=1000 || !is_legal(p1))
							continue;

					for(int t=0;t<n;t++)
					{
						p2=num1*digits[t];
						if(p2>=1000 || !is_legal(p2))
							continue;

						num2=digits[s]+digits[t]*10;
						sum=num1*num2;
						if(sum>=1000 && sum<10000 && is_legal(sum))	
							ans++;
					}
				}
			}
		}
	}

	fout<<ans<<endl;
	
	fin.close();
	fout.close();
	return 0;
}
