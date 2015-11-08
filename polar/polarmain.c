#include <stdio.h>
#include "polarfn.h"

int main(){

float x,y;
//calculates polar coordinates given x and y
//ask for x and y values
printf("This program converts cartesian coordinates into polar coordinates.\nPlease enter values for x and y.");
printf("\nX: ");
scanf("%f", &x);
printf("Y: ");
scanf("%f", &y);

float radius=findRadius(x,y);
float angle=findAngle(x,y);
int quadrant=findQuadrant(radius,angle);


printf("\nThe radius is %.2f and the angle is %.2f degrees counterclockwise from the positive x axis.\n", radius, angle);
switch(quadrant){
	case 0:
		printf("The point is on the origin.");
		break;
	case 1:
		printf("The point is in the first quadrant.");
		break;
	case 2:
                printf("The point is in	the second quadrant.");
                break;
 	case 3:
                printf("The point is in	the third quadrant.");
                break;
 	case 4:
                printf("The point is in	the fourth quadrant.");
                break;
 	case 5:
                printf("The point is on	the positive x axis.");
                break;
 	case 6:
                printf("The point is on the negative x axis.");
                break;
	case 7:
                printf("The point is on the positive y axis.");
                break;
 	case 8:
                printf("The point is on	the negative y axis.");
                break;

}
printf("\n");
}
