#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;

struct head
{int next;
bool used;
vector<int> list;
}base[10009];


int main()
{

 int no,ed;
 int mila[10000]={0},i,y,x,u,v;

 cin>>no>>ed;//no number of nodes ed number of edges

  for(i=0;i<=no;i++)
     base[i].used=false;

  for(i=0;i<ed;i++)
 { 
   cin>>u>>v;
 
  base[u].list.push_back(v);
  base[v].list.push_back(u);//bcz its undireted

 }

 //now stsrting the bfs

 

 queue<int> bf;
 
 vector<int>::iterator p;
  
  bf.push(1);
  
 while( !bf.empty() )
   {
      x=bf.front();
        bf.pop();
     
 
        //cout<<x<<"  ";
 
         mila[x]=1;
        base[x].used=true;

       for(p=base[x].list.begin();p!=base[x].list.end();p++)
         {   
              y=*p;
   
             if(!base[y].used)
               {  
                 bf.push(y);
                 base[y].used=true;
                }

          }

   }//end while
  bool conn=true;

  for(i=1;i<=no;i++)
     if(mila[i]==0)
       conn=false;
         
  if(conn && (ed==no-1) )
     printf("YES\n"); 
  else 
   printf("NO\n");
   
 return 0;

}      
                  
    
  

