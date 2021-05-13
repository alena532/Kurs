#include <stdio.h>
#include <stdlib.h>
#include "main.h"
char water ='.';
void setVertically(char field[10][10],int x,int y,int deck)
{
    int i;
    int j=x;
    for(i=y;i<y+deck;i++){
        field[i][j]='x';
    }
}
void setHorizontal(char field[10][10],int x,int y,int deck)
{
    int i=y;
    int j;
    for(j=x;j<x+deck;j++){
        field[i][j]='x';
    }
}
int vertically(char field[10][10],int x,int y,int deck)
{
    if(y+deck-1>9){
        return 0;
    }
    int j=x;
    int i;
    if(y==0){
        for( i=y;i<y+deck+1;i++){
            if(j==0){
                if(field[i][j]!= water||field[i][j+1]!=water){
                    return 0;
                }
            }else if(j==9){
                if(field[i][j]!=water||field[i][j-1]!=water){
                    return 0;
                }
            }else{
                if(field[i][j]!=water||field[i][j-1]!=water||field[i][j+1]!=water){
                
                    return 0;
                }
            }
        }
    }else if(y+deck-1==9){
        for( i=y-1;i<y+deck;i++){
            if(j==0){
                if(field[i][j]!=water||field[i][j+1]!=water){
                    return 0;
                }
            }else if(j==9){
                if(field[i][j]!=water||field[i][j-1]!=water){
                    return 0;
                }
            }else{
                if(field[i][j]!=water||field[i][j-1]!=water||field[i][j+1]!=water){
                    return 0;
                }
            }
        }
    }else{
        for(i=y-1;i<y+deck+1;i++){
            if(j==0){
                if(field[i][j]!=water||field[i][j+1]!=water){
                    return 0;
                }
            }else if(j==9){
                if(field[i][j]!=water||field[i][j-1]!=water){
                    return 0;
                }
            }else{
                if(field[i][j]!=water||field[i][j-1]!=water||field[i][j+1]!=water){
                    return 0;
                }
            }
        }
    }
    return 1;
}
int horizontal(char field[10][10],int x,int y,int deck)
{
    if(x+deck-1>9){
        return 0;
    }
    int i=y;
    int j;
    if(x==0){
        for( j=x;j<x+deck+1;j++){
            if(i==0){
                if(field[i][j]!=water||field[i+1][j]!=water){
                    return 0;
                }
            }else if(i==9){
                if  (field[i][j]!=water||field[i-1][j]!=water){
                    return 0;
                }
            }else{
                if(field[i][j]!=water||field[i-1][j]!=water||field[i+1][j]!=water){
                    return 0;
                }
            }
        }
    }else if(x+deck-1==9){
        for( j=x-1;j<x+deck;j++){
            if(i==0){
                if(field[i][j]!=water||field[i+1][j]!=water){
                    return 0;
                }
            }else if(i==9){
                if  (field[i][j]!=water||field[i-1][j]!=water){
                    return 0;
                }
            }else{
                if(field[i][j]!=water||field[i-1][j]!=water||field[i+1][j]!=water){
                    return 0;
                }
            }
        }
    }else{
        for( j=x-1;j<x+deck+1;j++){
            if(i==0){
                if(field[i][j]!=water||field[i+1][j]!=water){
                    return 0;
                }
            }else if(i==9){
                if  (field[i][j]!=water||field[i-1][j]!=water){
                    return 0;
                }
            }else{
                if(field[i][j]!=water||field[i-1][j]!=water||field[i+1][j]!=water){
                    return 0;
                }
            }
        }
    }
    return 1;
}
int main(int argc, const char * argv[]) {
    int sum=0;
    char field[10][10];
    int amount[4];
    int i,j;
    for(i=0;i<4;i++){
        amount[i]=4-i;
        sum+=amount[i];
    }
    for( i=0;i<10;i++){
        for( j=0;j<10;j++){
            field[i][j]=water;
        }
    }
    for( i=0;i<10;i++){
        for( j=0;j<10;j++){
            printf("%c",field[i][j]);
        }
        printf("\n");
    }
    while(sum!=0){
        int direction=rand()%2;
        int x=rand()%10;
        int y=rand()%10;
        int deck;
        int index;
        for( index=3;index>=0;index--){
            if(amount[index]!=0){
                deck=index+1;
                --amount[index];
                sum--;
                break;
            }
        }
        switch(direction){
            case 0:
                if(  vertically(field,x,y,deck)==0){
                    ++amount[index];
                    sum++;
                    continue;
                }
                setVertically(field,x,y,deck);
                break;
            case 1:
                if(horizontal(field,x,y,deck)==0){
                    ++amount[index];
                    sum++;
                    continue;
                }
                    setHorizontal(field,x,y,deck);
        }
    }
    printf("\n");
        for( i=0;i<10;i++){
            for( j=0;j<10;j++){
                printf("%c",field[i][j]);
            }
            printf("\n");
        }
    return 0;
}


