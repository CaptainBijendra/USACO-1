/*
ID: suzyzha1
PROG: fence3
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>
#include <iomanip>

using namespace std;
const int maxn = 152;

int n;
struct Fence
{
	int x1,y1,x2,y2;
	bool vertical;
} fence[maxn];

double square(double x)
{
	return x*x;
}

double dist(double x,double y,int cur)
{
	if(fence[cur].vertical)
	{
		if(y>fence[cur].y2)
			return sqrt(square(x-fence[cur].x1) + square(y-fence[cur].y2));
		if(y<fence[cur].y1)
			return sqrt(square(x-fence[cur].x1) + square(y-fence[cur].y1));
		return fabs(x-fence[cur].x1);
	}
	else
	{
		if(x>fence[cur].x2)
			return sqrt(square(y-fence[cur].y1) + square(x-fence[cur].x2));
		if(x<fence[cur].x1)
			return sqrt(square(y-fence[cur].y1) + square(x-fence[cur].x1));
		return fabs(y-fence[cur].y1);
	}
}

int main()
{
	double x,y,bestx,besty,best_len;
	fstream fin("fence3.in",ios::in);
	fstream fout("fence3.out",ios::out);

	fin>>n;

	srand(time(0));
	bestx=rand()%100;
	besty=rand()%100;
	best_len=0;

	int a,b,c,d;
	for(int i=1;i<=n;i++)
	{
		fin>>a>>b>>c>>d;
		if(a==c) fence[i].vertical=true;
		else fence[i].vertical=false;

		fence[i].x1 = a<c ? a:c;
		fence[i].x2 = a<c ? c:a;
		fence[i].y1 = b<d ? b:d;
		fence[i].y2 = b<d ? d:b;

		best_len+=dist(bestx,besty,i);
	}

	x=bestx; y=besty;
	double tem = 100.0,kk=31,tx,ty,tmp,yes;

while(tem>1e-3)
{
	for(int i=1;i<=500;i++)
	{
		tx = tem*(1.0*rand()/RAND_MAX)*(2*(rand()%2)-1);
		ty = y + sqrt(tem*tem-tx*tx)*(2*(rand()%2)-1);
		tx += x;

		tmp=0;
		for(int k=1;k<=n;k++)
			tmp+=dist(tx,ty,k);

		if(tmp<best_len)
		{
			best_len=tmp;
			bestx=tx;
			besty=ty;
			x=tx;
			y=ty;
		}
		else
		{
			yes=exp(-(tmp-best_len)/tem);
			double q=1.0*rand()/RAND_MAX;
			if(q>=yes) continue;
			x=tx;
			y=ty;
		}
	}
	kk+=1;
	tem*=log(20)/log(kk);
}

	fout<<fixed<<setprecision(1)<<bestx<<" "<<besty<<" "<<best_len<<endl;
	fout.close();
	return 0;
}
