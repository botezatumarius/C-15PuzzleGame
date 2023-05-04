#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int moveNumber=0, savingMoves[1000][17];
void delay(int milliseconds)
{
    long pause;
    clock_t now,then;

    pause = milliseconds*(CLOCKS_PER_SEC/1000);
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}

int checkforwin(int table1[15]){
    int win=0;
    for (int i=0;i<16;i++)
        if (table1[i]==i+1)
            win++;
    if (win==15){
        return 1;
    } else return 0;

}

void printtable(int table[15]){
    system("clear");
    if (checkforwin(table)){
        printf("");
        exit;
    } else {
        printf("--------------------------------------------------------------------------------\nBack to menu:m        Restart:r        Undo:u        Redo:y        Save:o\n--------------------------------------------------------------------------------");
        for (int i=0;i<16;i++){
            if (i%4==0)
                printf("\n");
            if ((table[i]/10)<1)
                printf("  %d",table[i]);
            else
                printf(" %d",table[i]);

        }
    }
}

int checkSolvability(int table[15],int blankSpace){
    int odd=0,invCount=0;
    float q=blankSpace/4;
    if (q<1||(q<3&&q>=2))
        odd=0;
    else odd=1;

    for (int i=0;i<15;i++){
        for (int j=i+1;j<16;j++){
            if (table[i]!=0&&table[j]!=0&&table[i]>table[j])
                invCount++;
        }
    }

    if ((odd==0&&invCount%2!=0)||(odd==1&&invCount%2==0))
        return 1;
    else return 0;
}

void savefile(int puzzleArray2[15],int locationSpace2){
    FILE *f;
    f=fopen("savefile.txt","w");
    if(f == NULL)
    {
        /* File not created hence exit */
        printf("Unable to create file.\n");
        exit(EXIT_FAILURE);
    }
    for (int i=0;i<16;i++){
        putw(puzzleArray2[i],f);
    }
    putw(locationSpace2,f);

    fclose(f);
    printf("File created and saved successfully. :) \n");
}


