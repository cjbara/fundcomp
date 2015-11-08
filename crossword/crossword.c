#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getInput(char[][16]);
void createBoard(char[][15]);
void printBoard(char[][15]);
void sortWords(int,char[][16]);
void longWord(int, char[][16], char[][15], int[][3]);
int placeWords(int, char[][16], char[][15], int[][3]);
int validVertical(int,int,int,char[][15],int[],char[]);
int validHorizontal(int,int,int,char[][15],int[],char[]);
int placeVertical(char[],char[][15],int[]);
int placeHorizontal(char[],char[][15],int[]);
void anagram(int,char[][16], int[][3]);
void showPuzzle(char[][15],char[][15]);
void randomizeWords(int,int,char[][16]);

//int bruteForceVertical(char[][15],char[],char[][3]);
//int bruteForceHorizontal(char[][15], char[],char[][3]);
//int placement(int,char[][16], char[][15], int[][3]);


int main()
{
 /* This program creates a crossword puzzle. The program will work in the following way
    	-Get inputs of words stop if there are more than 20 words or the user inputs a period
	-Create board array 15x15 char initialized to .
	-find longest word and place it in the middle of the board
	-print board array
 */ 
  int numberWords,success=0,i;//number of words entered
  char words[20][16];//max of 20 words and max of 15 letters per word
  char crossword[15][15];//enter the words into this array
  char puzzle[15][15];//to be used for the actual puzzle for solving
  int place[20][3];//collects the first index of each word, and across/down (third index)
  //the third index works as such: 0=down, 1=across (0=y,1=x coordinate)
  numberWords=getInput(words);
  createBoard(crossword);
  sortWords(numberWords,words);
  longWord(numberWords,words,crossword,place);
  for(i=0;i<10000;i++){
    success=placeWords(numberWords,words,crossword,place);
    if(success==1){
      printBoard(crossword);
      showPuzzle(crossword,puzzle);
      anagram(numberWords,words,place);
      break;
    } else {
      randomizeWords(2,numberWords,words);//if it doesn't work, then randomize the order and then try again
      //if after 10000 randomizations, it cannot find a valid board, then the program ends.
      //This does not mean there is not a board that can be generated, it just means 
      //the program took too much time
    createBoard(crossword);
    longWord(numberWords,words,crossword,place);
    }
    if(i==9999){
	printBoard(crossword);
        showPuzzle(crossword,puzzle);
        anagram(numberWords,words,place);
	printf("I'm sorry, but the board could not be created with these words.\nPlease try again.\n");
    }
  }
return 0;
}

void sortWords(int n, char words[][16]){
  //this function sorts the list, and will only be used in the first iteration
  int i,j;
  char temp[16];
  for(i=0;i<n-1;i++){
    for(j=0;j<n-i;j++){
	if(strlen(words[j])<strlen(words[j+1])){
	  strcpy(temp,words[j]);
	  strcpy(words[j],words[j+1]);
	  strcpy(words[j+1],temp);
	}
    }
  }
}

void randomizeWords(int iteration,int n,char words[][16]){
  int i,j=0,r;
  char temp[16];//temporary string to be used for swapping
  for(i=iteration;i<n;i++){
    j=iteration;
    while(j<(n-1)){
	r=(rand()%(n-j))+j;//we do not want to swap the first word, it should always be first placed
	strcpy(temp,words[r]);//give temp the value of words[r]
	strcpy(words[r],words[j]);//replace words[r1] with words[r2]
	strcpy(words[j],temp);//words[r2] is not the original words[r1]
	j++;
    }
  }
}

void createBoard(char crossword[][15]){//initializes board with . as every character
  int i,j;
  for(i=0;i<15;i++){
     for(j=0;j<15;j++){
	crossword[i][j]='.';
     }
  }
}

void printBoard(char crossword[][15]){//prints board
  int i,j;
  printf("\nSolution:\n");
  for(i=0;i<15;i++){
     for(j=0;j<15;j++){
	printf("%c",crossword[i][j]);
     }
	printf("\n");}
}

