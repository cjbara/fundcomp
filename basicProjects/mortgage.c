#include <stdio.h>

int main(){

float p; //principal
float yir; //yearly interest rate
float mp; //monthly payment

//Input principal, interest rate, monthly payment
printf("What is the principal? $");
scanf("%f",&p);
printf("What is the yearly interest rate? (In percentage form) %%");
scanf("%f", &yir);
printf("What is your desired monthly payment? $");
scanf("%f", &mp);

float mi; //monthly interest
float mir = yir/12/100; //monthly interest rate
int m=1; //Month number
float b=p; //balance
float newmp=0; // for later when the balance is under the monthly payment

//show the table's top axes
printf("Month\tPayment\t\tInterest\tBalance\n");


while(b>0){
	mi=b*mir; //calculates monthly interest for month
	b+=mi; //calculates balance plus monthly interest
	
	if(mp>b){
		newmp=b;
		b=0;
		printf("%i\t$%7.2f\t$%7.2f\t$%10.2f\n",m,newmp,mi,b);
	} else {
		b-=mp; //calculates balance minus payment	
		printf("%i\t$%7.2f\t$%7.2f\t$%10.2f\n",m,mp,mi,b);
		m++;
	}	

}
int years=m/12;
int remainingmonths=m%12;
printf("You paid a total of $%10.2f over %d years and %d months.\n", m*(mp-1)+newmp, years, remainingmonths);
}