void startmoves(int puzzleArray1[15],int locationSpace1){
    int x=0,puzzleArray2[15];
    char wayToMove;
   
    //for (int i=0;i<1000;i++)
        //for (int j=0;j<17;j++)
            //savingMoves[i][j]=0;

        printtable(puzzleArray1);

        //start moving around numbers

        while (checkforwin(puzzleArray1)!=1){

            //save state
            for (int i=0;i<16;i++)
                savingMoves[moveNumber][i]=puzzleArray1[i];
            savingMoves[moveNumber][16]=locationSpace1;
            moveNumber++;

            printf("\nw(up),s(down),a(left),d(right):");
            scanf(" %c",&wayToMove);
            switch (wayToMove)
            {
            case 'w':
                if (locationSpace1>3){
                    for (int i=moveNumber;i<1000;i++)
                        for (int j=0;j<17;j++)
                            savingMoves[i][j]=0;
                    x=puzzleArray1[locationSpace1];
                    puzzleArray1[locationSpace1]=puzzleArray1[locationSpace1-4];
                    puzzleArray1[locationSpace1-4]=x;
                    locationSpace1=locationSpace1-4;
                    printtable(puzzleArray1);
                } else printtable(puzzleArray1);
                break;
            case 's':
                if (locationSpace1<12){
                    for (int i=moveNumber;i<1000;i++)
                        for (int j=0;j<17;j++)
                            savingMoves[i][j]=0;
                    x=puzzleArray1[locationSpace1];
                    puzzleArray1[locationSpace1]=puzzleArray1[locationSpace1+4];
                    puzzleArray1[locationSpace1+4]=x;
                    locationSpace1=locationSpace1+4;
                    printtable(puzzleArray1);
                } else printtable(puzzleArray1);
                break;
            case 'd':
                if (locationSpace1!=3&&locationSpace1!=7&&locationSpace1!=11&&locationSpace1!=15){
                    for (int i=moveNumber;i<1000;i++)
                        for (int j=0;j<17;j++)
                            savingMoves[i][j]=0;
                    x=puzzleArray1[locationSpace1];
                    puzzleArray1[locationSpace1]=puzzleArray1[locationSpace1+1];
                    puzzleArray1[locationSpace1+1]=x;
                    locationSpace1=locationSpace1+1;
                    printtable(puzzleArray1);
                } else printtable(puzzleArray1);
                break;
            case 'a':
                if (locationSpace1!=0&&locationSpace1!=4&&locationSpace1!=8&&locationSpace1!=12){
                    for (int i=moveNumber;i<1000;i++)
                        for (int j=0;j<17;j++)
                            savingMoves[i][j]=0;
                    x=puzzleArray1[locationSpace1];
                    puzzleArray1[locationSpace1]=puzzleArray1[locationSpace1-1];
                    puzzleArray1[locationSpace1-1]=x;
                    locationSpace1=locationSpace1-1;
                    printtable(puzzleArray1);
                } else printtable(puzzleArray1);
                break;
            case 'm':
                moveNumber=0;
                main();
                break;
            case 'r':
                for (int i=1;i<1000;i++)
                    for (int j=0;j<17;j++)
                        savingMoves[i][j]=0;
                moveNumber=0;
                for (int i=0;i<16;i++)
                    puzzleArray2[i]=savingMoves[0][i];
                startmoves(puzzleArray2,savingMoves[0][16]);   
                break;
            case 'o':
                savefile(puzzleArray1,locationSpace1);
                break;
            case 'u':
                moveNumber--;
                if (moveNumber>0){
                    moveNumber--;
                    for (int i=0;i<16;i++)
                        puzzleArray2[i]=savingMoves[moveNumber][i];
                        startmoves(puzzleArray2,savingMoves[moveNumber][16]);
                }
                break;
            case 'y':
                if (savingMoves[moveNumber][0]!=0||savingMoves[moveNumber][1]!=0){
                    for (int i=0;i<16;i++)
                        puzzleArray2[i]=savingMoves[moveNumber][i];
                        startmoves(puzzleArray2,savingMoves[moveNumber][16]);
                } else moveNumber--;
                break;
            default:
                printtable(puzzleArray1);
        
            }
        }

        //player won

        int finish=0;
        char input;
        while (finish==0){
            printf("\033[93m");
            printf("\nYOU WOOOOOOOOOOOOOOOOOOOOOONNNNNNN!!!!!!!!!!!!!!!!!!  :D :D :D ( ͡❛ ͜ʖ ͡❛) :D :D :D\n\n\nm=Main Menu , e = Exit, anything else = replay the colors\n");
            delay(250);
            system("clear");
            printf("\033[92m");
            printf("\nYOU WOOOOOOOOOOOOOOOOOOOOOONNNNNNN!!!!!!!!!!!!!!!!!!  :D :D :D ( ͡❛ ͜ʖ ͡❛) :D :D :D\n\n\nm=Main Menu , e = Exit, anything else = replay the colors\n");
            delay(250);
            system("clear");
            printf("\033[96m");
            printf("\nYOU WOOOOOOOOOOOOOOOOOOOOOONNNNNNN!!!!!!!!!!!!!!!!!!  :D :D :D ( ͡❛ ͜ʖ ͡❛) :D :D :D\n\n\nm=Main Menu , e = Exit, anything else = replay the colors\n");
            delay(250);
            system("clear");
            printf("\033[91m");
            printf("\nYOU WOOOOOOOOOOOOOOOOOOOOOONNNNNNN!!!!!!!!!!!!!!!!!!  :D :D :D ( ͡❛ ͜ʖ ͡❛) :D :D :D\n\n\nm=Main Menu , e = Exit, anything else = replay the colors\n");
            delay(250);
            system("clear");
            printf("\033[94m");
            printf("\nYOU WOOOOOOOOOOOOOOOOOOOOOONNNNNNN!!!!!!!!!!!!!!!!!!  :D :D :D ( ͡❛ ͜ʖ ͡❛) :D :D :D\n\n\nm=Main Menu , e = Exit, anything else = replay the colors\n");
            delay(250);
            scanf("%c",&input);
            switch (input)
            {
            case 'm':
                mainmenu();
                finish=1;
                break;
            case 'e':
                printf("good bye :(\n");
                delay(2000);
                finish=1;
                break;
            }
            system("clear");
        }

}

void startgame(){

    //create the board

    int puzzleArray[15],number,x=0,f=time(NULL);

    for (int i=0;i<16;i++)
        puzzleArray[i]=0;

    system("clear");
    srand(f++);
    int locationSpace = rand() % 16;

    for (int i=0;i<16;i++){
        x=0;
        if (i!=locationSpace){
            while (x==0){
                srand(f++);
                int number = rand() % 16;
                for (int j=0;j<=i;j++){
                    if (puzzleArray[j]==number)
                        break;
                    else if (j==i) {
                        puzzleArray[i]=number;
                        x=1;
                    }

                }
            }
        }
    }
    if (checkSolvability(puzzleArray,locationSpace)){
        startmoves(puzzleArray,locationSpace);
    } else startgame();
}

void loadgame(){
    FILE *f;
    int num,i=0,loadedArray[17],emptyLocation;
    // open file for reading
  f = fopen("savefile.txt", "r");
  
  // display numbers
  printf("\nNumbers:\n");
  while ( (num = getw(f)) != EOF ) {
    if (i==16){
        emptyLocation=num;
    } else {
    loadedArray[i]=num;
    i++;
    }
  }
  
  // close connection
  fclose(f);
  startmoves(loadedArray,emptyLocation);
}

void mainmenu(){
    for (int i=0;i<1000;i++)
        for (int j=0;j<17;j++)
            savingMoves[i][j]=0;
    printf("\33[107m");
    printf("\33[91m");
    system("clear");
    int a;
    printf("                                     15 PUZZLE GAME!!\n");
    printf("                                         MENU\n");
    printf("1 - start the game\n2 - load game from a save file\n");
    while (a<1||a>1){
        scanf("%d",&a);
        switch (a)
        {
        case 1:
            startgame();
            break;
        case 2:
            loadgame();
            break;
        
        default:
            printf("Please input a proper number");
        }
    }

}

int main(){
    system("clear");
    mainmenu();
    return 0;
}