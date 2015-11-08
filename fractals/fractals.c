#include "gfx3.h"
#include <stdio.h>
#include <math.h>

void sierpTriangles(int,int,int,int,int,int);
void shrinkSquares(int,int,int);
void spiralSquares(int,int,double,int);
void circularLace(int,int,int);
void snowflake(int,int,int);
void tree(int,int,int,int,double,int);
void fern(int,int,int,double);
void spiralSpirals(int,int,double,int);

static int height=600,width=600;

int main()
{
  char fractal;
  int x=width/2,y=height/2,radius=width/3;
  int margin=20;	
  int x1=margin,x2=width-margin,x3=width/2,y1=margin,y2=margin,y3=height-margin;	
  gfx_open(width,height,"Fractals");
  gfx_clear_color(0,0,0);
  gfx_clear();
  gfx_color(255,255,255);
  printf("Which fractal would you like to see?\n1: Sierpinski Triangles\n2: Shrinking Squares\n3: Spiral Squares\n4: Circular Lace\n5: Snowflake\n6: Tree\n7: Fern\n8: Spiral of Spirals\n\n"); 
  while(fractal!='q'){
    fractal=gfx_wait();
    gfx_clear();
    switch(fractal){
      case 'q':
	return 0;
	break;
      case '1':
        printf("Sierpinski Triangles\n\n");
	sierpTriangles(x1,y1,x2,y2,x3,y3);
	break;
      case '2':
        printf("Shrinking Squares\n\n");
	shrinkSquares(x,y,width/4);
	break;
      case '3':
	printf("Spiral Squares\n\n");
        spiralSquares(x,y,-M_PI/4,width*2/3);
	break;
      case '4':
        printf("Circular Lace\n\n");
	circularLace(x,y,width);
	break;
      case '5':
        printf("Snowflake\n\n");
	snowflake(x,y,radius);
	break;
      case '6':
        printf("Tree\n\n");
	tree(x,height,x,height*3/4,0,height/4);
	break;
      case '7':
        printf("Fern\n\n");
	fern(width/2,height-margin,2*height/3,0);
	break;
      case '8':
        printf("Spiral of Spirals\n\n");
	spiralSpirals(x,y,0,width);
	break;
      default:
	printf("Please enter a valid option\n\n");
	break;
    }
  }  
}

void sierpTriangles(int x1,int y1,int x2,int y2,int x3,int y3){
  if(x1+3>=x2) return;                  		//check for base case
  //if the above case is not met, draw another triangle
 
  int xleft=(x1+x3)/2,xright=(x2+x3)/2,xtop=(x1+x2)/2;	//drawing step
  int ymiddle=(y1+y3)/2,ytop=y1;
  gfx_triangle(x1,y1,xtop,ytop,xleft,ymiddle);
  gfx_triangle(xtop,ytop,x2,y2,xright,ymiddle);
  gfx_triangle(xleft,ymiddle,xright,ymiddle,x3,y3);
  						//3 total recursive steps
  sierpTriangles(x1,y1,xtop,ytop,xleft,ymiddle);//top left triangle
  sierpTriangles(xtop,ytop,x2,y2,xright,ymiddle);//top right triangle
  sierpTriangles(xleft,ymiddle,xright,ymiddle,x3,y3);//bottom middle triangle
}

void shrinkSquares(int xcenter,int ycenter, int half){//half is length of half a side
  if(half<=1) return;					//check for base case

  int x1=xcenter-half,x2=xcenter+half,y1=ycenter-half,y2=ycenter+half; //draws squares
  gfx_line(xcenter-half,ycenter+half,xcenter-half,ycenter-half);//left side
  gfx_line(xcenter+half,ycenter+half,xcenter+half,ycenter-half);//right side
  gfx_line(xcenter-half,ycenter+half,xcenter+half,ycenter+half);//top side
  gfx_line(xcenter-half,ycenter-half,xcenter+half,ycenter-half);//bottom side

  int newHalf=half/2;				//recursive steps (one for each corner)
  shrinkSquares(x1,y1,newHalf);//top left
  shrinkSquares(x2,y1,newHalf);//top right
  shrinkSquares(x1,y2,newHalf);//botttom left
  shrinkSquares(x2,y2,newHalf);//bottom right
}

