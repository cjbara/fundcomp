#include <stdio.h>

int main(){

int touchdowns,fieldGoals,pats,safeties;

printf("Let's see how many points the Irish will get this week!\n");

printf("How many Touchdowns will the Irish score?\n");
scanf("%i", &touchdowns);

printf("How many Point After Touchdowns?\n");
scanf("%i",&pats);

printf("How many Field Goals?\n");
scanf("%i",&fieldGoals);

printf("How many Safeties?\n");
scanf("%i",&safeties);

/*assign total points scored, 6 for TD, 1 for pat, 3 for FG, 2 for safety*/
int pointsScored=6*touchdowns+pats+3*fieldGoals+2*safeties;

printf("The Irish will score %i points!\n",pointsScored);

}
