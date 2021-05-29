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




void main(int argc, char** argv)
{
  FILE *fp;
  int i;

  printf("Reading from file %s\n", argv[1]); // Debug

  int* pas = malloc(sizeof(int) * MAX_PAS_LENGTH);

  // Fill up pas text portion from input file
  // EX:
  // 3 0 4         ----->        [3][0][4][2][0][1]...    etc.
  // 2 0 1
  fp = fopen(argv[1], "r");

  for (i = 0; i < MAX_PAS_LENGTH; i++)
  {
    if (fscanf(fp, "%d", &pas[i]) == EOF)
      break;
  }

  printIntArr(pas, MAX_PAS_LENGTH); // Debug
  fclose(fp);