int getInput(char words[][16]){
  printf("Please enter a list of words:\n");
  //fill words array with words
  int n,i,j,isValidWord;
  char newWord[100];
  for(i=0;i<20;i++){
    isValidWord=0;//assumes i is not a valid word
    while(!isValidWord){
	scanf("%s",newWord);
    	//check if word is valid(15 or less letters)
	if(strcmp(newWord,".")==0){//end of the input
	    isValidWord=2;//end of array
    	} else if(strlen(newWord)>15){//the word is longer than 15
	    printf("No word can be longer than 15 letters. Please enter a valid word.\n");
    	} else if(strlen(newWord)<=1){//the word is shorter than 2
	    printf("Words have to be at least 2 letters. Please enter a valid word.\n");
	} else {
	    for(j=0;j<strlen(newWord);j++){
		if(!isalpha(newWord[j])){//has non-words, includes characters, not valid input
			isValidWord=0;
			printf("Words must only contain letters. Please enter a valid word.\n");
			break;
		} else { isValidWord=1;}
	    }
	}
    }
    if(isValidWord==2){break;}
    else{strcpy(words[i],newWord);}
  }
  n=i;
  for(i=0;i<n;i++){
    for(j=0;j<strlen(words[i]);j++){
	words[i][j]=toupper(words[i][j]);
    }
  }
  return n;//returns the number of words entered 
}
  
void longWord(int n,char words[][16], char crossword[][15],int place[][3]){
  //This function finds longest word in words array and places it in center of crossword board
  //start by sorting the array from longest to shortest
  int i,j;
  
  //now place largest word in center of board
  //each letter goes at words[7][x+i]
  //where x is (15-strlen(largeword))/2
  for(i=0;i<strlen(words[0]);i++){
    crossword[7][(15-strlen(words[0]))/2+i]=words[0][i];
  }
  place[0][0]=7;//row
  place[0][1]=(15-strlen(words[0]))/2;//column
  place[0][2]=1;//orientation is across
}

int placeWords(int n, char words[][16], char crossword[][15],int place[][3]){
  //the first, middle word is already placed, now we must place other words
  //start with the larger words and then place smaller words
  //words is already sorted, so just index through them
  int i,placed=1;//placed is 1 if the word has not been placed, 0 if good
  int allplaced=0,r=0;//r is number of times randomized
  int vertical=0,horizontal=1;
  for(i=1;i<n;i++){//This will loop through all words and place them
    placed=0;
    r=0;
    //this if statement makes sure there is about an even number of verticals and horizontals
    if(vertical<horizontal){//try vertical first
      while(placed!=1){
        if(r>(3*(n-i))){//if it has been randomized more than the number of words left, break the function
		return 0;
	}
        placed=placeVertical(words[i],crossword,place[i]);
        if(placed==1){
	  break;
        } else {
          placed=placeHorizontal(words[i],crossword,place[i]);
	  if(placed==1){
		break;
	  } else {
		placed=0;
		//we must randomize the remaining words until one can be placed
		randomizeWords(i,n,words);
		r++;
		continue;
		//return placed;//this element cannot be placed horizontally or vertically
	  }
        }
      }
    } else {
      while(placed!=1){//try horizontal first
        if(r>(3*(n-i))){//if it has been randomized more than the number of words left, break the function
		return 0;
	}
	placed=placeVertical(words[i],crossword,place[i]);
        if(placed==1){
          break;
        } else {
          placed=placeHorizontal(words[i],crossword,place[i]);
          if(placed==1){
                break;
          } else {
                placed=0;
		//we must randomize the remaining words until one can be placed
		randomizeWords(i,n,words);
		r++;
		continue;
                //return placed;//this element cannot be placed horizontally or vertically
          }
        }
      }
    }
    if(i==(n-1)){//all elements have been placed
	allplaced=1;
    }
  }
  return allplaced;
}

