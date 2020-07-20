#include <bits/stdc++.h>
#include <math.h>
#define N 50   //population size
#define M 100  //max marks
#define Y 10 //number of genes undergoing mutation
#define K 20 //this is the value of k for tournament selection
    
using namespace std;

void fitness(int stud[],int n, int currChro[4])
{
    int j,a,b,c,fitness = 0;
      for(j=0;j<n;j++)
      {
          a =  abs(stud[j]-currChro[0]);
          b =  abs(stud[j]-currChro[1]);
          c =  abs(stud[j]-currChro[2]);

          a>b?(b>c?fitness+=c:fitness+=b):(a>c?fitness+=c:fitness+=a);
      }
      currChro[3]=fitness;
}

void chromosomes(int stud[],int n,int chrom[][4],int m)
{  

    srand(time(0));
    int i,j,k;
    for(i=0;i<m;i++)
    {
        for(j=0;j<3;j++)
        {
            k = rand()%n;
            chrom[i][j] = stud[k];
        }
    }

     for(i=0;i<m;i++)
     {
         fitness(stud,n,chrom[i]);
     }

}

void selCrosMut(int stud[],int n,int chrom[][4])
{
    srand(time(0));
    int i,j,parent1,parent2,temp,chromTemp[N][4];
    
    for(i=0;i<N/2;i++)
    {   
// tournament selection
        int max=0;
        for(j=0;j<K;j++)
           { temp = rand()%N;
             if(chrom[temp][3]>max)
             {   max = chrom[temp][3];
                 parent1=temp;}
           }
        max =0;
        for(j=0;j<K;j++)
           { temp = rand()%N;
             if(chrom[temp][3]>max)
             {   max = chrom[temp][3];
                 parent2=temp;}
           }

           
//crossover
         int crossPoint = rand()%3;

         for(j=0;j<=crossPoint;j++)
         {
             chromTemp[i][j] = chrom[K][j];
             chromTemp[N-i-1][j] = chrom[j][j];
         }
         for(j=crossPoint+1;j<=2;j++)
         {
             chromTemp[i][j] = chrom[j][j];
             chromTemp[N-i-1][j] = chrom[K][j];
         }
         
    }
 
//mutation
    


    for(i=0;i<Y;i++)
    {
        int a,b,c;
        a = rand()%N;
        b = rand()%3;
        c = rand()%n;
        chromTemp[a][b] = stud[c];
    }
    for(i=0;i<N;i++)
     {
         fitness(stud,n,chromTemp[i]);
     }

     for(i=0;i<N;i++)
     {
          for(j=0;j<4;j++)
          {
              chrom[i][j]=chromTemp[i][j];
          }
     }


}

int main()
{
	int i,j,n,chromPopulation[50][4]; 
	 /*50 chromosome of length 3 contained in chromPopulation[][]. 4th index stores the corresponding fitness, which is the value of minimum diversity(absolute marks difference)*/
    
    cout<<"Enter no. of students: "<<endl;
    cin>>n;
    int gMinFitness=10000000; //global min fitness
	int count=1000; //minimum number of crossovers
	int minFitness=10000000; //current value of min fitness
	int stud[n];
    // array of marks of n students
    
	srand(time(NULL));
    for(i=0;i<n;i++)
     {
         stud[i] = rand()%M;                
     }

    chromosomes(stud,n,chromPopulation,50);
    int best[4];

    while((count--) || ((minFitness-gMinFitness)>0) )
    {
    int minimum[4];

    for(i=0;i<50;i++)
    {
        if(chromPopulation[i][3] < minFitness)
        {
            minFitness = chromPopulation[i][3];
            minimum[0] = chromPopulation[i][0];
            minimum[1] = chromPopulation[i][1];
            minimum[2] = chromPopulation[i][2];
            minimum[3] = chromPopulation[i][3];
        }
    }

    if(minFitness<gMinFitness)
    {
        gMinFitness = minFitness;
        best[0] = minimum[0];
        best[1]=minimum[1];
        best[2]=minimum[2];
        best[3]=minimum[3];
    }

     selCrosMut(stud,n,chromPopulation);
    }

    vector <int> g1,g2,g3;
     int a,b,c;
      for(j=0;j<n;j++)
      {
          a =  abs(stud[j]-best[0]);
          b =  abs(stud[j]-best[1]);
          c =  abs(stud[j]-best[2]);
			 a>b?(b>c?(g3.push_back(stud[j])):(g2.push_back(stud[j]))):(a>c?(g3.push_back(stud[j])):(g1.push_back(stud[j])));
      }
    
	cout<<"GROUP 1 Representative: "<<best[0]<<endl;
    for(j=0;j<g1.size();j++)
    {
        cout<<g1[j]<<" ";
    }
    cout<<"\nGROUP 2 Representative: "<<best[1]<<endl;
    for(j=0;j<g2.size();j++)
    {
        cout<<g2[j]<<" ";
    }
    cout<<"\nGROUP 3 Representative: "<<best[2]<<endl;
    for(j=0;j<g3.size();j++)
    {
       cout<<g3[j]<<" ";
    }
return 0;
}
