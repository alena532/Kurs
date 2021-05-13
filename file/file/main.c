
#include <stdio.h>
#include <stdlib.h>
int main(int argc, const char * argv[]) {
    char a[80];
    FILE* file;
     file=fopen("test.txt","r");
    if(!file){
        printf("Mistake");
        exit(1);
    }
    fgets(a,80,file);
  //  printf("%s",a);
    
    return 0;
}
