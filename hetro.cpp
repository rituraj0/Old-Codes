#include<iostream>
#include<time.h>
#include<vector>
#include<algorithm>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
//For  different u hav to change here
#define tasks 5
#define pros 2
using namespace std;

bool  allocated[tasks],iallocated[tasks];//Checks whether a task is allocated to any processor or not
float cost[tasks][pros];//This array is used to store Executation-cost-matrix of a task  on a  procesors 1 and 2
float dist[pros][pros];//To store distance  D(kl) as defined ..It'll be a  symmetric matrix and Dii=0
float resor[pros];//Tell about  the  max. load on  processor i
int   pr[tasks],pt[tasks];//task i is assigned to pr[i] processor 
float weit[tasks][tasks];//Assocoiated Weight  with a communicaton  channel between task i and j //Again  its  asymmetric matrix
float local(float);// To give a better soln ..originaly Loalsearch function in hetro.pdf
float busy(int p,int t);//retuns the load of processor p if processor  p is loaded with task t
float t_cost(); //returns total cost at  calling time
float ibusy(int,int);
float pcost();
float icost(int);
float load(int);
int mn=0,lc=0;

	
int main()
{
int i=0,j;
for(i=0;i<tasks;i++)
{pr[i]=-5;
pt[i]=-1;
}
	//take in weit[][]
cout<<"Amount of data transfer with the edge between tasks i and j \n";
for(i=0;i<tasks;i++)
for(j=0;j<tasks;j++)
cin>>weit[i][j];
	//take in cost[][]
cout<<"Entre the Executation-cost-matrix of a task  on a  procesors\n";
for(i=0;i<tasks;i++)
for(j=0;j<pros;j++)
cin>>cost[i][j]; 

	// take in resor[]
cout<<"Enter max. load on  processor i\n";
for(i=0;i<pros;i++)
cin>>resor[i];

	//take in dist[][]
cout<<"Enter communication cost frm processor k to processor l\n";
for(i=0;i<pros;i++)
for(j=0;j<pros;j++)
cin>>dist[i][j];

	//Intial soln stsrts here


	for(i=0;i<tasks;i++)
	{allocated[i]=false;//Intially no task is assigned to any processors
	 iallocated[i]=false;
        }
        
            
float ranndom=1,s0=0,s1=0,mini; 
int mi;
	for(i=0;i<tasks;i++)
	{
               iallocated[i]=true;
              mini=999999;
              mi=-1;
              for(j=0;j<pros;j++)
            {
              if(ibusy(j,i)<=resor[j])
               {s0=icost(i);
                if(s0<mini)
                {mini=s0;
                 mi=j;
                }
               }//end outer if
             }//end inner for
          pt[i]=mi;
           }
   
//chalo ab  initial soln ko bast me copy kar do
for(i=0;i<tasks;i++)
pr[i]=pt[i];
 //************End Initial sol ***********

//Now IteratedGreedy algo for  TaskAssignment   starts 


float fi0=t_cost();

float fi=local(fi0);

float fip,fis,fib=fi;//Best soluton fib so far,;
float t=0.025*t_cost();

clock_t t1,t2,t3;
t1=clock();
t2=clock();
t3=clock();//for recording best


int pi[tasks],k;
for(i=0;i<tasks;i++)
pi[i]=i;//Assigining tasks to the for generating prrmutaioms and removing it from the dag

float diff=( (float)t2-(float)t1 )/CLOCKS_PER_SEC,fic;


while(diff<0.5)
{
mn++;

fip=fi; 
k=rand()%(tasks);
next_permutation(pi,pi+k);

for(i=0;i<k;i++)
iallocated[pi[i]]=false;//Removing some random permutaton  ____ yaha pi[i] task hai


int w;
for(j=0;j<k;j++)
{

i=pi[j];//yaha i to task hua na 
  
for(w=0;w<pros;w++)
{
iallocated[i]=true;
if(ibusy(w,i)<=resor[w])
{pt[i]=w;         
w=pros;
}
}//end iner for

}//


fic=pcost();
fis=local(fic);

// Bhai ab 3 jagah processor ka aloaction stote karma padega 1,local 2.fi 3. best ___best wala to pr[] hi rahega 
//cool hai yaaar ..us pdf me intial soln ko bhi LOOP me mila dia hai , so no need of third fcost()  function

if(fis<t_cost())
{
 for(i=0;i<tasks;i++)//yaha to best assign ho raha hai
 pr[i]=pt[i];
 t3=clock();
//cout<<"Aaaya\n";
}
else if(ranndom < exp( -(fis-t_cost())/t ) )
{
for(i=0;i<tasks;i++)
pr[i]=pt[i];
cout<<"Chitoyapa hua\n";
}
          
t=0.9*t;
      
t2=clock();
diff=((float)t2-(float)t1)/CLOCKS_PER_SEC;

}


//**************IteratedGreedy algo. for  TaskAssignment ends

cout<<"\nTask    Processor\n";

for(i=0;i<tasks;i++)
cout<<i+1<<"        "<<pr[i]+1<<"\n";




cout<<"\nProcessor   Resorce  Current_Load\n";
for(i=0;i<pros;i++)
cout<<i+1<<"   \t     "<<resor[i]<<"   \t   "<<load(i)<<"\n";

cout<<"\nTotal cost is  "<<t_cost()<<"\n\n\n\n";

//Printing best time
diff=((float)t3)/CLOCKS_PER_SEC;
diff=diff* 1000+.5*i/100;
printf("Best Solution Occores at: %.4f  Miliseconds\n",diff);

cout<<"\n\n\n\n\n"
system("pause");
return 0;
}








