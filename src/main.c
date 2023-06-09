#include <stdio.h>
#include <string.h>

#define SIZE 256

struct Program{
    int instructionPointer;
    int freePointer;
    unsigned char program[SIZE];
};


//modifies input 
void readFileToBuffer(struct Program* program, char* filename){
    //read file 
    //whatever into the thing
    FILE *fptr;
    fptr=fopen(filename,"r");
    char thing[2];

    int index=0;

    while (fgets(thing,2,fptr)){
        //printf("%s\n",thing);
        program->program[index++]=thing[0];
    }

    //debug printing
    /*
    printf("read this file\n");
    for (int i=0; i<index; i++) {
        printf("%i\n ",program->program[i] );
    }
     * */

}


int checkBit(int byte, int position){
    return byte & (1<<position);
}


//modifies input program
void interpretCommand(struct Program *program ,int command){ 


    //if the first bit is 0 or 1 if first is 1 were incrementing somehting
    if(! checkBit(command, 8-1)) {

        //print or command instruction
        if (!checkBit(command, 8-2)){
            
            if(command==0){
                //command is 0 we dont print anythign
            }else{
                //print command
                int * pointer ;
                if (checkBit(command, 8-3)){
                    pointer=&program->instructionPointer;
                }else{
                    pointer=&program->freePointer;
                }

                int printable=0;
                
                //if print pointer or value
                if (checkBit(command, 8-5)){
                    printable=*pointer;
                }else{
                    printable=program->program[*pointer];
                }

                //if print in char or int
                if (checkBit(command, 8-4)){
                    printf("%i",printable); 
                }else{
                    printf("%c",printable); 
                }

            }


        }else{
            //command instruction logic
            int * pointer ;
            if (checkBit(command, 8-3)){
                pointer=&program->instructionPointer;
            }else{
                pointer=&program->freePointer;
            }
            int amount= command & 0b00011111;
            //if amount is zero we run the command once
            amount++;

            for(int i=0;i<amount; i++){
                interpretCommand(program,program->program[*pointer]);
            }
        }


        //incrementation logic
    }else{
        //we are incrementing pointer or value
        int * pointer ;
        //the amount is in the last 5 bits so we only take those
        int amount= command & 0b00011111;
        //if amount is zero we increment by one
        amount++;

        //check if we are incrementing instruction pointer or freepointer
        if (checkBit(command, 8-3)){
            pointer=&program->instructionPointer;
        }else{
            pointer=&program->freePointer;
        }

        //if we are incrementing pointer or value at pointer
        if (!checkBit(command, 8-2)){
            //printf("increment pointer %i\n",command);
            *pointer+=amount;
        }else{
            //printf("increment value  %i\n",command);
            program->program[*pointer]+=amount;

        }

    }

}


void printHelp(){
    printf("Crp Interpreter\n");

    printf("Options: \n");
    printf(" -h, --help     Prints this help messege \n");
    printf(" -f, --file     Determines input file name \n");
}





int main(int argc, char * argv[]){

    char *filename=0;
    int printedh=0;
    
    for (int i=1; i<argc;i++){
        if( strcmp( argv[i],"--help")==0 || strcmp( argv[i],"-h")==0 ){
            printHelp();
            printedh=1;
        }

        if( strcmp( argv[i],"-f")==0 || strcmp( argv[i],"--file")==0){
            if (i+1<argc){
                filename=argv[i+1];
            }else{
                printf("invalid args\n");
                return 1;
            }
        }

    }

    if (filename==0 ) {
        if (!printedh) {
            printf("invalid arguments no filename spesified\n");
            printHelp();
        }
        return 1;
    }



    struct Program program;

    //reset array 
    for(int i=0;i<SIZE; i++){
        program.program[i]=0;
    }
    
    //initialize pointers at 0
    program.instructionPointer=0;
    program.freePointer=0;

    readFileToBuffer(&program, filename);

    //interpret program
    while(program.instructionPointer <= 256){
        interpretCommand(&program,program.program[program.instructionPointer++]);
    }

    
    //debug printing
    /*
    printf("program ended with state :\n");
    for(int i=0;i<SIZE; i++){
        printf("%i:%i\n", program.program[i],i);
    }
    printf("\n");
     * */

}
