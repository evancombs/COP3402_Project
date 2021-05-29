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

  int* pas = malloc(sizeof(int) * MAX_PAS_LENGTH);

  read(argv[1], text);


    while (instr_index < BP)
    {
      int OP = IR[index];
      int L = IR[index + 1];
      int M = IR[index + 2];

      switch(OP)
      {
        case 1:
          // LIT, push literal onto stack
          break;

        case 2:
          // OPR, arith. preformed using data @ top of stack
          if (M == 0)
          {

          }

          // NEG
          if (M == 1)
          {
            PAS[sp] = PAS[sp] * -1;
          }

          // ADD
          if (M == 2)
          {
            sp = sp - 1;
            pas[sp] = pas[sp] + pas[sp + 1];
          }

          // MUL
          if (M == 3)
          {
            sp = sp - 1;
            pas[sp] = pas[sp] + pas[sp + 1];
          }

          // DIV
          if (M == 4)
          {
            sp = sp - 1;
            pas[sp] = pas[sp] + pas[sp + 1];
          }

          // DIV
          if (M == 5)
          {
            sp = sp - 1;
            pas[sp] = pas[sp] / pas[sp - 1];
          }

          // ODD
          if (M == 6)
          {
            pas[sp] = pas[sp] % 2;
          }

          // MOD
          if (M == 7)
          {
            sp = sp - 1;
            pas[sp] = pas[sp] % pas[sp + 1];
          }

          // EQL
          if (M == 8)
          {
            sp = sp - 1;
            pas[sp] = (pas[sp] == pas[sp + 1]);
          }

          // NEQ
          if (M == 9)
          {
            sp = sp - 1;
            pas[sp] = (pas[sp] != pas[sp + 1]);
          }

          // LSS
          if (M == 10)
          {
            sp = sp - 1;
            pas[sp] = pas[sp] < pas[sp + 1];
          }

          // LEQ
          if (M == 11)
          {
            sp = sp - 1;
            pas[sp] = (pas[sp] <= pas[sp + 1]);
          }

          // GTR
          if (M == 12)
          {
            sp = sp - 1;
            pas[sp] = (pas[sp] > pas[sp + 1]);
          }

          // GEQ
          if (M == 13)
          {
            sp = sp - 1;
            pas[sp] = (pas[sp] >= pas[sp + 1]);
          }


          break;

        case 3:
          // LOD, load val to top of stack from offset M of L levels down(???)
          break;

        case 4:
          // STO, store val from top of stack to an index @ offset M from L levels down (???)
          break;

        case 5:
          // CAL, calls procedure (another name for function/method) @ index M
          // Generates new activation record (???) and PC is set to M
          break;

        case 6:
          // INC, allocate M number of memory words. First 4 are reserved for:
          // Static Link, Dynamic Link, Return Address, and Parameter
          // Increment SP by M
          break;

        case 7:
          // JMP, jump to instr
          // PC set to M
          break;

        case 8:
          // JPC, jump to instr M if top stack val is 1
          // PC set to M
          break;

        case 9:
          if (M == 1)
          {
            // Write top stack val to screen
          }

          if (M == 2)
          {
            // Read user input & store @ top of stack
          }

          if (M == 3)
          {
            // End program, set Halt to 0
          }
      }

}