//***Local Search function *****
float local(float co)
{
lc++;
bool impro=true;
int i,k,pi[tasks],d,mi,j;//bhai , pi[]  yaha  random selected  tasks hai 
float mini;
while(impro)
{
	impro=false;
	
for(i=0;i<tasks;i++)
pi[i]=pr[i];

next_permutation(pi,pi+tasks);
//Cheking for best assignment 

float s0=0,s1=0; 

	for(i=0;i<tasks;i++)
	{
           d=pi[i];

     iallocated[d]=true;
              mini=999999;
              mi=-1;
              for(j=0;j<pros;j++)
            {
              if(ibusy(j,d)<=resor[j])
               {s0=icost(d);
                if(s0<mini)
                {mini=s0;
                 mi=j;
                }
               }//end if
             }//end inner for
          pt[d]=mi;
           } 
           


if(pcost()<co)
{impro=true;
for(i=0;i<tasks;i++)
pr[i]=pt[i];
co=pcost();
}

}

return co;
}







//*iNTIAL sOM=LN COST FUNCTION  icost() yaha pt[i] pr nikalenge  
float icost(int t)
{
      float zero=0;
      float ft=0;
      int i;
      ft=cost[t][pt[t]];
      
      for(i=0;i<t;i++)//Here , pahle se pata hai ki t ke pahle wale allocted hai so, allocated[i] ki jarurat nahi
        ft+=weit[i][t]*dist[pt[i]][pt[t]];
      
       
       return ft;
       }                   
      


//*********busy(int ,int) function declaration ***

float busy(int p,int t)
{
int i;
float b=0;
for(i=0;i<tasks;i++)
{
if(allocated[i]==true && pr[i]==p )
b=b+cost[i][p];

}

b=b+cost[t][p];
return b;
}

//For calculating ibusy()
float ibusy(int p,int t)
{
int i;
float b=0;
for(i=0;i<tasks;i++)
{
if(iallocated[i]==true && pt[i]==p )
b=b+cost[i][p];

}

b=b+cost[t][p];
return b;
}

//for temporary Total_cost() for localsearcg
float pcost()
{
      int i,j;
float tocost=0;
for(i=0;i<tasks;i++)
tocost+=cost[i][pt[i]];

for(i=0;i<tasks-1;i++)
 for(j=i+1;j<tasks;j++)
 tocost+=weit[i][j]*dist[pt[i]][pt[j]];

return tocost;
}
//*********T_COST FUNCTION TO Return total cost at the given time 
	
float t_cost()
{
      int i,j;
float tocost=0;
for(i=0;i<tasks;i++)
tocost+=cost[i][pr[i]];

for(i=0;i<tasks-1;i++)
 for(j=i+1;j<tasks;j++)
 tocost+=weit[i][j]*dist[pr[i]][pr[j]];

return tocost;
}

float load(int i)
{
float l;
int t;
for(t=0;t<tasks;t++)
{if(pr[t]==i)
l+=cost[t][i];
}

return l;
}
//For fcost() according to fi in main grredy algorithm


