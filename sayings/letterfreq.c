#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
  FILE *ifp;//input file pointer
  printf("Please enter the name of the file: \n");
  char filename[20];
  scanf("%s",filename);
  ifp=fopen(filename,"r");
  if(ifp==NULL){
	printf("This is not a valid file name.\n");
  	return 1;
  }

  char x;
  int scrabble[26];//one array index for every letter
  int letters=0, characters=0, whitespace=0;
  int i,perline=1;

  for(i=0;i<26;i++){
	scrabble[i]=0;
  }  

  while(!feof(ifp)){
    fscanf(ifp,"%c", &x);
    //check if it is a letter by converting it tolower, subtract 'a', then check the ASCII values
    if(isalpha(x)){
	x=tolower(x);
	//x is now a lowercase, so subtract 'a' to get the index number
    	x-='a';
    //add the number to the scrabble array in the letter column
	scrabble[x]++;
    	letters++;
    } else if(isspace(x)){
	whitespace++;
    }
    characters++;
  }


  int points[26]={1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};//number of points for each letter in the game of scrabble
  printf("Appearances\tPercent\t  Scrabble Value");
  for(i=0;i<26;i++){
	x=i+'A';
	if(i%(perline)==0){printf("\n");}//print a new line for every perline values
	printf("%c: %6i\t%6.2f%%\t\t%2i",x,scrabble[i],100*scrabble[i]/(float)(characters-whitespace),points[i]);
  }
  printf("\nTotal number of letters: %i\n", letters);
  printf("Total number of characters: %i\n", characters);
  printf("Space Percentage: %.2f%%\n", 100*whitespace/(float)characters);
}
