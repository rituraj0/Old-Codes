#include<iostream>
#include<cstdio>
#include<queue>
#include<cstdlib>
using namespace std;
typedef long long int lg;
lg n,m;

struct node 
{
  int x,y,vl;
}st[34000];

lg po(lg a, lg b)
{
return a*m+b;
}  

int main()
{

lg a[185][185],path[34000][10],an[185][185];//an me answerr store karenge
lg i,j,cn,k,x,y,z,mila,test;

char s[200];
scanf("%lld",&test);

while(test--)

{



scanf("%lld%lld",&n,&m);


for(i=0;i<n;i++)
{
  scanf("%s",s);
 for(j=0;j<m;j++)
  a[i][j]=s[j]-48;

}

//cout<<"Input Done\n";

for(i=0;i<n;i++)
 {
   for(j=0;j<m;j++)
    {

      k=po(i,j);

     st[k].vl=a[i][j];
     st[k].x=i;
     st[k].y=j; 
    
    path[k][0]=-1;
    path[k][1]=-1;
    path[k][2]=-1;
    path[k][3]=-1;

      if(i>0)//matlab  <<-- wala 
      {
          x=po(i-1,j);
          path[k][0]=x;
     }

     if(j>0)
    {
      x=po(i,j-1);
      path[k][1]=x;
    }


   if(i<n-1)//matlab sabse niche wale 
   {
     x=po(i+1,j); 
    path[k][2]=x;
   }

   if(j<m-1)
   {
    x=po(i,j+1);
   path[k][3]=x;
   }

 }
}//chalo path[]][] complete
              

//Now sratring the bfs
 for(i=0;i<n;i++)
  { 
     for(j=0;j<m;j++)
     {
        k=po(i,j);

        if(st[k].vl==1)
        {  an[i][j]=0;
            continue;
         }

          //ab sabke lia bfs kar rahe hai
          lg vs[34000]={0};

          queue<lg> q;

          q.push(k);
           vs[k]=1;
 
           cn=0;
           mila=0;

         while(!q.empty() && mila==0)
         {
           x=q.front();
            q.pop(); 
          
          
           if(st[x].vl==1)
           {an[i][j]=abs(st[k].x-st[x].x)+abs(st[k].y-st[x].y);
            mila=1;
            }
           
          for(y=0;y<4 && mila==0;y++)
          {
          z=path[x][y];//yahi tha o   
           if(z!=-1 && vs[z]==0) 
              { q.push(z);
                  vs[z]=1;
              }
          }//end for
        }//end while
       

   }
 }
          
 for(i=0;i<n;i++)
  {
         for(j=0;j<m;j++)
        printf("%lld ",an[i][j]);
     printf("\n");
  }



}
return 0;
}       
          

