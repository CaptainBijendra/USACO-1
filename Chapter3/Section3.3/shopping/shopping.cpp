/*
ID: suzyzha1
PROG: shopping
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>

using namespace std;

const int maxs = 100;
const int maxm = 6;

int s;
struct Offer
{
	int n,price;
	int code[maxm],num[1002];
} offers[maxs];

int m;
int codes[maxm],req[maxm],reg_price[maxm];

int f[maxm][maxm][maxm][maxm][maxm];

int main()
{
	fstream fin("shopping.in",ios::in);
	fstream fout("shopping.out",ios::out);

	fin>>s;
	int tmp;
	for(int i=0;i<s;i++)
	{
		fin>>offers[i].n;
		for(int j=0;j<offers[i].n;j++)
		{
			fin>>tmp;
			fin>>offers[i].num[tmp];
		}
		fin>>offers[i].price;
	}

	fin>>m;
	for(int i=0;i<m;i++)
		fin>>codes[i]>>req[i]>>reg_price[i];

	f[0][0][0][0][0]=0;
	for(int i=0;i<=req[0];i++)
		for(int j=0;j<=req[1];j++)
			for(int k=0;k<=req[2];k++)
				for(int p=0;p<=req[3];p++)
					for(int q=0;q<=req[4];q++)
					{
						if(i==0 && j==0 && k==0 && p==0 && q==0)
							continue;

						f[i][j][k][p][q]=i*reg_price[0]+j*reg_price[1]+k*reg_price[2]+p*reg_price[3]+q*reg_price[4];
						for(int t=0;t<s;t++)
						{
							if(    offers[t].num[codes[0]]>i || offers[t].num[codes[1]]>j
								|| offers[t].num[codes[2]]>k || offers[t].num[codes[3]]>p
								|| offers[t].num[codes[4]]>q) 
								continue;

							tmp=f[i-offers[t].num[codes[0]]][j-offers[t].num[codes[1]]]
								[k-offers[t].num[codes[2]]][p-offers[t].num[codes[3]]]
								[q-offers[t].num[codes[4]]]+offers[t].price;

							if(tmp<f[i][j][k][p][q]) f[i][j][k][p][q]=tmp;
						}
					}
	
	fout<<f[req[0]][req[1]][req[2]][req[3]][req[4]]<<endl;
	fin.close();
	fout.close();
	return 0;
}