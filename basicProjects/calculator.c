#include <stdio.h>


float add(float, float);
float subtract(float, float);
float multiply(float, float);
float divide(float, float);

int main(){

//This program is an interactive calculator for 3rd graders
//It adds, subtracts, multiplies, or divides numbers given input by user

char i;//user input

do{
printf("What would you like the calculator to do?\n1: add (a+b)\n2: subtract (a-b)\n3: multiply (a*b)\n4: divide (a/b)\n0: quit\nEnter your operation: ");
scanf("%i", &i);
if(i==0){
	break;
}
//gather inputs to perform operation on
float x,y;
printf("Please enter two numbers to perform this operation:\na= ");
scanf("%f", &x);
printf("b= ");
scanf("%f", &y);

float z;
if(i==1){
	z=add(x,y);
} else if(i==2){
	z=subtract(x,y);
} else if(i==3){
	z=multiply(x,y);
} else if(i==4){
	z=divide(x,y);
} else {
	printf("Please enter a valid command.\n");
	continue;
}
printf("\n");
} while (i!='q');

}

float add(float x, float y){
float z=x+y;
printf("The sum of %.3f and %.3f is %.3f",x,y,z);

return z;
}

float subtract(float x, float y){
float z=x-y;
printf("The difference of %.3f and %.3f is %.3f",x,y,z);

return z;
}

float multiply(float x, float y){
float z=x*y;
printf("The product of %.3f and %.3f is %.3f",x,y,z);

return z;
}

float divide(float x, float y){
float z=x/y;
printf("The quotient of %.3f and %.3f is %.3f",x,y,z);

return z;
}
