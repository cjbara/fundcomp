#include "gfx3.h"
#include <math.h>

void snowflake(int,int,int,double);
void tree(int,int,int,int,double,double,int);
void fern(int,int,int,double);

static int height=600,width=600;

int main()
{
  gfx_open(width,height,"Winter Wonderland");
  gfx_clear_color(255,255,255);
  gfx_clear();
  char q=' ';
  int snowflakes=100;
  double angle[snowflakes];
  int i,x[snowflakes],y[snowflakes],size[snowflakes],red,j,color,loops=0,wind;
  int colors[snowflakes][3];
  while(q!='q'){
    for(i=0;i<snowflakes;i++){			//100 snowflakes initiation loop
      	x[i]=rand()%width;
 	y[i]=rand()%height;
      	size[i]=rand()%10+10;//sizes between 10 and 20
      	angle[i]=rand()%6;//random angle
	for(j=0;j<3;j++)	colors[i][j]=rand()%255;
    }
    while(!gfx_event_waiting()){
      loops++;
      if(loops%20==0)	wind=(rand()%4%3-1)*10;	//wind moves positive or negative 5 or 0
      for(i=0;i<height*.4;i++){			//sky loop
      	red=(i*240/(height*.4)-255);
	//red=((i/5)%255);
      	gfx_color(red,red,255);
      	gfx_line(0,i,width,i);
      }/*
      for(i=1;i<70;i++){				//sun loop
	gfx_color(255,255,0);
	//else gfx_color(255,255,i-50);
	gfx_circle(width/2,height*.2,i);
	gfx_circle(width/2,height*.2+1,i);
      }
      for(i=height*.4;i<=height*.4+70;i++){		//ground loop
	color=255;
	gfx_color(color,color,color);
	gfx_line(0,i,width,i);
      }*/
      for(i=0;i<snowflakes;i++){
  	gfx_color(colors[i][0],colors[i][1],colors[i][2]);
	snowflake(x[i],y[i],size[i],angle[i]);
	x[i]+=(rand()%3-1)*5+wind;//each snowflake either moves 5 left or right, or wind is on
	if(x[i]>=width)	x[i]-=width;
	else if(x[i]<0) x[i]+=width;
	y[i]+=5;//each flake falls 5 spaces per iteration
	if(y[i]>=height)	y[i]-=height;
      }
      usleep(100000);
      gfx_clear();
    }
    if(gfx_event_waiting())	q=gfx_wait();
 }
}
void snowflake(int xcenter, int ycenter, int length, double initialAngle){
  if(length<1) return;                          //check for base case

  float angle=2*M_PI/5;                         //drawing step
  int i,xnew[5],ynew[5];
  for(i=1;i<=5;i++){
    xnew[i-1]=xcenter+length*cos(i*angle+initialAngle*M_PI/2);
    ynew[i-1]=ycenter+length*sin(i*angle+initialAngle*M_PI/2);
    gfx_line(xcenter,ycenter,xnew[i-1],ynew[i-1]);
  }

  int newLength=length*.38;             //recursive step
  for(i=0;i<5;i++) snowflake(xnew[i],ynew[i],newLength,initialAngle);
}
