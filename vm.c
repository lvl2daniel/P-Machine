#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ARRAY_SIZE 512

typedef struct instruction{
    int opcode; // code which tells the operation to be performed
    int l; // lexicographical level which tells the static level of the variable
    int m; // modifier which tells the offset of the variable
    }instruction;

void readFile(int inputs[][3]);
void execute();




int main(){

    //initialize variables
    int inputs[ARRAY_SIZE][3];
    readFile(inputs);
    printf("Hello World\n");
    execute(inputs);
    printf("goodbye world\n");


    return 0;
}

void execute(instruction inputs[]){

        int pc = 0; //program counter
        int bp = 0; //base pointer
        int sp = -1; //stack pointer
        instruction ir; //instruction register
        int halt = 0; //halt flag
        int stack[ ARRAY_SIZE ]; //stack
        printf("%d, %d, %d, %d, %d\n", pc, bp, sp, ir.opcode, halt);

        while(!halt){
            ir = inputs[pc];
            pc++;
            printf("no halt yet\n");
            printf("PC IS %d\n", pc);

            switch(ir.opcode){
                case 0: //RTN
                    sp = bp - 1;
                    pc = stack[sp + 3];
                    bp = stack[sp + 2];
                    break;
                case 1: //LIT
                    sp++;
                    stack[sp] = ir.m;
                    break;
                case 2: //OPR
                    sp--;
                    switch(ir.m){
                        case 0:
                            //RTN
                            sp = bp - 1;
                            bp = stack[sp + 2];
                            pc = stack[sp + 3];
                        case 1:
                            //ADD
                            stack[sp] += stack[sp+1];
                            break;
                        case 2:
                            //SUB
                            stack[sp] -= stack[sp+1];
                            break;
                        case 3:
                            //MUL
                            stack[sp] *= stack[sp+1];
                            break;
                        case 4:
                            //DIV
                            stack[sp] /= stack[sp+1];
                            break;
                        case 5:
                            //EQL
                            stack[sp] = stack[sp] == stack[sp+1];
                            break;
                        case 6:
                            //NEQ
                            stack[sp] = stack[sp] != stack[sp+1];
                            break;
                        case 7:
                            //LSS
                            stack[sp] = stack[sp] < stack[sp+1];
                            break;
                        case 8:
                            //LEQ
                            stack[sp] = stack[sp] <= stack[sp+1];
                            break;
                        case 9:
                            //GTR
                            stack[sp] = stack[sp] > stack[sp+1];
                            break;
                        case 10:
                            //GEQ
                            stack[sp] = stack[sp] >= stack[sp+1];
                            break;
                    }
                    break;
                case 3: //LOD
                    sp++;
                    stack[sp] = stack[base(stack,ir.l, bp) + ir.m];
                    break;
                case 4: //STO
                    stack[base(stack,ir.l, bp) + ir.m] = stack[sp];
                    sp--;
                    break;
                case 5: //CAL
                    stack[sp+1] = base(stack, ir.l, bp);
                    stack[sp+2] = bp;
                    stack[sp+3] = pc;
                    bp = sp + 1;
                    pc = ir.m;
                    break;
                case 6: //INC
                    sp += ir.m;
                    break;
                case 7: //JMP
                    pc = ir.m;
                    break;
                case 8: //JPC
                    if(stack[sp] == 0){
                        pc = ir.m;
                    }
                    sp--;
                    break;
                case 9: //SYS
                    switch(ir.m){
                        case 1:
                            //write
                            printf("%d\n", stack[sp]);
                            sp--;
                            break;
                        case 2:
                            //read
                            sp++;
                            scanf("%d", &stack[sp]);
                            break;
                        case 3:
                            //halt
                            halt = 1;
                            break;
                    }
                    break;

            }


        }
}

int base(int *stack, int l, int bp){
    int arb; //find base L levels down
    arb = bp; //arb = activation record base
    while(l > 0){
        arb = stack[arb];
        l--;
    }
    return arb;
}

void readFile(int inputs[][3]){

    //read input file

    //THIS IS BROKEN ... D:

    int i = 0;
    FILE *fp = fopen("input.txt", "r");
    printf("hello file\n");
    //read file into array
    while(!feof(fp)){

        printf("%d, %d, %d, %d,\n", inputs[i][0], inputs[i][1], inputs[i][2], i);
        fscanf(fp, "%d %d %d", &inputs[i][0], &inputs[i][1], &inputs[i][2]);
        i++;
        if(inputs[i][0] == 9 && inputs[i][3] == 3) break;
    }

    fclose(fp);
    return;
}
