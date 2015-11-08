#include <math.h>
#include "gfx.h"


void drawBucket(int, int);
void drawFerrisWheel(int,int,int[],int[],float);

int main(){
  int height=500, width=500;//screen dimensions
  gfx_open(height,width, "Ferris Wheel");
  gfx_clear_color(150,200,255);
  gfx_clear();

  char c='g';//checks for input, faster/slower/quit
  int xbucket[8];//has positions of 8 buckets
  int ybucket[8];
  float angle=0;
  int speed=30000;
  int ccw=-1;//determines if ferris wheel goes counter clockwise or clockwise (-1=cw, 1=ccw)
  while(c!='q'){
    drawFerrisWheel(width,height,xbucket,ybucket,angle);	    
    //drawBucket(250,250);
    if(ccw<0){
    	angle+=2*M_PI/360;//1 degree per animation  
    } else {
        angle-=2*M_PI/360;//1 degree per animation  
    }
    usleep(speed);//sleep a certain time, speed
    if(gfx_event_waiting()){
	c=gfx_wait();
	switch(c){
	  case 'f'://towards clockwise
		if(ccw>0){
                        speed+=3000;
                } else {
                        speed-=3000;
                }
                if(speed>48000){
                        speed=48000;
                        ccw=-ccw;
		} else if(speed<0){
			speed=0;
		}		
		break;
	  case 's'://towards counterclockwise
		if(ccw<0){
			speed+=3000;
		} else {
			speed-=3000;
		}
		if(speed>48000){
			speed=48000;
			ccw=-ccw;
		} else if(speed<0){
			speed=0;
		}
		break;
	  default:
		break;
	}
    }
  gfx_clear();
  }
}

void drawBucket(int x, int y){//x and y are the locations of the center of the bucket
        gfx_color(100,100,100);
	int toplength=20; //this is the length of top of the bucket 
        int bottomlength=15; //length of the bottom of the bucket
	int height=15; //all three of the variables are half of the actual lengths
	gfx_line(x+toplength, y-height, x-toplength, y-height); //top
        gfx_line(x+bottomlength, y+height, x-bottomlength, y+height); //bottom
        gfx_line(x-toplength, y-height, x-bottomlength, y+height); //left
        gfx_line(x+bottomlength, y+height, x+toplength, y-height); //right
	gfx_circle(x,y,2);
}

void drawFerrisWheel(int width, int height, int xbucket[], int ybucket[], float angle){//dimensions of the screen and bucket location array
    int i;
    int radius=200;
    int grassheight=25;//grass height off the bottom of the window
    //this section draws grass
    gfx_color(0,200,0);
    for(i=height;i>height-grassheight;i--){
        gfx_line(0,i,width,i);
    }
    //this section will place the buckets
    //fill out bucket array
    //bucket 1 starts at cos(0),sin(0)
    gfx_color(130,130,130); 
    int j; //loops through and fills bucket array
    for(j=0;j<8;j++){
	angle=angle+M_PI/4;
	xbucket[j]=width/2+(radius-2)*cos(angle);
	ybucket[j]=height/2+(radius-2)*sin(angle);
	gfx_line(width/2,height/2,xbucket[j],ybucket[j]);
    	drawBucket(xbucket[j],ybucket[j]);
    }
    //this section draws the wheel and the braces for the wheel
    gfx_color(0,0,0);
    gfx_line(width/4,height-grassheight,width/2,height/2);
    gfx_line(3*width/4,height-grassheight,width/2,height/2);
    gfx_circle(width/2,height/2,radius);
    gfx_circle(width/2,height/2,radius-5);
}



