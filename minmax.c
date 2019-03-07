#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Read file and input numbers into array
int* loadFile(FILE *myFile){
  int fileLength = 0;
  int i = 0;


  int *arr;
  arr = malloc(fileLength*sizeof(int*));

  while(!feof(myFile)){
    arr[i] = malloc(sizeof(int));
    fscanf(myFile,"%d",&arr[i]);
    //printf("Number %d in %d\n",arr[i],i);
    i = i + 1;
  }

  return arr;
}

//Find min,max,sum
int* findValues(int *arr){
  int values[3] = {0,0,0};
  int min = arr[0];
  int max = arr[0];
  int sum = 0;
  int arrSize;

  arrSize = sizeof(arr)/sizeof(int);
  int i;

  for(i = 0; i< arrSize; i = i+1){
    printf("%d\n",arr[i]);
    if(min > arr[i]){
      min = arr[i];
      values[0] = min;
      printf("Min: %d\n", values[0]);
    }
    if(max < arr[i]){
      max = arr[i];
      values[1] = max;
      printf("Max: %d\n", values[1]);
    }
    sum = sum + arr[i];
    values[2] = sum;
    printf("Sum: %d\n", values[2]);
  }

  // printf("\nMinimum is %d\n", min);
  // printf("\nMaximum is %d\n", max);
  // printf("\n Sum is %d\n", sum);

  return values;
}


int main(int argc, char *argv[]){
  FILE *myFile;
  char *path = argv[1];

  myFile = fopen(path,"r");
  int *numArray = loadFile(myFile);

  int *min = findValues(numArray);

  int index = 0;
  for(index = 0; index < 3; index = index + 1){
    printf("%d\n", min[index]);
  }



  fclose(myFile);
  return 0;
}
