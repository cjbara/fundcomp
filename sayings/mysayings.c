#include <stdio.h>

int getSayings(char[][80], int*);
void displaySayings(char[][80], int);
int newSaying(char[][80],int);
int choice(void);
void containsWord(char[][80],int);
void saveToFile(char[][80],int);

int main()
{
  int check;
  int totalSayings=0;
  char sayings[100][80];
  check=getSayings(sayings,&totalSayings);//fills out sayings array
  if(check==1){return 1;}
  
  int c;//prompt user what to ask for
  while(c!=5){
    c=choice();
    switch(c){
        case 1: 
		displaySayings(sayings,totalSayings);
		break;
	case 2:
		totalSayings=newSaying(sayings,totalSayings);
		totalSayings++;
		break;
	case 3:
		containsWord(sayings,totalSayings);
		break;
	case 4:
		saveToFile(sayings,totalSayings);
		break;
	case 5:
 		break;
	default:
		printf("That is not a valid saying.");
		break;
    }
    if(c==5){return 0;}
  }
  /*printf("%i", totalSayings);
  totalSayings=60;
  displaySayings(sayings,totalSayings);
  totalSayings=newSaying(sayings,totalSayings);
    printf("%i", totalSayings);

  displaySayings(sayings,totalSayings);
*/
}

int getSayings(char sayings[][80],int* totalSayings){
  FILE *ifp;
  printf("Please enter a file name that contains sayings: ");
  char filename[20];
  scanf("%s",filename);
  ifp=fopen(filename,"r");//read the file
  if(ifp==NULL){
    printf("This is not a valid file name.\n");
    return 1;
  } else {
  int i,j=0;
  char x;
  for(i=0;i<100;i++){
    fgets(sayings[i],80,ifp);
    if(feof(ifp)){
	*totalSayings=i;//number of sayings in the array
	break;
    }
    j=0;
  }
  fclose(ifp);
  return 0;
  }
}

void displaySayings(char sayings[][80], int totalSayings){
  int i,j;
  char x;
  for(i=0;i<totalSayings;i++){
        printf("%s", sayings[i]);
  }
}
  /*	 * display all sayings currently in the database
	 * enter a new saying into the database
	 * list sayings that contain a given word (substring) entered by the user
	 * save all sayings in a new text file
	 * quit the program
	 */

int newSaying(char sayings[][80], int totalSayings){
  totalSayings++;
  printf("Please enter a new saying: ");
  getchar(); 
  gets(sayings[totalSayings]);
  printf("You entered %s\n",sayings[totalSayings]);
  return totalSayings;
}

int choice(void){
  int c;
  printf("What would you like the program to do?\n1: Display all sayings in database\n2: Enter a new saying\n3: List sayings that contain a given word\n4: Save all sayings to a new text file\n5: Quit\n");
  scanf("%i",&c);
  return c;
}

void containsWord(char sayings[][80],int totalSayings){}
void saveToFile(char sayings[][80],int totalSayings){
  int i,j;
  char x;
  char filename[20];
  printf("Please enter a file name to write to: ");
  scanf("%s",filename);
  FILE *ofp;
  ofp=fopen(filename,"w");
  for(i=0;i<totalSayings;i++){
        fprintf(ofp,"%s", sayings[i]);
  }

}

