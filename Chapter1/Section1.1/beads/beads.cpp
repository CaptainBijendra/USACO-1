/*
ID: suzyzha1
PROG: beads
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int n,ans;
string beads;

int main()
{
	fstream fin("beads.in",ios::in);
	fstream fout("beads.out",ios::out);

	fin>>n>>beads;

	ans=2;
	int tmp,j,lim;
	char target;
	for(int i=0;i<n;i++)
	{
		tmp=1;
		j=(i+1)%n;
		target=beads[i];
		while(j!=(i-1+n)%n && (beads[j]==target || beads[j]=='w' || target=='w'))
		{
			tmp++;
			if(target=='w') target=beads[j];
			
			j=(j+1)%n;
		}

		tmp++;
		lim=(j-1+n)%n;
		j=(i-2+n)%n;
		target=beads[(i-1+n)%n];
		while(j!=lim && (beads[j]==target || beads[j]=='w' || target=='w'))
		{
			tmp++;
			if(target=='w') target=beads[j];

			j=(j-1+n)%n;
		}

		ans=tmp>ans ? tmp:ans;
	}

	fout<<ans<<endl;

	fin.close();
	fout.close();
	return 0;
}
