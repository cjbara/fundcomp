#include <stdio.h>

int getgcd(int,int);

int main(){

int a,b,gcd;

printf("This program will calculate the greatest common divisor of two numbers.\n");

//Ask for two numbers and store them into variables a and b
printf("Please enter two integer numbers:\nFirst Number: ");
scanf("%i", &a);
printf("Second Number: ");
scanf("%i", &b);

//calculates using getgcd function
gcd = getgcd(a,b);

printf("The greatest common divisor of %i and %i is %i.\n\n", a, b, gcd);

}

int getgcd(int a, int b){
int x;
if(b>a){
	x=b; //x is a placeholder to make sure a is bigger than b
	b=a;
	a=x;
}

int c=a%b;

//this is using euclidian algorithm
while(c!=0){
	x = b % c; //x is again used as a placeholder for the value needed to be stored in c
	b=c;
	c=x;
}

//after loop breaks, b is the gcd

return b;

}
