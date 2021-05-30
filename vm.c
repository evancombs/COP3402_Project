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
	while (L > 0)     //find base L levels down
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
  IR instruction_register;

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
    instruction_register.OP = pas[PC];
    instruction_register.L = pas[PC + 1];
    instruction_register.M = pas[PC + 2];
    //int OP = pas[PC];
    //int L = pas[PC + 1];
    //int M = pas[PC + 2];

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
        else if (M == 1)
        {
          pas[SP] = pas[SP] * -1;
        }

        // ADD
        else if (M == 2)
        {
          SP = SP - 1;
          pas[SP] = pas[SP] + pas[SP + 1];
        }

        // MUL
        else if (M == 3)
        {
          SP = SP - 1;
          pas[SP] = pas[SP] + pas[SP + 1];
        }

        // DIV
        else if (M == 4)
        {
          SP = SP - 1;
          pas[SP] = pas[SP] + pas[SP + 1];
        }

        // DIV
        else if (M == 5)
        {
          SP = SP - 1;
          pas[SP] = pas[SP] / pas[SP - 1];
        }

        // ODD
        else if (M == 6)
        {
          pas[SP] = pas[SP] % 2;
        }

        // MOD
        else if (M == 7)
        {
          SP = SP - 1;
          pas[SP] = pas[SP] % pas[SP + 1];
        }

        // EQL
        else if (M == 8)
        {
          SP = SP - 1;
          pas[SP] = (pas[SP] == pas[SP + 1]);
        }

        // NEQ
        else if (M == 9)
        {
          SP = SP - 1;
          pas[SP] = (pas[SP] != pas[SP + 1]);
        }

        // LSS
        else if (M == 10)
        {
          SP = SP - 1;
          pas[SP] = (pas[SP] < pas[SP + 1]);
        }

        // LEQ
        else if (M == 11)
        {
          SP = SP - 1;
          pas[SP] = (pas[SP] <= pas[SP + 1]);
        }

        // GTR
        else if (M == 12)
        {
          SP = SP - 1;
          pas[SP] = (pas[SP] > pas[SP + 1]);
        }

        // GEQ
        else if (M == 13)
        {
          SP = SP - 1;
          pas[SP] = (pas[SP] >= pas[SP + 1]);
        }

        else
        {
          Halt = 1;
        }

        break;

      // LOD, load val to top of stack from offset M of L levels down
      case 3:
        sp = sp - 1;
        pas[sp] = pas[base(L) + M];
        break;

      // STO, store val from top of stack to an index @ offset M from L levels down
      case 4:
        pas[base(L) + M] = pas[sp];
        sp = sp - 1;
        break;

      case 5:
        // CAL, calls procedure (another name for function/method) @ index M
        // Generates new activation record (???) and PC is set to M

        pas[sp + 1] = base(L);
        pas[sp + 2] = BP;
        pas[sp + 3] = PC;
        BP = sp + 1;
        PC = M;
        break;

      case 6:
        // INC, allocate M number of memory words. First 4 are reserved for:
        // Static Link, Dynamic Link, Return Address, and Parameter
        // Increment SP by M

        sp = sp + M;
        break;

      // JMP, jump to instr
      case 7:
        PC = M;
        break;

        // JPC, jump to instr M if top stack val is 1
      case 8:
        if (pas[sp] == 1)
        {
          PC = M;
          sp = sp - 1;
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

        else if (M == 2)
        {
          // Read user input & store @ top of stack
          printf("Please Enter and Integer:")
          sp = sp + 1;
          scanf("%d", pas[sp]);
        }

        else if (M == 3)
        {
          // End program, set Halt to 0
          Halt = 0;
          return 0;
        }

        else
        {
          Halt = 1;
        }

        break;

        default:
          Halt = 1;
          break;
    }
  }

}
