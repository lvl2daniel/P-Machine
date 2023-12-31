// Authors: Ian Ordonez, Daniel Gonzalez (Group 18)
// Assignment: HW1 
// Class: COP 3402 Fall 0001

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 512

typedef struct instruction
{
    int opcode; // code which tells the operation to be performed
    int l;      // lexicographical level which tells the static level of the variable
    int m;      // modifier which tells the offset of the variable
} instruction;

int readFile(int inputs[ARRAY_SIZE], const char *argv);
void execute(int inputs[ARRAY_SIZE], int count);
int base(int *stack, int l, int bp);
void printStackWithAR(int* stack, int bp, int sp, int count);

int main(int argc, char **argv)
{

    // initialize variables
    int inputs[ARRAY_SIZE] = {0};
    int count;
    // printf("%s", argv[1]);
    const char *fileName = argv[1];
    // printf("%s", fileName);
    count = readFile(inputs, fileName);
    // printf("Hello World\n");
    execute(inputs, count);
    // printf("goodbye world\n");

    return 0;
}

void execute(int inputs[], int count)
{
    int pc = 0;                  // program counter
    int bp = count;              // base pointer
    int sp = count - 1;          // stack pointer
    instruction ir;              // instruction register
    int halt = 0;                // halt flag
    int stack[ARRAY_SIZE] = {0}; // stack
    printf("\t\t\tPC\t BP\t SP\t stack\n");
    printf("Initial Values:\t\t%d\t %d\t %d\t\n", pc, bp, sp);
    while (!halt)
    {
        ir.opcode = inputs[pc];
        ir.l = inputs[pc + 1];
        ir.m = inputs[pc + 2];
        pc += 3;

        switch (ir.opcode)
        {
        case 0: // RTN
            sp = bp - 1;
            pc = stack[sp + 3];
            bp = stack[sp + 2];
            printf("RTN\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
            // print the stack
            for (int i = bp; i <= sp; i++)
            {
                printf("%d ", stack[i]);
            }
            break;
        case 1: // LIT

            sp++;
            stack[sp] = ir.m;
            printf("LIT\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
            printStackWithAR(stack, bp, sp, count);
            break;
        case 2: // OPR
            sp--;
            switch (ir.m)
            {
            case 0:
                // RTN
                sp = bp - 1;
                bp = stack[sp + 2];
                pc = stack[sp + 3];
                printf("RTN\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
                // Print the stack
                for (int i = bp; i <= sp; i++)
                {
                    printf("%d ", stack[i]);
                }
                break;
            case 1:
                // ADD
                stack[sp] += stack[sp + 1];
                printf("ADD\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
                printStackWithAR(stack, bp, sp, count);
                break;
            case 2:
                // SUB
                stack[sp] -= stack[sp + 1];
                printf("SUB\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
                printStackWithAR(stack, bp, sp, count);
                break;
            case 3:
                // MUL
                stack[sp] *= stack[sp + 1];
                printf("MUL\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
                printStackWithAR(stack, bp, sp, count);
                break;
            case 4:
                // DIV
                stack[sp] /= stack[sp + 1];
                printf("DIV\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
                printStackWithAR(stack, bp, sp, count);
                break;
            case 5:
                // EQL
                stack[sp] = stack[sp] == stack[sp + 1];
                printf("EQL\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
                printStackWithAR(stack, bp, sp, count);
                break;
            case 6:
                // NEQ
                stack[sp] = stack[sp] != stack[sp + 1];
                printf("NEQ\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
                printStackWithAR(stack, bp, sp, count);
                break;
            case 7:
                // LSS
                stack[sp] = stack[sp] < stack[sp + 1];
                printf("LSS\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
                printStackWithAR(stack, bp, sp, count);
                break;
            case 8:
                // LEQ
                stack[sp] = stack[sp] <= stack[sp + 1];
                printf("LEQ\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
                printStackWithAR(stack, bp, sp, count);
                break;
            case 9:
                // GTR
                stack[sp] = stack[sp] > stack[sp + 1];
                printf("GTR\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
                printStackWithAR(stack, bp, sp, count);
                break;
            case 10:
                // GEQ
                stack[sp] = stack[sp] >= stack[sp + 1];
                printf("GEQ\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
                printStackWithAR(stack, bp, sp, count);
                break;
            }
            break;
        case 3: // LOD
            printf("LOD\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
            sp++;
            stack[sp] = stack[base(stack, ir.l, bp) + ir.m];
            printStackWithAR(stack, bp, sp, count);
            break;
        case 4: // STO
            stack[base(stack, ir.l, bp) + ir.m] = stack[sp];
            sp--;
            printf("STO\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
            printStackWithAR(stack, bp, sp, count);
            break;
        case 5: // CAL
            stack[sp + 1] = base(stack, ir.l, bp);
            stack[sp + 2] = bp;
            stack[sp + 3] = pc;
            bp = sp + 1;
            pc = ir.m;
            printf("CAL\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
            // Print stack
            for (int i = count; i <= sp; i++)
            {
                printf("%d ", stack[i]);
            }
            break;
        case 6: // INC
            sp += ir.m;
            printf("INC\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
            printStackWithAR(stack, bp, sp, count);
            break;
        case 7: // JMP
            pc = ir.m;
            printf("JMP\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
            break;
        case 8: // JPC
            if (stack[sp] == 0)
            {
                pc = ir.m;
            }
            sp--;
            printf("JPC\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
            printStackWithAR(stack, bp, sp, count);
            break;
        case 9: // SYS
            switch (ir.m)
            {
            case 1:
                // write
                printf("The output result is: %d\n", stack[sp]);
                sp--;
                printf("SYS\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
                for (int i = bp; i <= sp; i++)
                {
                    printf("%d ", stack[i]);
                }
                break;
            case 2:
                // read
                sp++;
                printf("Please enter an integer: ");
                scanf("%d", &stack[sp]);
                printf("SYS\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
                for (int i = bp; i <= sp; i++)
                {
                    printf("%d ", stack[i]);
                }
                break;
            case 3:
                // halt
                halt = 1;
                printf("SYS\t %d\t %d\t %d\t%d\t%d\t", ir.l, ir.m, pc, bp, sp);
                for (int i = bp; i <= sp; i++)
                {
                    printf("%d ", stack[i]);
                }
                break;
            }
            break;
        }
        printf("\n");
    }
}

int base(int *stack, int l, int bp)
{
    int arb;  // find base L levels down
    arb = bp; // arb = activation record base
    while (l > 0)
    {
        arb = stack[arb];
        l--;
    }
    return arb;
}

int readFile(int inputs[ARRAY_SIZE], const char *argv)
{
    int count = 0;
    if (argv == NULL)
        argv = "input.txt";
    FILE *fp = fopen(argv, "r");
    if (fp == NULL)
    {
        perror("Error opening input file");
        exit(1);
    }

    // printf("Check 1\n");
    // Read instructions from the file into the input array
    while (fscanf(fp, "%d", &inputs[count]) != EOF)
    {
        count++;
    }

    fclose(fp);
    return count;
}

void printStackWithAR(int* stack, int bp, int sp, int count){
    for (int i = count; i <= sp; i++)
    {
        printf("%d ", stack[i]);
        if (i + 1 == bp)
        {
            printf("| ");
        }
    }
}