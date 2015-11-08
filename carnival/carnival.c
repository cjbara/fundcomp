#include "gfx2.h"
#include <math.h>
#include <stdio.h>

int centerUpdate(int, int, int*);
void drawBase(int, int, int, int, int);
void drawSquare(int, int, double, double, int, int, double, int);
void disp(int, int);//displays 2 numbers
void drawTri(int, int, double, int);

int main(){
  int x=600,y=600;
  int xcenter=x/2,ycenter=y/2;//center of big circle 
  int xright=1;//xright is which direction the big circle is moving (1=right, 0=left)
  gfx_open(x,y,"Carnival Ride");
  gfx_clear_color(0,160,255);
  gfx_clear(); 
  char c=1;
  int bigRadius=200;//radius of big outer circle
  double bigAngle=0;//angle of rotation of square with respect to circle
  double squareAngle=0;//angle of rotation of square with respect to itself
  int squareRadius=60;
  double triAngle=0;//angle of triangles 
  int triRadius=25;//radius of triangles (center to vertex)
  while(c!='q'){
    //update center of circle then draw it
    xcenter=centerUpdate(x, xcenter, &xright);
    drawBase(x,y,bigRadius,xcenter,ycenter);

    drawSquare(xcenter, ycenter, bigAngle, squareAngle, bigRadius, squareRadius, triAngle, triRadius);

    usleep(20000);

    //update the angles for the elements
    bigAngle+=M_PI/360;
    squareAngle-=M_PI/180;
    triAngle+=M_PI/90;

    if (gfx_event_waiting()){
	c=gfx_wait();
    }
    gfx_clear();
  }
}

void disp(int a,int b){
  printf("%i %i\n",a,b);
}

int centerUpdate(int x, int xcenter, int* xright){//updates the center of the circle, and xright using a pointer
  if(*xright==1){
	xcenter++;
  } else {
 	xcenter--;
  }
  if(xcenter>(2*x/3)){
	*xright=0;
	xcenter=2*x/3;
  } else if(xcenter<(x/3)){
	*xright=1;
	xcenter=x/3;
  }
  return xcenter;
}

void drawBase(int x,int y, int r, int xcenter, int ycenter){//draws the base of the shape and circle to be moved in x direction
  int i,j=0;//j can be used to make the outer rings thicker
  //for(j=0;j<3;j++){//this loop allows the major things to be thicker
    gfx_color(100,100,100);
    gfx_line(x/4,y/2+j,3*x/4,y/2+j);//draws axis of horizontal motion for circle
    //next four draw support beams for the axis of motion
    gfx_line(0+j,y,x/4+j,y/2);//draws one support beam (far left)
    gfx_line(3*x/8-j,y,x/4-j,y/2);//left middle
    gfx_line(5*x/8+j,y,3*x/4+j,y/2);//right middle
    gfx_line(x-j,y,3*x/4-j,y/2);//far right
    
    gfx_color(0,0,0);
    gfx_circle(xcenter, ycenter, r-j);//radius r-j give it a circle of radius 
    gfx_circle(xcenter, ycenter, 3);//center bolt
  //}
  
  //this section draws grass
  int grassheight=25;//grass height off the bottom of the window 
  gfx_color(0,200,0);
  for(i=y;i>y-grassheight;i--){
    gfx_line(0,i,x,i);
  }
  
}

void drawSquare(int xcenter, int ycenter, double bigAngle, double squareAngle, int bigRadius, int squareRadius, double triAngle, int triRadius){
  gfx_color(255,0,0);//red square
  int i,j;
  int x1,x2,y1,y2;
for(j=0;j<4;j++){
  //this block draws the hinge and the line connecting the square to circle
  gfx_color(0,0,0);
  gfx_circle(xcenter+bigRadius*cos(bigAngle),ycenter+bigRadius*sin(bigAngle),3);//draws pin at center of square
  x1=xcenter;
  y1=ycenter;
  x2=xcenter+bigRadius*cos(bigAngle);
  y2=ycenter+bigRadius*sin(bigAngle);
  gfx_line(x1,y1,x2,y2);

  gfx_color(255,0,0);//red square
  for(i=0;i<4;i++){
    //the corner of one side  will be xcenter-bigRadius*cos(bigAngle)-squareRadius*cos(squareAngle)
    x1=xcenter+bigRadius*cos(bigAngle)+squareRadius*cos(squareAngle);
    y1=ycenter+bigRadius*sin(bigAngle)+squareRadius*sin(squareAngle);
	//draw the triangle here using the points of the square
	drawTri(x1,y1,triAngle,triRadius);
    //now increment squareAngle by pi/2
    gfx_color(255,0,0);
    squareAngle+=M_PI/2;
    x2=xcenter+bigRadius*cos(bigAngle)+squareRadius*cos(squareAngle);
    y2=ycenter+bigRadius*sin(bigAngle)+squareRadius*sin(squareAngle);

    gfx_line(x1,y1,x2,y2);
  }
  bigAngle+=M_PI/2;
}
}

void drawTri(int x, int y, double triAngle, int triRadius){
  int i;
  gfx_color(0,255,0);
  for(i=0;i<3;i++){
	gfx_line(x+triRadius*cos(triAngle),y+triRadius*sin(triAngle),x+triRadius*cos(triAngle+2*M_PI/3),y+triRadius*sin(triAngle+2*M_PI/3));
	triAngle+=2*M_PI/3;
  }
}
