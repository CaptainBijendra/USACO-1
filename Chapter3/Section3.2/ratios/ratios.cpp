/*
ID: suzyzha1
PROG: ratios
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class Mixture
{
public:
	int x,y,z;
	Mixture& operator = (const Mixture &b)
	{
		x=b.x;
		y=b.y;
		z=b.z;
		return *this;
	}

	Mixture& operator + (const Mixture &b)
	{
		x+=b.x;
		y+=b.y;
		z+=b.z;
		return *this;
	}

	Mixture& operator * (const int b)
	{
		x*=b;
		y*=b;
		z*=b;
		return *this;
	}
};

Mixture goal,p[3];

int main()
{
	fstream fin("ratios.in",ios::in);
	fstream fout("ratios.out",ios::out);

	fin>>goal.x>>goal.y>>goal.z;
	for(int i=0;i<3;i++) fin>>p[i].x>>p[i].y>>p[i].z;

	Mixture cur,t0,t1,t2;
	bool flag=false;
	int tmp1,tmp2,tmp3,sum,i,j,k,multiple;
	for(sum=0;sum<298;sum++)
	{
		cur.x=cur.y=cur.z=0;
		for(i=0;i<=sum && i<100;i++)
		{
			for(j=0;j<=sum-i && j<100;j++)
			{
				k=sum-i-j;
				if(k>99) continue;

				t0=p[0]; t1=p[1]; t2=p[2]; 
				cur=t0*i+t1*j+t2*k;
				if(cur.x<goal.x || cur.y<goal.y || cur.z<goal.z) continue;
				
				if(goal.x==0 && cur.x!=0) continue;
				if(goal.y==0 && cur.y!=0) continue;
				if(goal.z==0 && cur.z!=0) continue;

				if(goal.x>0 && cur.x%goal.x!=0) continue;
				if(goal.y>0 && cur.y%goal.y!=0) continue;
				if(goal.z>0 && cur.z%goal.z!=0) continue;

				if(goal.x==0) tmp1=-1;
				else tmp1=cur.x/goal.x;

				if(goal.y==0) tmp2=-1;
				else tmp2=cur.y/goal.y;

				if(tmp1!=tmp2 && tmp1!=-1 && tmp2!=-1) continue;

				if(tmp1==-1) tmp1=tmp2;

				if(goal.z==0) tmp3=-1;
				else tmp3=cur.z/goal.z;

				if(tmp1!=tmp3 && tmp1!=-1 && tmp3!=-1) continue;

				if(tmp1==-1) tmp1=tmp3;
				flag=true;
				multiple=tmp1;
				break;
			}
			if(flag) break;
		}
		if(flag) break;
	}

	if(flag)
		fout<<i<<" "<<j<<" "<<k<<" "<<multiple<<endl;
	else
		fout<<"NONE"<<endl;

	fin.close();
	fout.close();
	return 0;
}