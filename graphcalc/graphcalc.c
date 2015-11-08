#include "gfx2.h"
#include <math.h>
#include <stdio.h>

double compute(int, double);
int xdecimalToPixel(double, int);
int ydecimalToPixel(double, int);
void axes(int, int);
void graphPoints(int, int, int, int);
char *num2str(int);

int main(){
  
  int xwindow=500;//x screen size
  int ywindow=500;//y screen size

  gfx_open(xwindow,ywindow, "Graphing Calculator");
  gfx_clear_color(255,255,255);
  gfx_clear();
  axes(xwindow,ywindow);

  int terms=1;//number of terms
  
  char c='t';  
  //new function must take all values of x and compute the y value 
  //all values of x include all pixels of screen, starting in middle as (0,0)
  //there are 250 points on each side of (0,0), so each pixel is 10/xwindow=1/25
  double x1=-10., y1;
  double x2=x1+10./xwindow, y2;
  int x1p, y1p, x2p, y2p;//these are assigned pixel values to be plotted
  int i,j;
  while(c!='q'){
    x1=-10.;
    x2=x1+10./xwindow;
    for(j=1; j<=xwindow*10; j++){
      for(i=1;i<=1;i++){
	//function computes y values of the function
   	y1=compute(terms, x1);
    	y2=compute(terms, x2);
    	
	//convert all values of x and y to pixel values
    	x1p=xdecimalToPixel(x1,xwindow);
    	y1p=ydecimalToPixel(y1,ywindow);
    	x2p=xdecimalToPixel(x2,xwindow);
    	y2p=ydecimalToPixel(y2,ywindow);
    	//graph the points
    	graphPoints(x1p,y1p,x2p,y2p);
	    
    	//update values of x1 and x2, and begin new loop
    	x1=x2;
    	x2+=10./xwindow;
      }
    }
    printf("Number of Terms: %i\n", terms);
    c=gfx_wait();
    switch(c){
	case 'i':
		terms++;
		break;
	case 'd':
		terms--;
		break;
    }
    if(terms>15){
	terms=15;}
    else if(terms<0){ 
	terms=0;}
  gfx_clear();
  axes(xwindow,ywindow);
  }
}

double compute(int terms, double x){//this program calculates values for taylor series 
				//expansion of sin(X) for a certain value of x for a certain number of terms
  int i,j,power;//i, j iterators, power is the exponent of the term, f is the factorial term
  double f=1,m,ex=0;//m is the numerator
  for(i=1; i<=terms; i++){
    power=2*i-1;//1st=1 2nd=3 3rd=5 etc.
    m=pow(x,power);
    f=1;
    for(j=1; j<=power; j++){//calculates factorial
	f*=j;
    } 

    if(i%2!=0){//in this case the term must be negative
	m*=-1;
    }
    ex+=m/f;
  }
return ex;
}

int xdecimalToPixel(double a, int window){
  //Multiply a by window/2/10 and add window/2 to get pixel number
  return (window/20.*a+window/2);
}

int ydecimalToPixel(double a, int window){
  //Multiply a by window/2/10 and add window/2 to get pixel number
  return window/20.*a+window/2;
  }

void graphPoints(int x1, int y1, int x2, int y2){
  gfx_color(255,0,0);
  gfx_line(x1,y1,x2,y2);
}

void axes(int x, int y){
  gfx_color(0,0,0);
  gfx_line(x/2,0,x/2,y);//vertical line
  gfx_line(0,y/2,x,y/2);//horizontal line
  int i;
  for(i=1; i<=20; i++){
    gfx_line(i*x/20,y/2-5,i*x/20,y/2+5);
    gfx_text(i*x/20,y/2-7,num2str(i-10));
    gfx_line(x/2-5,i*y/20,x/2+5,i*y/20);
    gfx_text(x/2+7,i*y/20,num2str(10-i));
  }
}

char *num2str(int n){
  static char a[4]; 
  sprintf(a, "%d", n);
  return (char *) a;
}




