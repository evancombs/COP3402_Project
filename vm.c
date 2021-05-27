// COP 3402 Summer A, 2021
// HW1 VM Assignments
// Evan Combs and Dylan McKim

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  FILE *fp;
  int i, j;
  char instruction[3];
  int len;
  int* text2 = calloc(450, sizeof(int));

  fp = fopen(inputFile, "r");

  for (i = 0; i < 450; i++)
  {
    fscanf(fp, "%d", &text2[i]);
  }

  printIntArr(text2, 450);
  fclose(fp);
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
  char* text = malloc(sizeof(int) * 450);
  printf("Reading from file %s\n", argv[1]);
  read(argv[1], text);
}
