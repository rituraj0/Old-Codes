#include<iostream>
#include<time.h>
#include<vector>
#include<math.h>
#include<stdlib.h>
#define pros 2
#define tasks 5
#define d 3
using namespace std;

bool allocated[tasks];//Checks whether a task is allocated to any processor or not
float cost[tasks][pros];//This array is used to store Executation-cost-matrix of a task  on a  procesors 1 and 2
float dist[pros][pros];//To store distance  D(kl) as defined ..It'll be a  symmetric matrix and Dii=0
float  resor[pros];//Tell about  the  max. load on  processor i
float busy[pros];//Tell aboot how much resorces of a processor  is busy in  executing 
int  pr[tasks];//task i is assigned to pr[i] processor
float   weit[tasks][tasks];//Assocoiated Weight  with a communicaton  channel between task i and j //Again  its  asymmetric matrix

float crcost(int t);//CAlculate cost if  task t assigned to processor p
float local(float);// To give a better soln ..originaly Loalsearch function in hetro.pdf
float t_cost();
	
int main()
{
int i=0,j;
	//take in weit[][]
cout<<"Enter Weight associated with the edge between tasks i and j \n";
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
cin>>resor[i];
	//take in dist[][]
cout<<"Enter distance-related communication cost frm processor k to processor l\n";
for(i=0;i<pros;i++)
for(j=0;j<pros;j++)
cin>>dist[i][j];

	//Intial soln
	
	for(i=0;i<tasks;i++)
	allocated[i]=false;//Intially no task is assigned to any processors
	
         allocated[0]=true;

	if(cost[0][0]>cost[0][1] && busy[1]<=resor[1] )
	pr[0]=1;	//Assiging first task to processor one 
         float ranndom=1; 
	for(i=1;i<tasks;i++)
	{
                
		allocated[i]=true;
		float s0=crcost(i);
		pr[i]=1;//Now   task i is assigned to proceesor  1 and cost is calulated
		float s1=crcost(i);
         if(s1>s0)
         pr[i]=0;
         //Intial soln without consraints bcz let all tasks  distrinbute 
         
	 }
 //************End Initial sol ***********


//Now IteratedGreedy algo for  TaskAssignment   starts 


float fi0=t_cost();
float fi=local(fi0);
float fib=fi,fip,fis;;

float t=0.025*t_cost();

clock_t t1,t2;
t1=clock();
t2=clock();
float diff=( (float)t2-(float)t1 )/CLOCKS_PER_SEC;//Here i taken computation time limit ( 1 sec, in this case)as Termination condition for termination of while loop 

while(diff<1)
{
fip=fi;

for(i=0;i<d;i++)
allocated[rand()%tasks]=false;//Destruction phase .Declaring some random tasks as non-assigned
float co=t_cost();
for(i=0;i<tasks;i++)
{
if(allocated[i]==false)
{
if(pr[i]==0)
{
pr[i]=1;
if(t_cost()>co && busy[1]>=resor[1])
pr[i]=0;
}
else 
{
pr[i]=0;
if(t_cost()>co && busy[0]>=resor[0])
pr[i]=1;
}

}
}
float fic=t_cost();
fis=local(fic);

if(fis<fi)
 {fi=fis;
if(fi<fib)
fib=fi;
}else if(ranndom<exp( -(fis-fi)/t ) )
fi=fis;

t=0.9*t;


t2=clock();
diff=( (float)t2-(float)t1 )/CLOCKS_PER_SEC;

}

//**************IteratedGreedy algo. for  TaskAssignment ends
cout<<"Task    Processor\n";
for(i=0;i<tasks;i++)
cout<<i+1<<"   "<<pr[i]<<"\n";

cout<<"Total cost is  "<<t_cost()<<"\n";
return 0;
}









//***Local Search function *****
float local(float co)
{
bool impro=true;
int i,k,pi[tasks];

while(impro)
{
	impro=false;
	
for(i=0;i<tasks;i++)
pi[i]=rand()%tasks;

for(k=0;k<tasks;k++)
{
i=pi[k];
if(pr[i]==0)
{
pr[i]=1;
if(t_cost()>co && busy[1]>=resor[1])
pr[i]=0;
}
else 
{
pr[i]=0;
if(t_cost()>co && busy[0]>=resor[0])
pr[i]=1;
}
}

if(t_cost()<co)
impro=true;
}

return t_cost();
}


//*********T_COST FUNCTION TO Return total cost at the given time 
	
float t_cost()
{
float tcost=0;
int i,j;
for(i=0;i<tasks;i++)
{
if(allocated[i])
{
tcost=tcost+cost[i][pr[i]];
for(j=0;i<tasks;j++)
{
if(allocated[j])
tcost=tcost+weit[i][j]*dist[pr[i]][pr[j]];
}
}
}
}	

//******crcost(int i)  it calculate the cost in  intial solution phase where  cost due to task i is passed as parameter 
float crcost(int t)
{
	float ft=cost[t][pr[t]];
	for(int i=0;i<t;i++)
	ft=ft+weit[i][t]*dist[pr[i]][pr[t]];
	
	return ft;
}































