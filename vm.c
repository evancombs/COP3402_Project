// COP 3402 Summer A, 2021
// HW1 VM Assignments
// Evan Combs and Dylan McKim

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_PAS_LENGTH 500
// BP = base pointer
// SP = stack pointer
// PC = program counter
// IR = instruction register


// Temp Debug Functions
void printIntArr(int* arr, int len)
{
  int i;

  for (i = 0; i < len; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return;
}

// Takes in an input file name and an empty text array, and fills
// in each instruction from the input file
// EX:
// 3 0 4         ----->        [3][0][4][2][0][1]...    etc.
// 2 0 1
void read(char* inputFile, char* text)
{

}




// Takes in the name of the input file, the position to read from, and
void fetch(char* input, int PC, char** IR)
{

}

void execute()
{

}

void main(int argc, char** argv)
{
  FILE *fp;
  int i, j;

  // char* text = malloc(sizeof(int) * 450);
  printf("Reading from file %s\n", argv[1]);

  int* pas = malloc(sizeof(int) * MAX_PAS_LENGTH);

  int len;
  // int* text2 = calloc(450, sizeof(int));

  fp = fopen(argv[1], "r");

  for (i = 0; i < MAX_PAS_LENGTH; i++)
  {
    if (fscanf(fp, "%d", &pas[i]) == EOF)
      break;
  }

  printIntArr(pas, MAX_PAS_LENGTH);
  fclose(fp);

  // read(argv[1], text);
}