int validVertical(int i, int j, int startRow, char crossword[][15],int place[],char word[]){//checks if the space is a valid space, returns 1 if valid, else returns 0
  //startRow is the beginning row for the word, and will go down toward 
  int k,a,b,valid=1;//k loops through the word, a and b are columns next to the word
  a=j-1;
  b=j+1;
  for(k=0;k<strlen(word);k++){
    if((k+startRow)!=i){
      if(isalpha(crossword[startRow+k][a]) || isalpha(crossword[startRow+k][b]) || isalpha(crossword[startRow+k][j])){//checks the left, right, and the current space for a letter
	//either left or right is a letter, which is invalid
	valid=0;//this is not a valid position for the word
	return valid;
      } else {
        if(k==0 && startRow>0){//there must be a space above, or else it will skip this if
	  //condition for k is the first letter, check above
	  if(isalpha(crossword[startRow-1][j])){
		//the space above this placement is already taken by another word, return 0
		valid=0;//this is not a valid position for the word
        	return valid;
	  }
        } else if((k==(strlen(word)-1)) && ((startRow+k)<14)){
	  //condition for k is last letter, check below it
	  //does not check if there is no space below this space
	  if(isalpha(crossword[startRow+strlen(word)][j])){
		//the space below this placement is already taken by another word, return 0
		valid=0;//this is not a valid position for the word
        	return valid;
	  }
	}
      }
    } else if(startRow==i && startRow!=0 && k==0){//not first row
	//check the above if the intersection is the first letter
	if(isalpha(crossword[startRow-1][j])){
		//the space above this placement is already taken by another word, return 0
		valid=0;//this is not a valid position for the word
        	return valid;
	}	
    } else if((startRow+strlen(word)-1)==i && startRow<14 && k==(strlen(word)-1)){
	//check the below if the intersection is the last letter
	if(isalpha(crossword[startRow+strlen(word)][j])){
		//the space below this placement is already taken by another word, return 0
		valid=0;//this is not a valid position for the word
        	return valid;
	}
    }
  }
  //place this word here
  place[0]=startRow;//where the first row the word appears in
  place[1]=j;//column
  place[2]=0;//vertical placement
  return valid;
}
int placeVertical(char word[], char crossword[][15], int place[]){
  int i,j,k,m,startRow;
  for(i=0;i<15;i++){
    for(j=0;j<15;j++){
      for(k=0;k<strlen(word);k++){
	if(crossword[i][j]==word[k]){//the word contains this particular character
	  startRow=i-k;
	  if((startRow>=0) && ((strlen(word)+startRow)<14)){//word can fit on the board in this space
                if(validVertical(i,j,startRow,crossword,place,word)){
		  //place the word in the specified spot
                  for(m=0;m<strlen(word);m++){
                    crossword[startRow+m][j]=word[m];
		  }
		  return 1;//the word was placed successfully
                }
	  } else {break;}
        }
      }
    }
  } return 0;//the word was not placed successfully
}

int validHorizontal(int i, int j, int startCol, char crossword[][15],int place[],char word[]){//checks if the space is a valid space, returns 1 if valid, else returns 0
  //startCol is the beginning column for the word, and will go down toward 
  int k,a,b,valid=1;//k loops through the word, a and b are columns next to the word
  a=i-1;
  b=i+1;
  for(k=0;k<strlen(word);k++){
    if((k+startCol)!=j){
      if(isalpha(crossword[a][startCol+k]) || isalpha(crossword[b][startCol+k]) || isalpha(crossword[i][startCol+k])){//checks above, below, and the current space for a letter
	//either above, below, or space itself is a letter, which is invalid
	valid=0;//this is not a valid position for the word
	return valid;
      } else {
        if(k==0 && startCol>0){//there must be a space to the left, or else it will skip this if
	  //condition for k is the first letter, check left
	  if(isalpha(crossword[i][startCol-1])){
		//the space left of this placement is already taken by another word, return 0
		valid=0;//this is not a valid position for the word
        	return valid;
	  }
        } else if((k==(strlen(word)-1)) && ((startCol+k)<14)){
	  //condition for k is last letter, check right of it
	  //does not check if there is no space right of this space
	  if(isalpha(crossword[i][startCol+k+1])){
		//the space below this placement is already taken by another word, return 0
		valid=0;//this is not a valid position for the word
        	return valid;
	  }
	}
      }
    } else if(startCol==j && startCol>0 && k==0){//not first column
	//check the left if the intersection is the first letter
	if(isalpha(crossword[i][startCol-1])){
		//the space left of this placement is already taken by another word, return 0
		valid=0;//this is not a valid position for the word
        	return valid;
	}	
    } else if((startCol+strlen(word))==j && startCol<14 && k==(strlen(word)-1)){//not last column
	//check the below if the intersection is the last letter
	if(isalpha(crossword[i][startCol+k+1])){
		//the space below this placement is already taken by another word, return 0
		valid=0;//this is not a valid position for the word
        	return valid;
	}
    }
  }
  //place this word here
  place[0]=i;//row
  place[1]=startCol;//the first column the word appears in
  place[2]=1;//horizontal placement
  return valid;
}
int placeHorizontal(char word[], char crossword[][15], int place[]){
  int i,j,k,m,startCol;
  for(i=0;i<15;i++){
    for(j=0;j<15;j++){
      for(k=0;k<strlen(word);k++){
	if(crossword[i][j]==word[k]){//the word contains this particular character
	  startCol=j-k;
	  if((startCol>=0) && ((strlen(word)+startCol)<15)){//word can fit on the board in this space
                if(validHorizontal(i,j,startCol,crossword,place,word)){
		  //place the word in the specified spot
                  for(m=0;m<strlen(word);m++){
                    crossword[i][startCol+m]=word[m];
		  }
		  return 1;//the word was placed successfully
                }
	  } else {break;}
        }
      }
    }
  } return 0;//the word was not placed successfully
}

