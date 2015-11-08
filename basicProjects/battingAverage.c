#include <stdio.h>
int main(){

float plateApps;
int hits,walks,HBPs,errors,FCs;

printf("\n This program will compute your batting average (Avg.)\n and on base percentage (OBP)!\n");
printf("How many times have you been at the plate? ");
scanf("%f\n",&plateApps);
printf("How many hits do you have? ");
scanf("%d\n",&hits);
printf("How many walks have you had? ");
scanf("%d\n",&walks);
printf("How many hit by pitches have you had? ");
scanf("%d\n",&HBPs);
printf("How many errors have you had? ");
scanf("%d\n",&errors);
printf("How many fielder's choices have you had? ");
scanf("%d\n",&FCs);

float avg,obp;

obp=(hits+errors+walks+HBPs+FCs)/plateApps;
avg=hits/(plateApps-walks-HBPs);

printf("Your Avg. is: %f and your OBP is %f!",avg,obp);

}
