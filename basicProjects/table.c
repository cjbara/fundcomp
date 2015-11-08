//This program creates a multiplication table given dimensions by the user
#include <stdio.h>

int main(){

//Gather dimensions for the table
int rows=0,columns=0;

puts("How many rows should the table have? ");
scanf("%d", &rows);

puts("\nHow many columns should the table have? ");
scanf("%d", &columns);

int x,y;

for(x=0; x<=rows; x++){
	for(y=0; y<=columns; y++){
		if(x==0 && y==0){	//first frame is a star
			printf("     *");
		} else if(x==0){	//this is to initialize the top row
			printf("%6i",y);
		} else if(y==0){//to initialize the side row
			printf("%6i",x);
		} else {	//to get the actual multiplication table
			printf("%6i",x*y);
		}
	} 
	printf("\n");
}
}