void anagram(int n,char words[][16],int place[][3]){//creates anagrams for the different words and displays them and their coordinates on the board
  int i,j=0;
  int r;
  char jumble[16],copy[16];//jumble becomes the new word to be printed and copy is replaced by a string of ....... etc. to determine which letters have been used
  printf("\nClues:\n");
  for(i=0;i<n;i++){
	//jumble the letters of words
	strcpy(jumble,words[i]);
	strcpy(copy,words[i]);
	j=0;
	while(j<strlen(jumble)){
		r=rand()%strlen(jumble);
		if(copy[r]=='.'){
			continue;//continue to next loop to choose new number
		} else {
			jumble[j]=copy[r];//replace jumble[r] with the random copied letter
			copy[r]='.';
			j++;
		}
	}
	//print out the anagrams
	if(place[i][2]==0){
	  printf("%2i,%2i Down   %s\n",place[i][0],place[i][1],jumble);
	} else {
	  printf("%2i,%2i Across %s\n",place[i][0],place[i][1],jumble);
	} 
  }printf("\n");
}

void showPuzzle(char crossword[][15], char puzzle[][15]){
  int i,j;
  printf("\nCrossword Puzzle:\n");
  for(i=0;i<15;i++){
    for(j=0;j<15;j++){
	if(isalpha(crossword[i][j])){
		puzzle[i][j]=' ';
	} else {
		puzzle[i][j]='#';
	}
    printf("%c",puzzle[i][j]);
    }
  printf("\n");
  }

}
/*UNUSED CODE 

 //this function places a single word (words[i])into the crossword array vertically
  //it attaches it to the word (words[l])
  int j,k,s;
  for(j=0;j<strlen(words[i]);j++){//this loops through the word to be placed next
    for(k=0;k<strlen(words[i-l]);k++){//loops through previous word to find a match
	if(words[i][j]==words[i-l][k]){
	//this means there is a match of letters and the word can be placed on the board
	//this word will be connected to the previous word placed
	  place[i][2]=0;
	  place[i][0]=place[i-l][0]-j;
	  place[i][1]=place[i-l][1]+k;
	  if((place[i][0]+strlen(words[i])-j)>=15) {
	      continue;//go to next loop if there's not enough room on board
	  }
	  s=0;//we have found a match for this word, so break both loops (using s as sentinel)
	  break;
	}
	s=1;
    }
    if(s==0){break;}
  }
  for(j=0;j<strlen(words[i]);j++){
        crossword[place[i][0]+j][place[i][1]]=words[i][j];
  }
  return s;

  //this function places a single word (words[i]) into the crossword array horizontally 
  //it attaches it to the word (words[l])
  int j,k,s;
  for(j=0;j<strlen(words[i]);j++){//this loops through the word to be placed next
    for(k=0;k<strlen(words[i-l]);k++){//loops through previous word to find a match
	if(words[i][j]==words[i-l][k]){
	//this means there is a match of letters and the word can be placed on the board
	//this word will be connected to the previous word placed
	  place[i][2]=0;
	  place[i][0]=place[i-l][0]+k;
	  place[i][1]=place[i-l][1]-j;
	  if((place[i][1]+strlen(words[i])-j)>=15) {
	      continue;//go to next loop if there's not enough room on board
	  }
	  s=0;//we have found a match for this word, so break both loops (using s as sentinel)
	  break;
	}
	s=1;
    }
    if(s==0){break;}
  }
  for(j=0;j<strlen(words[i]);j++){
        crossword[place[i][0]][place[i][1]+j]=words[i][j];
  }
  return s;


*/

