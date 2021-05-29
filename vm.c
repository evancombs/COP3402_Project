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

// Registers
typedef struct IR
{
  int OP;
  int L;
  int M;
} IR;

// Global
int SP = 0;
int BP = 0;
int PC = 0;
int Halt = 0;

int* pas;
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

// From HW1 Instructions, Appendix D
int base(int L)
{
	int arb = BP;	// arb = activation record base
	while ( L > 0)     //find base L levels down
	{
		arb = pas[arb];
		L--;
	}
	return arb;
}


void main(int argc, char** argv)
{
  FILE *fp;
  int i;


  printf("Reading from file %s\n", argv[1]); // Debug

  pas = calloc(MAX_PAS_LENGTH, sizeof(int));

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

  SP = i;
  BP = SP + 1;

  printIntArr(pas, MAX_PAS_LENGTH); // Debug
  fclose(fp);

  while (PC < BP)
  {
    // Fetch Cycle
    int OP = pas[PC];
    int L = pas[PC + 1];
    int M = pas[PC + 2];

    PC = PC + 3;

    // Execute Cycle
    switch(OP)
    {
      // LIT, pushes literal onto stack
      case 1:
        sp = sp + 1;
        pas[sp] = M;
        break;

      // OPR, arith. preformed using data @ top of stack
      case 2:

        // RTN
        if (M == 0)
        {
          sp = bp - 1;
          bp = pas[sp + 2];
          pc = pas[sp + 3];
        }

        // NEG
        if (M == 1)
        {
          pas[SP] = pas[SP] * -1;
        }

        // ADD
        if (M == 2)
        {
          SP = SP - 1;
          pas[SP] = pas[SP] + pas[SP + 1];
        }

        // MUL
        if (M == 3)
        {
          SP = SP - 1;
          pas[SP] = pas[SP] + pas[SP + 1];
        }

        // DIV
        if (M == 4)
        {
          SP = SP - 1;
          pas[SP] = pas[SP] + pas[SP + 1];
        }

        // DIV
        if (M == 5)
        {
          SP = SP - 1;
          pas[SP] = pas[SP] / pas[SP - 1];
        }

        // ODD
        if (M == 6)
        {
          pas[SP] = pas[SP] % 2;
        }

        // MOD
        if (M == 7)
        {
          SP = SP - 1;
          pas[SP] = pas[SP] % pas[SP + 1];
        }

        // EQL
        if (M == 8)
        {
          SP = SP - 1;
          pas[SP] = (pas[SP] == pas[SP + 1]);
        }

        // NEQ
        if (M == 9)
        {
          SP = SP - 1;
          pas[SP] = (pas[SP] != pas[SP + 1]);
        }

        // LSS
        if (M == 10)
        {
          SP = SP - 1;
          pas[SP] = pas[SP] < pas[SP + 1];
        }

        // LEQ
        if (M == 11)
        {
          SP = SP - 1;
          pas[SP] = (pas[SP] <= pas[SP + 1]);
        }

        // GTR
        if (M == 12)
        {
          SP = SP - 1;
          pas[SP] = (pas[SP] > pas[SP + 1]);
        }

        // GEQ
        if (M == 13)
        {
          SP = SP - 1;
          pas[SP] = (pas[SP] >= pas[SP + 1]);
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

      // JMP, jump to instr
      case 7:
        PC = M;
        break;

        // JPC, jump to instr M if top stack val is 1
      case 8:
        if (BP == 1)
        {
          PC = M;
        }
        break;

      case 9:
        if (M == 1)
        {
          // Write top stack val to screen
          printf("Top of Stack Value:")
          printf("%d", pas[sp]);
          sp = sp - 1;
        }

        if (M == 2)
        {
          // Read user input & store @ top of stack
          printf("Please Enter and Integer:")
          sp = sp + 1;
          scanf("%d", pas[sp]);
        }

        if (M == 3)
        {
          // End program, set Halt to 0
          Halt = 0;
          return 0;
        }

        break;
    }
  }

}