void spiralSquares(int x,int y,double angle,int length){
  if(length/5<=0) return;			//check for base case
  //length/5 in the above is the length of half a square's side

  int xcenter=x+length*cos(angle);		//drawing case (1 square per case)
  int ycenter=y-length*sin(angle);
  int half=length/5;
  //this draws a square (copied from shrinkSquares)
  int x1=xcenter-half,x2=xcenter+half,y1=ycenter-half,y2=ycenter+half;
  gfx_line(xcenter-half,ycenter+half,xcenter-half,ycenter-half);//left side
  gfx_line(xcenter+half,ycenter+half,xcenter+half,ycenter-half);//right side
  gfx_line(xcenter-half,ycenter+half,xcenter+half,ycenter+half);//top side
  gfx_line(xcenter-half,ycenter-half,xcenter+half,ycenter-half);//bottom side  

  double newAngle=angle-M_PI/5;
  int newLength=length*9/10;
  spiralSquares(x,y,newAngle,newLength);	//recursive step
}

void circularLace(int xcenter,int ycenter, int radius){
  if(radius<=1) return; 			//check for base case
  
  int newRadius=ceil(radius/3.);//scaling factor for the radius is 3
  gfx_circle(xcenter,ycenter,newRadius);		//drawing step
  
  //everything else is the recursive step
  int xpoints[6],ypoints[6],i;
  for(i=0;i<6;i++){
    xpoints[i]=xcenter+newRadius*cos(i*60*M_PI/180);//finds new x center points and stores it into xpoints[i]
    ypoints[i]=ycenter+newRadius*sin(i*60*M_PI/180);//finds new y center points and stores it into ypoints[i]
    circularLace(xpoints[i],ypoints[i],newRadius);//recursive step
  }
}

void snowflake(int xcenter, int ycenter, int length){
  if(length<1) return;				//check for base case
 
  float angle=2*M_PI/5;				//drawing step
  int i,xnew[5],ynew[5];
  for(i=1;i<=5;i++){
    xnew[i-1]=xcenter+length*cos(i*angle+3*M_PI/2);
    ynew[i-1]=ycenter+length*sin(i*angle+3*M_PI/2);
    gfx_line(xcenter,ycenter,xnew[i-1],ynew[i-1]);
  }
 
  int newLength=length*.38;		//recursive step
  for(i=0;i<5;i++) snowflake(xnew[i],ynew[i],newLength);
}

void tree(int x1,int y1,int x2,int y2,double angle,int length){	//angle is angle from vertical y axis
  if(length<=0) return;				//check for base case
  
  int i,xnew[2],ynew[2];			//drawing case, two lines
  double newAngle[2]={angle+M_PI/6,angle-M_PI/6};
  int newLength=length*2/3;
  gfx_line(x1,y1,x2,y2);//base line
  for(i=0;i<2;i++){
    xnew[i]=x2-sin(newAngle[i])*length;
    ynew[i]=y2-cos(newAngle[i])*length;
    gfx_line(x2,y2,xnew[i],ynew[i]);
  
    tree(x2,y2,xnew[i],ynew[i],newAngle[i],newLength);//recursive case
  }
}

void fern(int x1,int y1,int length,double angle){
  if(length<=1) return;				//base case
  
  int x2[4],y2[4],i;
  double newAngle=M_PI/6;		
  int newLength=length/3;
  for(i=1;i<=4;i++){
    x2[i-1]=x1-length*sin(angle)*i/4;		//tabulates points for next fern branch
    y2[i-1]=y1-length*cos(angle)*i/4;		
  }
  gfx_line(x1,y1,x2[3],y2[3]);			//draws next fern branch
  
  for(i=0;i<4;i++){				//recursive step (8 total steps in 4 loops)
    fern(x2[i],y2[i],newLength,angle+newAngle);
    fern(x2[i],y2[i],newLength,angle-newAngle);
  } 
}

void spiralSpirals(int x,int y, double angle,int length){
  if(length<=0) return;				//check for base case

  int xcenter=x+length*cos(angle);		//drawing case (1 point per case)
  int ycenter=y-length*sin(angle);
  gfx_point(xcenter,ycenter);
  gfx_point(xcenter+length*cos(angle),ycenter+length*sin(angle));
  spiralSpirals(xcenter,ycenter,angle,length/3);
  
  double newAngle=angle-M_PI/5;
  int newLength=length*.9;
  spiralSpirals(x,y,newAngle,newLength);
}
