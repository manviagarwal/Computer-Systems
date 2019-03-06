#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Read file and input numbers into array
int* loadFile(FILE *myFile){
  int fileLength = 0;
  int i = 0;


  int **arr;
  arr = malloc(fileLength*sizeof(int*));

  while(!feof(myFile)){
    arr[i] = malloc(sizeof(int));
    fscanf(myFile,"%d",&arr[i]);
    //printf("Number is %d\n",arr[i]);

  }

  return arr;
}


int main(int argc, char *argv[]){
  FILE *myFile;
  char *path = argv[1];

  myFile = fopen(path,"r");
  int *numArray = loadFile(myFile);

  int index = 0;
  for(index = 0; index < 7;index++){
    printf("%d\n",numArray[index]);
  }

  fclose(myFile);
  return 0;
}
