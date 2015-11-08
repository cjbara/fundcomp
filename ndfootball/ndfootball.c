#include <stdio.h>
#include "records.h"

int main(){
  int i;
  /* ask user what he wants to know
  choices include:
	winning seasons (above .500)
	losing seasons (below .500)
	seasons with 10 or more wins
	undefeated seasons
	seasons with equal wins and losses
	bowl eligible seasons
  */
  int response;//for gathering user's response
  int y=1;
  int currentyear=113;//+1900=2013

  while(y==1){
  printf("What would you like to know?\n1: Winning seasons (above .500)\n2: Losing seasons (below .500)\n3: Seasons with equal wins and losses\n4: Seasons with 10 or more wins\n5: Undefeated seasons\n6: Bowl-eligible seasons (above or equal to .500)\n7: Quit\nPlease enter your response: ");

  scanf("%i", &response);
  switch(response){
	case 1:
		printf("The winning seasons are:\n");
		for(i=0; i<currentyear; i++){
			if(wins[i]>losses[i]){
				printf("%i\n",1900+i);
			}
		}
		break;
	case 2:
		printf("The losing seasons are:\n");
                for(i=0; i<currentyear; i++){
                        if(wins[i]<losses[i]){
                                printf("%i\n",1900+i);
                        }
                }
                break;
	case 3:
                printf("The .500 seasons (with equal wins and losses) are:\n");
                for(i=0; i<currentyear; i++){
                        if(wins[i]==losses[i]){
                                printf("%i\n",1900+i);
                        }
                }
                break;
	case 4:
		printf("The seasons the Irish got 10 or more wins are:\n");
                for(i=0; i<currentyear; i++){
                        if(wins[i]>=10){
                                printf("%i\n",1900+i);
                        }
                }
                break;
	case 5:
		printf("The undefeated seasons are:\n");
                for(i=0; i<currentyear; i++){
                        if(losses[i]==0){
                                printf("%i\n",1900+i);
                        }
                }
                break;
	case 6:
		printf("The bowl-eligible seasosn are:\n");
                for(i=0; i<currentyear; i++){
                        if(wins[i]>losses[i]){
                                printf("%i\n",1900+i);
                        }
                }
                break;
	case 7:
		y=0;
		break;
	default: 
		printf("Please enter a valid command.\n");
  }
}
return 0;
}
