#include<iostream>
#include<cstdio>
//typedef long long int lg;
using namespace std;
int al[2005],tm[2005],an,tn;//an n tn are the count o

int  lc()
{
 int ar[200][200],i,j;
 
 for(i=0;i<=an;i++)
  ar[i][0]=0;
 
 for(i=0;i<=tn;i++)
   ar[0][i]=0;

 for(i=2;i<=an;i++)
     for(j=2;j<=tn;j++)
  {
    if(al[i]==tm[j])
       ar[i][j]=ar[i-1][j-1]+1;
    
    else if( ar[i-1][j] >= ar[i][j-1])
        ar[i][j]=ar[i-1][j];
     
    else
         ar[i][j]=ar[i][j-1];
   }

return ar[an][tn];
}


int main()
{

int i,t,mx=0,temp;
 
scanf("%d", &t);

  while(t--)
	{
		temp=1;
		an=0;
		while(temp!=0)
		{
			scanf("%d", &temp);
			al[++an]=temp;
			
		}

		mx=0;
 
		while(1)
		{
			scanf("%d", &temp);
			if(temp==0)
				break;
			else
			{
				tn=0;
				tm[0]=temp;
				while(temp!=0)
				{
					scanf("%d", &temp);
					tm[++tn]=temp;
				}

                             i=lc();
                            if(i>mx)
                             mx=i;
                         }

                 }


   printf("-->> op is  %d  <--\n",mx);
}
return 0;

}

