#include "gfx.h"
#include <math.h>

void drawSquare(int, int);
void drawPolygon(int, int, int);

int main(){

  gfx_open(600,600, "Symbolic Typewriter");

  char c;

  while(c != 'q'){
    c=gfx_wait();
    if(c==1){
	gfx_color(0,0,255);
	drawSquare(gfx_xpos(),gfx_ypos());
    } else if(c=='t'){
	gfx_color(0,255,0);
	drawPolygon(gfx_xpos(), gfx_ypos(), 3);
    } else if(c=='c'){
	gfx_color(255,255,255);
	gfx_circle(gfx_xpos(), gfx_ypos(), 50);//radius 50
    } else if(c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='8'||c=='9'){
	int num = c -'0';
	gfx_color(140,0,170);
	drawPolygon(gfx_xpos(), gfx_ypos(), num);
    } else if(c=='q'){
	break;
    }
  }
}

void drawSquare(int x, int y){//x and y are the locations of the center of the square
	int hsl=50; //this is the length of half of a side of the square
	gfx_line(x+hsl, y-hsl, x-hsl, y-hsl); //top
	gfx_line(x+hsl, y+hsl, x-hsl, y+hsl); //bottom
	gfx_line(x-hsl, y-hsl, x-hsl, y+hsl); //left
	gfx_line(x+hsl, y-hsl, x+hsl, y+hsl); //right
}

void drawPolygon(int x, int y, int sides){
  int r=50; //radius of polygon
  int i;
  float angle=2.*M_PI/sides;
  for(i=0; i<sides; i++){
	gfx_line(x+r*cos(angle*i), y+r*sin(angle*i), x+r*cos(angle*(i+1)), y+r*sin(angle*(i+1)));
  }
}