/*
int bruteForceVertical(char crossword[][15],char word[]){
  int i,j,k,canPlace=0;
  for(j=0;j<15;j++){
    for(i=0;i<(15-strlen(word));i++){
      for(k=0;k<strlen(word);k++){
	if(crossword[i+k][j]=='.' || crossword[i+k][j]==word[k]){
	  if(k==(strlen(word)-1)){//if it has made it through every letter in the word and it all works, then the word can be placed there
		canPlace=1;
                place[w][0]=i;
                place[w][1]=j;
                place[w][2]=0;
		return canPlace;
	  } else {continue;}
	  validSpace(i,j,crossword);
	  canPlace=0;
	} else {break;}
      }
    }
  }
}
int bruteForceHorizontal(char crossword[][15], char word[]){
  int i,j,k,canPlace=0;
  for(i=0;i<15;i++){
    for(j=0;j<(15-strlen(word));j++){
      for(k=0;k<strlen(word);k++){
	if(crossword[i][j+k]=='.' || crossword[i][j+k]==word[k]){
	  if(k==(strlen(word)-1)){//if it has made it through every letter in the word and it all works, then the word can be placed there
		canPlace=1;
		place[w][0]=i;
		place[w][1]=j;
		place[w][2]=1;
		return canPlace;
	  } else {continue;}
	  validSpace(i,j,crossword);
	  canPlace=0;
	} else {break;}
      }
    }
  }
}
*/		 

/*
int placement(int w,char words[][16], char crossword[][15], int place[][3]){
  int i,j,k,m,s=0;
  for(i=0;i<15;i++){
    for(j=0;j<15;j++){
      for(k=0;k<strlen(words[w]);k++){
        s=0;
	if(crossword[i][j]==words[w][k]){//the word contains this particular character
	  if(((i-k)>=0) && ((strlen(words[w])+i-k)<15)){
		printf("\nYES %i %i %i %i\n",i,j,k,w);
		//place vertically, vertical placement is default
		place[k][0]=i-k;
          	place[k][1]=j;
		place[k][2]=0;//vertical placement
		for(m=0;m<strlen(words[w]);m++){//this loop checks if the word can be placed 
		//into the specified spot (checks for overlapping letters anywhere)
	          if((crossword[place[k][0]+m][place[k][1]]!=words[w][k]) && (crossword[place[k][0]+m][place[k][1]]!='.')){
			s=1;
			break;//immediately stop checking if an invalid is found
		  }
		}
	        if(s==1){
                        continue;
                } else {
                  for(m=0;m<strlen(words[w]);m++){
                    crossword[place[k][0]+m][place[k][1]]=words[w][m];
		  }
		  return 0;
                }
	  } else if(((j-k)>=0) && ((strlen(words[w])+j-k)<15)){
		printf("\nYES\n");
		//place horizontally
		place[k][0]=i;
                place[k][1]=j-k;
		place[k][2]=1;//horizontal placement
		for(m=0;m<strlen(words[w]);m++){
		//this loop checks if the word can be placed 
		//into the specified spot (checks for overlapping letters anywhere)
                  if((crossword[place[k][0]][place[k][1]+m]!=words[w][k]) && (crossword[place[k][0]][place[k][1]+m]!='.')){
                        s=1;
                        break;//immediately stop checking if an invalid is found
                  }
                }
		if(s==1){
			continue;//this means the word will not work here, find another place
		} else {
                  for(m=0;m<strlen(words[w]);m++){
                    crossword[place[k][0]][place[k][1]+m]=words[w][m];
		  }
		  return 0;
                }	
	  } else {break;}
	}
      } 
    }
  } return s;
}
*/
/*
int placeHorizontal(int w, char words[][16], char crossword[][15], int place[][3]){
int i,j,k,m,s=0;
  for(i=0;i<15;i++){
    for(j=0;j<15;j++){
      for(k=0;k<strlen(words[w]);k++){
        s=0;
        if(crossword[i][j]==words[w][k]){//the word contains this particular character
	  if(((j-k)>=0) && ((strlen(words[w])+j-k)<15)){
		printf("\nYES H %i %i %i %i\n",i,j,k,w);
		//place horizontally
		place[w][0]=i;
		printf("\nYES\n");
                place[w][1]=j-k;
		printf("\nYES\n");
		place[w][2]=1;//horizontal placement
		printf("\nYES\n");
		for(m=0;m<strlen(words[w]);m++){
		//this loop checks if the word can be placed 
		//into the specified spot (checks for overlapping letters anywhere)
                  if((crossword[place[w][0]][place[w][1]+m]!=words[w][k]) && (crossword[place[w][0]][place[w][1]+m]!='.')){
                        s=1;
                        break;//immediately stop checking if an invalid is found
                  }
                }
		if(s==1){
			continue;//this means the word will not work here, find another place
		} else {
                  for(m=0;m<strlen(words[w]);m++){
                    crossword[place[k][0]][place[k][1]+m]=words[w][m];
		  }
		  return 0;
                }	
	  } else {break;}
	}
      } 
    }
  } return s;
}
*/

