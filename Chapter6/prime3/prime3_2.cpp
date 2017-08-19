#include <stdio.h>
#define maxx(a,b) ((a)>(b)?(a):(b))
#define minn(a,b) ((a)<(b)?(a):(b))
 
struct reco
{
    int rec[5][5];
}ans[1000]={0};
int total ,frist ,stop = (1<<10) -1 ,change[1025]={0};
int numh[5]={0} ,numl[5]={0} ,xx ,re=0 ,prime[5][5]={0};
short h[100000]={0} ,test[100000]={0};
 
void init()
{
    int i,j,x,l,k,sum,t,flag;
    scanf("%d%d",&total,&frist);
 
    for ( i=2 ; i<100000 ; i++ )
      if ( !h[i] )
      {
         for ( j=i+i ; j<100000 ; j+=i )
            h[j] = 1;
         if ( i > 10000 )
         {
            sum = 0;
            flag = 1;
            for( l=4,x=i ; x>0 ; x/=10,l-- )
            {
              sum += x%10;
              if ( x%10 == 0 )
                flag = 0;
            }
            if ( sum == total )
              test[i] = 1;
         }
      }
   int s = 1000,e = 10000;
   for ( i=3 ; i>=0 ; i--,s/=10,e/=10 ) 
     for ( j=s ; j<e ; j++ )
       for ( k=0 ; k<10 ; k++ )
         if ( test[j*10+k] )
           test[j] |= 1<<k;
 
   xx = prime[0][0] = numh[0] = numl[0] = frist;
 
   for ( i=0 ; i<10 ; i++ )
     change[1<<i] = i;
}
void record()
{
    int i,j,x[5]={0},y[5]={0},xx=0,yy=0;
    for ( i = 0 ; i < 4 ; i++ )
       for ( j = 0 ; j < 4 ; j++ )
       {
          x[i] += prime[i][j];
          y[j] += prime[i][j];
       }
    for ( i = 0 ; i < 4 ; i++ )
    {
       prime[i][4] = total - x[i];
       prime[4][i] = total - y[i];
       x[4] += prime[4][i];
       y[4] += prime[i][4];
       xx += prime[i][i];
       yy += prime[i][4-i];
    }
    yy += prime[4][0];
    if ( yy == total && x[4] == y[4] && x[4] == xx && x[4] < total )
    {
       prime[4][4] = total - x[4];
       for ( i=0 ; i<5 ; i++ )
         for ( j=0 ; j<5 ; j++ )
           ans[re].rec[i][j] = prime[j][i];
       re++;
    }
 
}
int yy=0;
void fun(int x,int y)
{
    if ( x==4 )
      record();
    else
    {
        int i,be,s,hash = stop,hash2 = stop,hash3 = stop;
        if ( y > 0 )
        {
           hash &= test[numh[x]];
           if ( x==3 )
           {
             numh[4] = numh[4]*10 + change[test[numl[y-1]]];
             hash3 &= test[numh[4]];
           }
        }
        else
        {
           prime[x-1][4] = change[test[numh[x-1]]];
           numl[4] = numl[4]*10 + prime[x-1][4];
        }
 
        if ( x > 0 ) 
        {
           hash &= test[numl[y]];
           if ( y==3 )
             hash2 &= test[numl[4]];
        }
 
        if ( x == y )
        {
           hash &= test[xx];
           xx *= 10;
        }
 
        if ( x==1 && y==0 )
           yy = change[test[numh[0]]];
 
        if ( x+y==4 )
        {
           hash &= test[yy];
           yy *= 10;
        }
 
        numh[x] *= 10;
        numl[y] *= 10;
        be = 0;
 
        while ( hash > 0 )
        {
          s = hash & (-hash);
          i = change[s];
          //printf("x:%d y:%d hash:%d lowbit:%d cur:%d\n",x,y,hash,s,i );
          if ( ( test[numh[x]+i-be] & hash2 ) && ( hash3 & test[numl[y]+i-be] ) )
          {
            numh[x] += i-be;
            numl[y] += i-be;
            be = i;
            prime[x][y] = i;
            if ( x==y )
              xx += i;
            if ( x+y==4 )
              yy += i;
 
            if ( y < 3 )
              fun (x,y+1);
            else 
              fun (x+1,0);
 
            if ( x==y )
              xx -= i;
            if ( x+y==4 )
              yy -= i;
          }
          hash -= s;
        }
 
        numh[x] /= 10;
        numl[y] /= 10;
        if ( x==y )
          xx /= 10;
        if ( y==0 )
          numl[4] /= 10;
        if ( x==3 )
          numh[4] /= 10;
        if ( x+y==4 )
          yy /= 10;
    }
}
void print()
{
    int i,j,x,y,min;
    struct reco temp;
    for ( i = 0 ; i < re ; i++ )
    {
       for ( min = i,j = i+1 ; j < re ; j++ )
       {
         for ( x = 0 ; x < 5 ; x++ )
           for ( y = 0 ; y < 5 ; y++ )
             if ( ans[min].rec[x][y] > ans[j].rec[x][y] )
             {
                min = j;
                goto end;
             }
             else if ( ans[min].rec[x][y] < ans[j].rec[x][y] )
                goto end;
         end:;
       }
       if ( min != i )
       {
          temp = ans[min];
          ans[min] = ans[i];
          ans[i] = temp;
       }
    }
    for ( i = 0 ; i < re ; i++ )
    {
      for ( x = 0 ; x < 5 ; x++ )
      {
        for ( y = 0 ; y < 5 ; y++ )
          printf("%d",ans[i].rec[x][y]);
        printf("\n");
      }
      if( i != re-1 )
        printf("\n");
    }
}
int main()
{
    freopen("prime3.in","r",stdin);
    freopen("prime3_2.out","w",stdout);
    init();
    fun(0,1);
    print();
    return 0;
 
}