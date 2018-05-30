#include <iostream>
#include <random>
#include <vector>

using namespace std;

vector< char > initRoad(int,int);
void KMC(mt19937&,vector<char>);
void printRoad(vector<char>);
vector<int> jumpRateVec(vector<char>);
int calculateRate(vector<char>,int);
void printRates(vector<int>);
vector<int> calculateCumulativeFunction(vector<int>);
int findEvent(vector<int>,int,double);
vector<char> moveCar(vector<char>,int);
 
int main(){

  mt19937 rand(373);
  cout<<"The road: "<<endl;
  vector<char> road=initRoad(50,100);
  printRoad(road);
  KMC(rand,road);
  
  
  return 0;

}

vector< char > initRoad(int N,int L){
  
  double r = (double) N/L;
  double i = 0;
  int count = 0;
	
  vector<char> road(L);
  while(count <L){
	
    if(i ==0 || roundf(i)==i){
      road[count]='X';
    }else{
      road[count]=' ';
    }		
    i+=r;
    count++;

  }
      
  return road;
}

void printRoad(vector<char> road){
  for(int i=0;i<road.size();i++){
    cout<<road[i];
  }
  cout<<"\n";
}

void KMC(mt19937& rand,vector<char> road){

  int t=0;
  double u;
  vector<int> jumpRates(road.size());
  vector<int> cumulativeF(road.size());
  
  int RN=0;
  int event =0;
  double deltaT=0;
  int indeksi=0;
  while(indeksi <= 10000000){
    jumpRates=jumpRateVec(road);
    cumulativeF=calculateCumulativeFunction(jumpRates);
    RN=cumulativeF[cumulativeF.size()-1];
 
    u=(double)rand()/rand.max();
    event = findEvent(cumulativeF,RN,u);
   
    road=moveCar(road,event);
    u=(double)rand()/rand.max();
    deltaT=(double)-log(u)/RN;
    t+=deltaT;
    //printRates(jumpRates);
    //  cout<<endl;
    printRoad(road);
    indeksi++;
  }

  
    
  
}

vector<int> jumpRateVec(vector<char> road){
  vector<int> jumpRates(road.size());
  for(int i=0;i<road.size();i++){
    if(road[i] == ' '){
      jumpRates[i]==0;
    }else{
      int rate = calculateRate(road,i);
      jumpRates[i]=rate;
    }
  }
  return jumpRates;
}

int calculateRate(vector<char> road,int index){
  int rate = 0;
  int start =0;
  if(index != road.size()-1){
    start = index+1;
  }else{
    start =0;
  }
 	
  while(true){
    if(road[start] ==' '){
      rate++;
    }else{
      break;
    }
   
    start++;
     if(start >=road.size()){
      start=0;
    }
  }
  return rate;
}	
	
	
	
void printRates(vector<int> rates){
  for(int i=0;i<rates.size();i++){
    cout<<rates[i];
  }
  cout<<"\n";
}
	
vector<int> calculateCumulativeFunction(vector<int> rates){
  vector<int> cumulativeF(rates.size());
  int sum =0;
  for(int i=0;i<rates.size();i++){
    sum=0;
    for(int j=0;j<=i;j++){
      sum+=rates[j];		
    }
    cumulativeF[i]=sum;
  }
  return cumulativeF;
}

 int findEvent(vector<int> R,int RN,double u){
   int eventIndex =0;

   while(R[eventIndex]==0){
     eventIndex++;
   }
   for(int i=eventIndex;i<R.size();i++){
     if(R[i-1] <u*RN && u*RN<=R[i]){
       eventIndex=i;
       break;
     }
   }
   return eventIndex;
    
 }

vector<char> moveCar(vector<char> road,int index){
  if(index != road.size()-1){
    road[index]=' ';
    road[index+1]='X';
  }else{
    road[index]=' ';
    road[0]='X';
  }
  return road;
}
  
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
