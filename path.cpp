#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
using namespace std;
int h,w;
inline int po(int i,int j)
{
 return i*w+j;
}


int main()
{  
scanf("%d%d",&h,&w);
   
  while(h!=0 ||  w !=0)
 {


     int h,w,ap[2400]={0},bf[2400][2400]={0},i,j,k,cn,mx,p,wd[2400]={0};
     char save[2401],a[51][51],s[51];
    
     for(i=0;i<h;i++)
     {
     cin>>s;
     for(j=0;j<w;j++)
      a[i][j]=s[j]; 
      } 
 
      

      for(i=0;i<h;i++)
       {
        for(j=0;j<w;j++)
         {
           k=po(i,j);//denotes the positon of the array in the 
           save[k]=a[i][j];
 
     //now total eight  conditions
           if(i>0)//matlab pahla row nahi  to upar to ja sakte hai na Verticlyy UPAr
             if(a[i][j]+1==a[i-1][j])
              bf[k][po(i-1,j)]=1;


            if(j>0) //ie.  leftmost nahi hai to left me to ja sakte hai hi
             if(a[i][j]+1==a[j-1][j])
              bf[k][po(i,j-1)]=1;

  
            if(i<h-1) //ie, niche ja sakte hai 
              if(a[i][j]+1==a[i+1][j])
                bf[k][po(i+1,j)]=1;

            if(j<w-1)//ie, right side ja sakte hai
              if(a[i][j]+1==a[i][j+1])
               bf[k][po(i,j+1)]=1;

  
             if(i>0 && j>0)//pichle left
               if(a[i][j]+1==a[i-1][j-1])
                 bf[k][po(i-1,j-1)]=1;

            if(i>0 & j<w-1)//piche upar
               if(a[i][j]+1==a[i-1][j+1])
                 bf[k][po(i-1,j-1)]=1;

           if(i<h-1 && j>0)//niche left
              if(a[i][j]+1==a[i+1][j-1])
                 bf[k][po(i+1,j-1)]=1;

          if(i<h-1 && j<w-1)//niche right
            if(a[i][j]+1==a[i+1][j+1])
              bf[k][po(i+1,j+1)]=1;   
 
    
          }
        }//******chloo bfs ke lia mahal taiyarr hai\n"
     
        //now printing BF Matrix


        //yah atak to cool hai
        for(i=0;i<h;i++) 
          for(j=0;j<w;j++)
            if(a[i][j]=='A')
              ap[po(i,j)]=1;


            //****Now starting the BFS****

          k=po(h-1,w-1);
           cn=mx=0;

          char maxc='@';

          for(i=0;i<=k;i++)//checking if stsrting memebre is A
           {
 
              if(ap[i]==1)//matlb jab kow A mile to
               {
                queue<int> q;
                  int vs[3000]={0};
                      cn=0;
                   q.push(i);
   
                while(!q.empty())
                  {
                   p=q.front();
   
                  if(save[p]>maxc)
                    maxc=save[p];//assigning th maximum to the maxc 
     
                       q.pop();
 
                    vs[p]=1;
                     cn++;
                  for(j=0;j<=k;j++)//matlab p ke saare nodes dekh rahe hai
                    {
                    if(bf[p][j]==1)//MATLB EDGE HAI
                      if(vs[j]==0)//matlb visited  nahi hai
                       {if(j==10)
                        q.push(j);
                       }
                      }
                 }//end while

               }//end if

 
               }//end for

       cout<<maxc-64<<endl;
        scanf("%d%d",&h,&w);
     }

 return 0;
}



