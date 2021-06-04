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

int debug = 0; // TODO: REMOVE before submit

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

  if (debug)
    printf("Reading from file %s\n", argv[1]); // Debug

  pas = calloc(MAX_PAS_LENGTH, sizeof(int));

  // Fill up pas text portion from input file
  // EX:
  // 3 0 4         ----->        [3][0][4][2][0][1]...    etc.
  // 2 0 1
  fp = fopen(argv[1], "r");

  for (i = 0; i < MAX_PAS_LENGTH; i++)
  {
    if (debug)
      printf("i = %d\n", i);

    if (fscanf(fp, "%d", &pas[i]) == EOF)
      break;

    if (debug)
      printf("finished loop\n");
  }


  SP = i - 1;
  BP = SP + 1;

  printIntArr(pas, MAX_PAS_LENGTH); // Debug
  fclose(fp);

  printf("\n\n");
  printf("                PC   BP    SP   stack\n");
  printf("Initial values: %d    %d    %d\n\n", PC, BP, SP);
  while (PC < BP)
  {
    // Fetch Cycle
    instruction_register.OP = pas[PC];
    instruction_register.L = pas[PC + 1];
    instruction_register.M = pas[PC + 2];
    //int OP = pas[PC];
    //int L = pas[PC + 1];
    //int M = pas[PC + 2];

    if (PC / 10 == 0)
    {
      printf(" ");
    }

    //printf("%d ", PC);
    PC = PC + 3;

    if (debug)
    {
      printf("\n***beginning of entire stack***: ");
      for (i = 0; i < MAX_PAS_LENGTH - BP; i++)
      {
        printf("%d ", pas[BP + i]);
      }
      printf("***end of entire stack***\n");
    }

    // Execute Cycle
    switch(instruction_register.OP)
    {
      // LIT, pushes literal onto stack
      case 1:
        printf("%d ", PC - 3);
        printf("LIT");
        SP = SP + 1;
        pas[SP] = instruction_register.M;
        break;

      // OPR, arith. preformed using data @ top of stack
      case 2:
        printf("%d ", PC - 3);

        // RTN
        if (instruction_register.M == 0)
        {
          printf("RTN");
          SP = BP - 1;
          BP = pas[SP + 2];
          PC = pas[SP + 3];
        }

        // NEG
        else if (instruction_register.M == 1)
        {
          printf("NEG");
          pas[SP] = (pas[SP] * (-1));
        }

        // ADD
        else if (instruction_register.M == 2)
        {
          printf("ADD");
          SP = SP - 1;
          pas[SP] = pas[SP] + pas[SP + 1];
        }

        // SUB
        else if (instruction_register.M == 3)
        {
          printf("SUB");
          SP = SP - 1;
          pas[SP] = pas[SP] - pas[SP + 1];
        }

        // MUL
        else if (instruction_register.M == 4)
        {
          printf("MUL");
          SP = SP - 1;
          pas[SP] = pas[SP] * pas[SP + 1];
        }

        // DIV
        else if (instruction_register.M == 5)
        {
          printf("DIV");
          SP = SP - 1;
          pas[SP] = pas[SP] / pas[SP - 1];
        }

        // ODD
        else if (instruction_register.M == 6)
        {
          printf("ODD");
          pas[SP] = pas[SP] % 2;
        }

        // MOD
        else if (instruction_register.M == 7)
        {
          printf("MOD");
          SP = SP - 1;
          pas[SP] = pas[SP] % pas[SP + 1];
        }

        // EQL
        else if (instruction_register.M == 8)
        {
          printf("EQL");
          SP = SP - 1;
          pas[SP] = (pas[SP] == pas[SP + 1]);
        }

        // NEQ
        else if (instruction_register.M == 9)
        {
          printf("NEQ");
          SP = SP - 1;
          pas[SP] = (pas[SP] != pas[SP + 1]);
        }

        // LSS
        else if (instruction_register.M == 10)
        {
          printf("LSS");
          SP = SP - 1;
          // pas[SP] = (pas[SP] < pas[SP + 1]);
          if (pas[SP] = pas[SP] < pas[SP + 1])
            pas[SP] = 1;
          else
            pas[SP] = 0;
        }

        // LEQ
        else if (instruction_register.M == 11)
        {
          printf("LEQ");
          SP = SP - 1;
          pas[SP] = (pas[SP] <= pas[SP + 1]);
        }

        // GTR
        else if (instruction_register.M == 12)
        {
          printf("GTR");
          SP = SP - 1;
          pas[SP] = (pas[SP] > pas[SP + 1]);
        }

        // GEQ
        else if (instruction_register.M == 13)
        {
          printf("GEQ");
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
        printf("%d ", PC - 3);
        printf("LOD");
        SP = SP + 1;
        pas[SP] = pas[base(instruction_register.L) + instruction_register.M];
        break;

      // STO, store val from top of stack to an index @ offset M from L levels down
      case 4:
        printf("%d ", PC - 3);
        printf("STO");
        pas[base(instruction_register.L) + instruction_register.M] = pas[SP];
        SP = SP - 1;
        break;

      case 5:
        // CAL, calls procedure (another name for function/method) @ index M
        // Generates new activation record (???) and PC is set to M
        printf("%d ", PC - 3);
        printf("CAL");
        pas[SP + 1] = base(instruction_register.L);
        pas[SP + 2] = BP;
        pas[SP + 3] = PC;
        BP = SP + 1;
        PC = instruction_register.M;
        break;

      case 6:
        // INC, allocate M number of memory words. First 4 are reserved for:
        // Static Link, Dynamic Link, Return Address, and Parameter
        // Increment SP by M
        printf("%d ", PC - 3);
        printf("INC");
        SP = SP + instruction_register.M;
        break;

      // JMP, jump to instr
      case 7:
        printf("%d ", PC - 3);
        printf("JMP");
        PC = instruction_register.M;
        break;

        // JPC, jump to instr M if top stack val is 1
      case 8:
        printf("%d ", PC - 3);
        printf("JPC");
        if (pas[SP] == 1)
        {
          PC = instruction_register.M;
        }
        SP = SP - 1;
        break;

      case 9:
        if (instruction_register.M == 1)
        {
          // Write top stack val to screen
          printf("Output result is: %d\n", pas[SP]);
          SP = SP - 1;
          printf("%d ", PC - 3);
          printf("SYS");
        }

        else if (instruction_register.M == 2)
        {
          // Read user input & store @ top of stack
          printf("Please Enter an Integer: ");
          SP = SP + 1;
          scanf("%d", &pas[SP]);
          //printf("\n");
          printf("%d ", PC - 3);
          printf("SYS");
        }

        else if (instruction_register.M == 3)
        {
          // End program, set Halt to 0
          Halt = 0;
          printf("%d ", PC - 3);
          printf("SYS");
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

    printf("%3d%3d    ", instruction_register.L, instruction_register.M);
    printf("%4d %4d %4d   ", PC, BP, SP);

    // potential issue where SP and BP are equal so it prints nothing
    // SP starts as the index of the last M value of the last instruction,
    // while BP is the index after that. If the stack is length 1 then both
    // SP and BP hold the same index.
    if (debug)
      printf("\nSP = %d\nBP = %d\n", SP, BP);
    for (i = 0; i <= (SP - BP); i++)
    {
      printf("%d ", pas[BP + i]);
    }

    printf("\n");
  }

}
