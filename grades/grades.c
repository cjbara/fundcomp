#include <stdio.h>
#include <math.h>

float avg(int, int[]);
float std(int, float, int[]);

int main(){
  //store inputs into array grades
  int grades[50];

  int j=0; //iterator for the following for loop
  while(1){
  //take input and determine if it is a grade or a sentinel (negative number)
    scanf("%i", &grades[j]);
    if(grades[j]<0){
	break;
    } else {//assumes all non-negative numbers are valid grades
	j++;
    }
  }
//take the array and compute average
float average;
average=avg(j, grades);
printf("The average grade is %.0f\n", average);

//compute standard deviation
float stdeviation=std(j, average, grades);
printf("The standard deviation is %.2f\n",stdeviation);
}

float avg(int iterator, int gradeArray[]){
  int i;
  float total=0;
  for(i=0; i<iterator; i++){
	total+=gradeArray[i];
  }

  float average=total/iterator;
  return average;
}

float std(int iterator, float avg, int gradeArray[]){
  int i;
  float minusAvg;
  float stdTotal=0;

  for(i=0; i<iterator; i++){
	minusAvg=gradeArray[i]-avg;
	minusAvg*=minusAvg;
	stdTotal+=minusAvg;
  }
  float newAvg=stdTotal/iterator;
  return sqrt(newAvg);
}

