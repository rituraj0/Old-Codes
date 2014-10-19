#include<iostream>
#include<cstdio>
#include<cstring>
char st[1001][1001],s[1001];
int pr[1001]={-1};
bool vs[1001]={true};
int n; 

int in()//it will check  s aginst the vailalble string and if more than one output then  return  with max pr
{
int  mp=-1,id=-1,i,j,mila,l;
    
    l=strlen(s);
    
for(i=0;i<n;i++) 
{
      mila=0;
      
     if(!vs[i])
     continue; 
                 
   for(j=0;j<l ;j++)
    if(st[i][j]== s[j])
     mila=i;  //aha tal mila hai(dekh agar bichh me kahi na mila krta to a loop khatam ho gaya hota
      else
      break;//nahi mila to is  inner loop ka kam khatan karo  
      
   if(mila==l-1)//matlab mila hai
   {
     if(mp<pr[i])
      {
      mp=pr[i];
       id=i;
       }
   }
   
}
vs[id]=false;
return id;
}   
       
                        
      

int main()
{
    int i,k,q;
    
    scanf("%d",&n);
  
    for(i=0;i<n;i++)
    scanf("%s %d",st[i],&pr[i]);
    
    scanf("%d",&q);
    
    for(i=0;i<q;i++)
    {
      scanf("%s",s);
      k=in();
      printf("%s\n",st[k]);
    }
    
    return 0;
    
}
                    
    
    
