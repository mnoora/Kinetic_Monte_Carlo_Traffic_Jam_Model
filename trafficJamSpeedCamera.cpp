#include <iostream>
#include <random>
#include <vector>

using namespace std;


// Function for initializing the road
vector< char > initRoad(int,int);
// Function for the Kinetic Monte Carlo method
void KMC(mt19937&,vector<char>);
//Function for printing the road
void printRoad(vector<char>);
// Function for creating a vector of the jump rate
vector<int> jumpRateVec(vector<char>);
// Function for calculating the jump rates
int calculateRate(vector<char>,int);
// Function for printing the jump rates
void printRates(vector<int>);
// Function for calculating the cumulative function
vector<int> calculateCumulativeFunction(vector<int>);
// Function for finding an event to carry out
int findEvent(vector<int>,int,double);
// Function for carrying out the event
vector<char> moveCar(vector<char>,int);
 
int main(){

   // Initializing Mersenne Twister Random random generator
  mt19937 rand(373);
  cout<<"The road: "<<endl;
  
  // Initializing the road
  vector<char> road=initRoad(75,150);
  
  printRoad(road);
  
  // Kinetic Monte Carlo
  KMC(rand,road);
  
  return 0;

}

vector< char > initRoad(int N,int L){
  // Initializing the road with the car density roadLength/number of cars (L/N)
  double r = (double) N/L;
  int p = floor(1/r);
  
  int i = 0;
  int count = 0;
	
  vector<char> road(L);
  while(count <L){
	
    if(i ==0 || count%p==0){
      road[count]='X';
    }else{
      road[count]=' ';
    }		
    i+=p;
    count++;

  }
      
  return road;
}

//Function for printing the road
void printRoad(vector<char> road){
  for(int i=0;i<road.size();i++){
    cout<<road[i];
  }
  cout<<"\n";
}

void KMC(mt19937& rand,vector<char> road){

  // How often the road is printed (now every 100 time units)
  double printLimit=100;
  double limit=printLimit;
  double t=0;
  double u;
  // Vectors for jump rates and cumulative function
  vector<int> jumpRates(road.size());
  vector<int> cumulativeF(road.size());
  
  int RN=0;
  int event =0;
  double deltaT=0;
  int index=0;
  while(index <= 10000000){
    // Calculating the jump rates and the cumulative function
    jumpRates=jumpRateVec(road);
    cumulativeF=calculateCumulativeFunction(jumpRates);
    RN=cumulativeF[cumulativeF.size()-1];

    // Generating a random number and finding an event to carry out
    u=(double)rand()/rand.max();
    event = findEvent(cumulativeF,RN,u);

    // Carry out the event
    road=moveCar(road,event);

    // Generating a new random number and advancing time
    u=(double)rand()/rand.max();
    deltaT=(double)-log(u)/RN;
    t+=deltaT;
  
    if(printLimit < 0){
      cout<<t<<endl;
      printRoad(road);
      printLimit=limit;
    }else{
      printLimit-=deltaT;
    }
    index++;
  }
}

// Creating a vector for jump rates
vector<int> jumpRateVec(vector<char> road){
  vector<int> jumpRates(road.size());
  // Calculating how many empty blocks of road every car has in front of them
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

// Calculating the jump rate for a car
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
    // The speed camera on the road at index 5. Cars in front of that can have jump rates smaller or equal than three
    if(index == 5 && rate > 3){
      rate=3;
      break;
    }
   
    start++;
     if(start >=road.size()){
      start=0;
    }
  }
  return rate;
}	
	
	
// Printing a vector with jump rates	
void printRates(vector<int> rates){
  for(int i=0;i<rates.size();i++){
    cout<<rates[i];
  }
  cout<<"\n";
}

// Calculating the cumulative function
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

    //finding an event to carry out, with the KMC condition
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

//Moving a car forward
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
  
	
	
	
	
	
	
	
	
	
