#include <stdlib.h>
#include "gfx.h"
#include <math.h>
#include <time.h>

int newV(int,int);

int main(){
  
  int xwindow=500, ywindow=500;//window size

  gfx_open(xwindow, ywindow, "Bounce");
  gfx_color(255,255,255);
  
  int x=250,y=250; //shows x and y positions, updated every while loop iteration
  int radius=50;
  char c='y';
  int newx=x, newy=y;//where the bal will go toward
  
  int vmax=5;//maximum velocities in both x and y

  srand(time(NULL));//seeds random number
  int xv, yv;//xv and yv are velocities in x and y
  xv=newV(xv,vmax);
  yv=newV(yv,vmax);

  while(c!='q'){ 
    gfx_circle(x, y, radius);
    //increment ball location
    x+=xv;
    y+=yv;
    usleep(5000); //pause for 2 ms  
    //check if ball hits edge
    if((x+radius)>xwindow){
	x=xwindow-radius;
	xv=-xv;//flip velocity direction
    } else if((x-radius)<0){
	x=radius;
	xv=-xv;//flip velocity
    } else if((y+radius)>ywindow){
	y=ywindow-radius;
	yv=-yv;//flip velocity
    } else if((y-radius)<0){
	y=radius;
	yv=-yv;
    }
    //check for click 
    if(gfx_event_waiting()){
	c=gfx_wait();
	if(c==1){//this is a click
	  x=gfx_xpos();
	  y=gfx_ypos();//sets new target x and y position
	  xv=newV(xv,vmax);
	  yv=newV(yv,vmax);
        }
    }    
  gfx_clear();
  }
}

int newV(int v, int vmax){//this function can be called for both x and y assignment values, and returns a value for a new velocity for the variables
	v=(rand()%vmax+1);
	int left=rand()%2;//either 0 or 1, 1 is left(for x, up for y), 0 is right(for x, down for y)
	if(left){	
		v=-v;
	}
	return v;
}


