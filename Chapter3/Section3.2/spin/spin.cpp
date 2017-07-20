/*
ID: suzyzha1
PROG: spin
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct Wedge
{
	int st_angle,extent;
	Wedge(int s,int e)
	{
		st_angle=s;
		extent=e;
	}
};

struct Wheel
{
	int speed,w;
	Wedge *wedges[5];
} wheels[5];

int light[360];

int gcd(int a,int b)
{
	if(a%b==0) return b;
	return gcd(b,a%b);
}

bool beam()
{
	memset(light,0,sizeof(light));

	int k,p;
	for(int i=0;i<5;i++)
		for(int j=0;j<wheels[i].w;j++)
		{
			k=wheels[i].wedges[j]->st_angle;
			p=wheels[i].wedges[j]->extent+1;
			while(p)
			{
				light[k]|=(1<<i);
				k++;
				if(k>=360) k=0;
				p--;
			}
		}

	for(int j=0;j<360;j++)
	{
		if(light[j]==31)
			return true;
	}
	return false;
}

void spin()
{
	for(int i=0;i<5;i++)
		for(int j=0;j<wheels[i].w;j++)
		{
			wheels[i].wedges[j]->st_angle+=wheels[i].speed;
			wheels[i].wedges[j]->st_angle%=360;
		}
}

int main()
{
	fstream fin("spin.in",ios::in);
	fstream fout("spin.out",ios::out);

	int t1,t2;
	for(int i=0;i<5;i++)
	{
		fin>>wheels[i].speed>>wheels[i].w;
		for(int j=0;j<wheels[i].w;j++)
		{
			fin>>t1>>t2;
			wheels[i].wedges[j]=new Wedge(t1,t2);
		}
	}

	int ans=-1;
	for(int i=0;i<=360;i++)
	{
		if(beam())
		{
			ans=i;
			break;
		}
		spin();
	}

	if(ans>=0) fout<<ans<<endl;
	else fout<<"none"<<endl;

	fin.close();
	fout.close();
	return 0;
}