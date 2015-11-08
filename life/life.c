#include <stdio.h>

const int SIZE=40;
const int SLEEPTIME=100000;

void initializeBoard(char[][SIZE]);
void displayBoard(char[][SIZE]);
int input(char[][SIZE],char[][SIZE]);
int fileInput(char[][SIZE],char[][SIZE],char[]);
int fileORuser(int);
int addCell(char[][SIZE],int,int);
int removeCell(char[][SIZE],int,int);
int nextLife(char[][SIZE],char[][SIZE]);
int neighbors(char[][SIZE],int,int);

int main(int argc,char *argv[])
{
  char present[SIZE][SIZE];
  char future[SIZE][SIZE];
  initializeBoard(present);
  int user=fileORuser(argc);
  if(user==0) return 1;//ends program with error message in function fileORuser
  else if(user==1){//user inputs accepted
    input(present,future);
  } else {//take input from a file
    fileInput(present,future,argv[1]);
  }
}

void initializeBoard(char present[][SIZE]){
  int i,j;
  for(i=0;i<SIZE;i++)
    for(j=0;j<SIZE;j++)
      present[i][j]=' ';
}

void displayBoard(char present[][SIZE]){//displays board along with borders
  int i,j,k;
  system("clear");
  /*for(k=0;k<SIZE;k++){
	printf("_");
  }*/
  for(i=0;i<SIZE;i++){
    printf("|");
    for(j=0;j<SIZE;j++){
      printf("%c",present[i][j]);
    }printf("|\n");
  }
  /*for(k=0;k<SIZE;k++){
	printf("_");
  }*/
}
  
int fileORuser(int argc){//determines whether to use a file or user input
  if(argc==1)		return 1;//this activates user mode
  else if(argc==2)	return 2;//this activates file input mode
  else{
	printf("Too many inputs\n");
	return 0;//this ends program
  }
}

int fileInput(char present[][SIZE],char future[][SIZE],char argv[]){//returns 1 if error reading file
  FILE *ifp;
  ifp=fopen(argv, "r");
  if(ifp==NULL){
    printf("This is not a valid input file.\n");
    return 1;
  }	
  char action;//receives the action of the user (a,r,n,q, or p)
  int xposition,yposition;
  while(1){
    fscanf(ifp,"%c",&action);
    switch (action){
	case 'a'://add new cell
		fscanf(ifp,"%i %i",&xposition,&yposition);
		addCell(present,xposition,yposition);
		break;
	case 'r':
		fscanf(ifp,"%i %i",&xposition,&yposition);
		removeCell(present,xposition,yposition);
		break;
	case 'n':
		//do one iteration of life
		nextLife(present,future);
		break;
	case 'q':
		return 0;
		break;
	case 'p':
		//play forever
		while(1){ 
                    nextLife(present,future);
                    usleep(SLEEPTIME);
                }
		break;
    }
  }
}

int input(char present[][SIZE],char future[][SIZE]){
  char action;//receives the action of the user (a,r,n,q, or p)
  int xposition,yposition;
  char nothing;
  while(1){
    printf("Please enter an action:\na: add new cell\nr: remove existing cell\nn: advance to next iteration\nq: quit simulation\np: play forever\n");
    scanf("%c",&action);
    switch (action){
	case 'a'://add new cell
		printf("Enter x and y coordinates for the new cell separated by a space: ");
		scanf("%i%i",&xposition,&yposition);
		addCell(present,xposition,yposition);
		break;
	case 'r'://removes cell 
		printf("Enter x and y coordinates of cell to be deleted separated by a space: ");
		scanf("%i%i",&xposition,&yposition);
		removeCell(present,xposition,yposition);
		break;
	case 'n':
		//do one iteration of life
		nextLife(present,future);
		break;
	case 'q':
		return 0;
		break;
	case 'p':
		//play forever
		while(1){
		    nextLife(present,future);
		    usleep(SLEEPTIME);
		}
		break;
	/*default:
		printf("Please enter a valid command\n");
		break;*/
    }
    scanf("%c",&nothing);
  }
}
int addCell(char present[][SIZE],int x,int y){//adds a new live cell to board, only if coordinates are on board, if they aren't return 1
  if(x>=0 && x<SIZE && y>=0 && y<SIZE){ 
        present[x][y]='X';
	displayBoard(present);
        return 0;
  } else {return 1;}
}

int removeCell(char present[][SIZE],int x,int y){//adds a new live cell to board, only if coordinates are on board, if they aren't return 1
  if(x>=0 && x<SIZE && y>=0 && y<SIZE){
	present[x][y]=' ';
	displayBoard(present);
  	return 0;
  } else {return 1;}
} 

int nextLife(char present[][SIZE],char future[][SIZE]){
  int i,j,n;//n is number of neighbors around certian point
  system("clear");

  for(i=0;i<SIZE;i++){
    for(j=0;j<SIZE;j++){
      n=neighbors(present,i,j);
      if(n==3 && present[i][j]==' '){//dead cell to be revived
	future[i][j]='X';
      } else if((n==2 || n==3) && present[i][j]=='X'){//live cell to be kept
	future[i][j]='X';
      } else {
	future[i][j]=' ';
      }
    }
  }

  //now that we calculated a whole future board, make present=future
  for(i=0;i<SIZE;i++){
    for(j=0;j<SIZE;j++){
	present[i][j]=future[i][j]; 
    }
  } 
  displayBoard(present);
}

int neighbors(char present[][SIZE],int i, int j){//returns number of neighbors for a certain cell
  int k,n=0;//n is number of neighbors
  int top=1,bottom=1,left=1,right=1;//assume it isn't on an edge
  //if the space is on an edge, then mark that side as a 0
  if(i==0) 	top=0;
  if(i==SIZE-1) bottom=0;
  if(j==0)  	left=0;
  if(j==SIZE-1) right=0;
  
  for(k=j-left;k<=(j+right);k++){
    if(top==1){//only check the row above if there is a row above
	if(present[i-1][k]=='X') n++;
    }
    if(present[i][k]=='X'){
	if(k!=j) n++;//make sure it isn't the middle one
    }
    if(bottom==1){
	if(present[i+bottom][k]=='X') n++;
    }
  }
  return n;
}
