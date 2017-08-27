/*
ID: suzyzha1
PROG: prime3
LANG: C++
*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
FILE *fpin,*fpout;

const int stop=(1<<10)-1;

int first,sum;
int xx,yy;
int numh[6],numl[6];
int d[6][6];

int flag[100000];
int test[100000];
int change[1050];

int ansnum;
int ans[1000][6][6];

void record()
{
	int i,j,sx[6],sy[6],sxx=0,syy=0;
	sx[1]=sx[2]=sx[3]=sx[4]=sx[5]=0;
	sy[1]=sy[2]=sy[3]=sy[4]=sy[5]=0;
	
	for(i=1;i<=4;i++)
	for(j=1;j<=4;j++)
	{
		sx[i]+=d[i][j];
		sy[j]+=d[i][j];
	}
	
	for(i=1;i<=4;i++)
	{
		d[i][5]=sum-sx[i];
		d[5][i]=sum-sy[i];
		sx[5]+=d[5][i];
		sy[5]+=d[i][5];
		sxx+=d[i][i];
		syy+=d[6-i][i];
	}
	syy+=d[1][5];
	if(syy==sum && sx[5]==sy[5] && sy[5]==sxx)
	{
		ansnum++;
		d[5][5]=sum-sx[5];
		for(i=1;i<=5;i++)
		for(j=1;j<=5;j++)
		    ans[ansnum][i][j]=d[j][i];
	}
}

int xiao(int a,int b)
{
	int i,j;
	for(i=1;i<=5;i++)
	for(j=1;j<=5;j++)
		if(ans[a][i][j]<ans[b][i][j]) return 1;
		else
		if(ans[a][i][j]>ans[b][i][j]) return 0;
}

void print()
{
	int i,j,k,p,tmp;
	
	if(ansnum==0)
	{
	    fprintf(fpout,"NONE\n");
	    return;
	}
	
	for(i=1;i<ansnum;i++)
	for(j=1;j<=ansnum-i;j++)
	if(xiao(j+1,j)==1)
	{
		for(k=1;k<=5;k++)
		for(p=1;p<=5;p++)
		{
			tmp=ans[j][k][p];
			ans[j][k][p]=ans[j+1][k][p];
			ans[j+1][k][p]=tmp;
		}
	}
	
	////////////////
	for(i=1;i<=ansnum;i++)
	{
		for(j=1;j<=5;j++)
		{
			for(k=1;k<=5;k++)
				fprintf(fpout,"%d",ans[i][j][k]);
			fprintf(fpout,"\n");
		}
		if(i<ansnum) fprintf(fpout,"\n");
	}
}

void dfs(int x,int y)
{
	int i,hash,hash2,hash3,be,s;
	
	if(x==5) {record(); return;}
	
	hash=hash2=hash3=stop;
	
	if(y==1)
	{
		d[x-1][5]=change[test[numh[x-1]]];
		numl[5]=numl[5]*10+d[x-1][5];
	}
	else
	{
		hash&=test[numh[x]];
		if(x==4)
		{
			numh[5]=numh[5]*10+change[test[numl[y-1]]];
			hash3&=test[numh[5]];
		}
	}

	if(x>1)
	{
		hash&=test[numl[y]];
		hash2&=test[numl[y+1]];
	}
	
	if(x==y)
	{
		hash&=test[xx];
		xx*=10;
	}
	
	if(x==2 && y==1)
	    yy=change[test[numh[1]]];
	    
	if(x+y==6)
	{
		hash&=test[yy];
		yy*=10;
	}
	
	numh[x]*=10;
	numl[y]*=10;
	be=0;
	
	while(hash>0)
	{
		s=hash&(-hash);
		i=change[s];
		if((hash3 & test[numl[y]+i-be]) && (hash2 & test[numh[x]+i-be]))
		{
			numh[x]+=i-be;
			numl[y]+=i-be;
			be=i;

			d[x][y]=i;
			
			if(x==y) xx+=i;
			if(x+y==6) yy+=i;
			
			if(y<4) dfs(x,y+1); 
			else dfs(x+1,1); 
			
			if(x==y) xx-=i;
			if(x+y==6) yy-=i; 
		}
		
		hash-=s;
	}
	
	numh[x]/=10;
	numl[y]/=10;
	if(x==y) xx/=10;
	if(y==1) numl[5]/=10;
	if(x==4) numh[5]/=10;
	if(x+y==6) yy/=10;
}

int main()
{
	int i,j,k;
	int s,e,tot;

	fpin=fopen("prime3.in","r");
	fpout=fopen("prime3.out","w");

	fscanf(fpin,"%d%d",&sum,&first);
	
	d[1][1]=xx=numh[1]=numl[1]=first;
	//////////////////////////////
	for(i=2;i<100000;i++)
	if(flag[i]==0)
	{
		for(j=i+i;j<100000;j+=i)
			flag[j]=1;
			
		if(i>10000)
		{
			tot=0;
			for(j=i;j>0;j/=10)
			{
				tot+=j%10;
			}
			if(tot==sum) test[i]=1;
		}
	}
	
	s=1000; e=10000;
	for(i=3;i>=0;i--)
	{
		for(j=s;j<e;j++)
		for(k=0;k<=9;k++)
		if(test[j*10+k])
			test[j]|=(1<<k);
			
		e/=10;
		s/=10;
	}
	
	for(i=0;i<10;i++)
	    change[1<<i]=i;
	///////////////////////
	
	dfs(1,2);
	
	print();

	fclose(fpin);
	fclose(fpout);
	return 0;
}
