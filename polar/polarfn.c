#include <stdio.h>
#include <math.h>

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
        origin=0        */

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

