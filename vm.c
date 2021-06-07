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
int STACK_LEN = 0;

int is_first_inc = 1;
int instr_end = 0;
int Halt = 0;
int* pas;

// From HW1 Instructions, Appendix D
int base(int L)
{
	int arb = BP;
	while (L > 0)
	{
		arb = pas[arb];
		L--;
	}
	return arb;
}


int main(int argc, char** argv)
{
  FILE *fp;
  int i,j;
  IR instruction_register;

  pas = calloc(MAX_PAS_LENGTH, sizeof(int));

  fp = fopen(argv[1], "r");

  // Reads instructions from file into pas array
  for (i = 0; i < MAX_PAS_LENGTH; i++)
  {
    if (fscanf(fp, "%d", &pas[i]) == EOF)
      break;
  }

  instr_end = i;
  SP = i - 1;
  BP = SP + 1;

  fclose(fp);
  printf("                  PC   BP    SP   stack\n");
  printf("Initial values:  %2d    %2d    %2d\n\n", PC, BP, SP);
  while (PC < instr_end)
  {
    // Fetch Cycle
    instruction_register.OP = pas[PC];
    instruction_register.L = pas[PC + 1];
    instruction_register.M = pas[PC + 2];

    PC = PC + 3;

    // Execute Cycle
    switch(instruction_register.OP)
    {
      // LIT, pushes literal onto stack
      case 1:
        printf("%2d ", PC - 3);
        printf("LIT");
        SP = SP + 1;
        pas[SP] = instruction_register.M;
        break;

      // OPR, arithmetic performed using data from top of stack
      case 2:
        printf("%2d ", PC - 3);

        // RTN
        if (instruction_register.M == 0)
        {
          printf("RTN");
          SP = BP - 1;
          BP = pas[SP + 2];
          PC = pas[SP + 3];
        }

        // NEG, negates value at top of stack
        else if (instruction_register.M == 1)
        {
          printf("NEG");
          pas[SP] = (pas[SP] * (-1));
        }

        // ADD, adds top and 2nd to top values on stack
        else if (instruction_register.M == 2)
        {
          printf("ADD");
          SP = SP - 1;
          pas[SP] = pas[SP] + pas[SP + 1];
        }

        // SUB, subtracts top and 2nd to top values on stack
        else if (instruction_register.M == 3)
        {
          printf("SUB");
          SP = SP - 1;
          pas[SP] = pas[SP] - pas[SP + 1];
        }

        // MUL, multiplies top and 2nd to top values on stack
        else if (instruction_register.M == 4)
        {
          printf("MUL");
          SP = SP - 1;
          pas[SP] = pas[SP] * pas[SP + 1];
        }

        // DIV, divides 2nd to top value from the top value in the stack
        else if (instruction_register.M == 5)
        {
          printf("DIV");
          SP = SP - 1;
          pas[SP] = pas[SP] / pas[SP + 1];
        }

        // ODD, if top of stack is odd, it is replaced with a 1
        else if (instruction_register.M == 6)
        {
          printf("ODD");
          pas[SP] = pas[SP] % 2;
        }

        // MOD, modulo the 2nd to top value by the top value of stack
        else if (instruction_register.M == 7)
        {
          printf("MOD");
          SP = SP - 1;
          pas[SP] = pas[SP] % pas[SP + 1];
        }

        // EQL, if top and 2nd to top values in stack are equal, top is replaced with a 0
        else if (instruction_register.M == 8)
        {
          printf("EQL");
          SP = SP - 1;
          pas[SP] = !(pas[SP] == pas[SP + 1]);
        }

        // NEQ, if top and 2nd to top values in stack are NOT equal, top is replaced with a 0
        else if (instruction_register.M == 9)
        {
          printf("NEQ");
          SP = SP - 1;
          pas[SP] = !(pas[SP] != pas[SP + 1]);
        }

        // LSS, if 2nd to top stack value is less than top of stack value, top of stack is replaced with a 0
        else if (instruction_register.M == 10)
        {
          printf("LSS");
          SP = SP - 1;
          pas[SP] = !(pas[SP] < pas[SP + 1]);
        }

        // LEQ, if 2nd to top stack value is less than or equal to top of stack value, top of stack is replaced with a 0
        else if (instruction_register.M == 11)
        {
          printf("LEQ");
          SP = SP - 1;
          pas[SP] = !(pas[SP] <= pas[SP + 1]);
        }

        // GTR, if 2nd to top stack value is greater than the top of stack value, top of stack is replaced with a 0
        else if (instruction_register.M == 12)
        {
          printf("GTR");
          SP = SP - 1;
          pas[SP] = !(pas[SP] > pas[SP + 1]);
        }

        // GEQ, if 2nd to top stack value is greater than or equal to top of stack value, top of stack is replaced with a 0
        else if (instruction_register.M == 13)
        {
          printf("GEQ");
          SP = SP - 1;
          pas[SP] = !(pas[SP] >= pas[SP + 1]);
        }

        // Represents and invalid arithmetic  instruction
        else
        {
          Halt = 1;
        }

        break;

      // LOD, load value to top of stack from offset M of L levels down
      case 3:
        printf("%2d ", PC - 3);
        printf("LOD");
        SP = SP + 1;
        pas[SP] = pas[base(instruction_register.L) + instruction_register.M];
        break;

      // STO, store val from top of stack to an index at offset M from L levels down
      case 4:
        printf("%2d ", PC - 3);
        printf("STO");
        pas[base(instruction_register.L) + instruction_register.M] = pas[SP];
        SP = SP - 1;
        break;

      // CAL, calls procedure at index M
      // Generates new activation record and PC is set to M
      case 5:
        printf("%2d ", PC - 3);
        printf("CAL");
        pas[SP + 1] = base(instruction_register.L);
        pas[SP + 2] = BP;
        pas[SP + 3] = PC;
        BP = SP + 1;
        PC = instruction_register.M;
        break;

      // INC, allocate M number of memory words. First 4 are reserved for:
      // Static Link, Dynamic Link, Return Address, and Parameter
      // Increments SP by M
      case 6:
        if (is_first_inc)
        {
          STACK_LEN = instruction_register.M;
          is_first_inc = 0;
        }
        printf("%2d ", PC - 3);
        printf("INC");
        SP = SP + instruction_register.M;
        break;

      // JMP, jumps to instruction at index specified by M
      case 7:
        printf("%2d ", PC - 3);
        printf("JMP");
        PC = instruction_register.M;
        break;

      // JPC, if the top of the stack is equal to 1, jumps to instruction at index specified by M
      case 8:
        printf("%2d ", PC - 3);
        printf("JPC");

        if (pas[SP] == 1)
        {
          PC = instruction_register.M;
        }
        SP = SP - 1;
        break;

      // System Calls
      case 9:
        // Write top of stack value to screen
        if (instruction_register.M == 1)
        {
          printf("Output result is: %d\n", pas[SP]);
          SP = SP - 1;
          printf("%2d ", PC - 3);
          printf("SYS");
        }

        // Read user input & store at the top of the stack
        else if (instruction_register.M == 2)
        {
          printf("Please Enter an Integer:\n");
          SP = SP + 1;
          scanf("%d", &pas[SP]);
          //printf("\n");
          printf("%2d ", PC - 3);
          printf("SYS");
        }

        // End program, set Halt to 0
        else if (instruction_register.M == 3)
        {
          Halt = 0;
          printf("%2d ", PC - 3);
          printf("SYS");
        }

        // Represents an invalid instruction
        else
        {
          Halt = 1;
        }

        break;

        // Represents an invalid SYS instruction
        default:
          Halt = 1;
          break;
    }

    // Prints the L and M fields of the current instruction,
    // along with the current Program Counter, Base Pointer,
    // and Stack Pointer
    printf("%3d%3d    ", instruction_register.L, instruction_register.M);
    printf("%4d %4d %4d   ", PC, BP, SP);

    // Prints out the stack and following activation records,
    // separated by the appropriate pipe characters
    for (i = instr_end; i <= SP; i++)
    {
      printf("%d ", pas[i]);

      if (i == instr_end + STACK_LEN -  1)
      {
        printf(" | ");
      }

      else if (i >= instr_end + STACK_LEN -  1 && i < BP)
      {
        if ((i - STACK_LEN - 2) % 3 == 0)
        {
          printf(" | ");
        }
      }
    }

    printf("\n");
  }

  return 0;
}
