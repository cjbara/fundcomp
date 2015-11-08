#include <stdio.h>
#include <math.h>

int main(){

int r=0;
float min=10.;
float minx=0.;
float max=10.;
float maxx=0.;
float y=20.;
float x=0.;
int i=0;

printf("A plot of y = 10*(2+sin(2x)-cos(x)) from x=0 to 20.0\n");
printf("    X         Y\n");
for(x=0.; x<=20.1; x+=0.2){
	y=10*(2+sin(2*x)-cos(x));
	if(y<min){
		min=y;
		minx=x;
	}

	if(y>max){
		max=y;
		maxx=x;
	}

	r=rint(y);
	printf("%5.2f%10.2f\t",x,y);
	for(i=0; i<=r; i++){
		printf("#");
	}
	printf("\n");
}
printf("The maximum value of %5.2f was at x=%5.2f\n",max,maxx);
printf("The minimum value of %5.2f was at x=%5.2f\n",min,minx);


}
