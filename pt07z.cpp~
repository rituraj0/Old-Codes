#include<iostream>
#include<list>
#include<vector>
#include<cstdio>
#include<queue>
using namespace std;

struct head
{ bool used;
  vector<int> list;
}base[10009];

int main()
{
 int no,ed,i,x,y,u,v;
 cin>>no;
 ed=no-1;//bcz its tree so, number of edges'll be no-1


 for(i=0;i<ed;i++)
 {
  scanf("%d%d",&u,&v);
  
  base[u].list.push_back(v);
  base[v].list.push_back(u);
 }
 
  queue<int> bfs1;
  vector<int>::iterator p;

 
 
  int dist[10009]={0};//distance i contains the distance of  from sorce 1
   
  dist[1]=0;
  int in=-1,mx=-1;//in stores the maximun of the values  and  in its indsex

   bfs1.push(1);
   base[1].used=true;
 
  while(!bfs1.empty())
  { 
    
     x=bfs1.front();
      bfs1.pop();
        
   
   for(p=base[x].list.begin();p!=base[x].list.end();p++)
      { 
        y=*p;
            if(!base[y].used)
              { bfs1.push(y);
                base[y].used=true;
                dist[y]=dist[x]+1;
                 
                 if(dist[y]>mx)
                   {mx=dist[y];in=y;}
               
              }
      }//end for

  }//end while
//cout<<"--->  "<<in<<" <---\n";
//now plot for second visit

for(i=0;i<=no;i++)
 base[i].used=false;

 int dist2[10009]={0};  
   dist[in]=0;
  
 queue<int> bfs2;

  bfs2.push(in);
   base[in].used=true;

  mx=-1;

  while(!bfs2.empty() )
{
  x=bfs2.front();
    bfs2.pop();

  for(p=base[x].list.begin();p!=base[x].list.end();p++)
   {
      y=*p;
         if(!base[y].used)
            {bfs2.push(y);
              base[y].used=true;
              dist[y]=dist[x]+1;
            
                if(dist[y]>mx)
                    mx=dist[y];
             }
    }
}    
   
  
printf("%d\n",mx);
return 0;
}
