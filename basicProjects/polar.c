#include <stdio.h>
#include <math.h>

float findRadius(float, float);
float findAngle(float, float);
int findQuadrant(float, float);

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

float findRadius(float x, float y){
	//radius is sqrt(x^2+y^2)
	return sqrt(pow(x,2)+pow(y,2));
}

float findAngle(float x, float y){
	//angle is arctan(y/x), convert to degrees
	float angle;
	if(x==0. && y==0.){
		angle=0.;
	} else {
		angle = atan(y/x);
	}

	angle = angle*180/M_PI;
	//check the x coordinate for negative values
	if(x<0){//in the second or third quadrant
		angle+=180;
	} else if(y<0){//in the fourth quadrant
		angle+=360;
	}
	return angle;
}

int findQuadrant(float radius, float angle){
/*	Quadrants are as follows:
	Q1=1
	Q2=2
	Q3=3
	Q4=4
	positive x axis=5
	negative x axis=6
	positive y axis=7
	negative y axis=8
	origin=0	*/

	int quad;//returns the quadrant according to above comment
	if(radius==0.){
		quad=0;
	} else if(angle>0. && angle<90.){ //1st quadrant
		quad=1;
	} else if(angle>90. && angle<180.){ //2nd quadrant
                quad=2;
	} else if(angle>180. && angle<270.){ //3rd quadrant
                quad=3;
        } else if(angle>270. && angle<360.){ //4th quadrant
                quad=4;
	} else if(angle==0. || angle==360.){ //positive x
                quad=5;
        } else if(angle==90.){ //positive y
                quad=7;
	} else if(angle==180.){ //negative x
		quad=6;
	} else { //negative y
		quad=8;
	}
return quad;
}
