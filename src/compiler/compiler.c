
#include <stdio.h>
#include <string.h>



void printHelp(){
    printf("crp Compiler\n");

    printf("Options: \n");
    printf(" -h, --help     Prints this help messege \n");
    printf(" -f, --file     Determines input file name \n");
    printf(" -o, --out      Determines output file name \n");
}





//reads file with numbers then makes anohter file with the numbers casted to unsighed chars
int main(int argc, char* argv[]){

    //change i dont want refs to be consts
    char *filename=0;
    char *outfilename=0;
    int printedh=0;
    
    for (int i=1; i<argc;i++){
        if( strcmp( argv[i],"--help")==0 || strcmp( argv[i],"-h")==0 ){
            printHelp();
            printedh=1;
        }

        if( strcmp( argv[i],"-f")==0 || strcmp( argv[i],"--file")==0){
            if (i+1<argc){
                filename=argv[i+1];
            }
        }

        if( strcmp( argv[i],"-o")==0 || strcmp( argv[i],"--out" )==0){
            if (i+1<argc){
                outfilename=argv[i+1];
            }
        }
    }

    if (filename==0 ||outfilename==0) {
        if (!printedh) {
            printf("invalid arguments no filename or output name spesified\n");
            printHelp();
        }
        return 1;
    }






    int nums[256];
    int numpoinr=0;


    FILE *fptr;
    fptr=fopen(filename,"r");


    char buffer[10];

    //read file
    while (fgets(buffer,10,fptr)){
        
        int num=0;
        
        int current_mul=1;

        // convert char[] into int
        for (int i=2; i>=0; i--) {
            if (buffer[i]!=10 && buffer[i]!=0 &&buffer[i]==' '){
                num += (buffer[i]-0x30)*current_mul;
                current_mul*=10;
            }
        }
        nums[numpoinr++]=num;
    }

    
    fclose(fptr);


    FILE *wfptr;

    wfptr=fopen(outfilename,"wb");

    //write nums into file
    for (int i=0; i<numpoinr;i++){
        fputc(nums[i], wfptr);
    }


    fclose(wfptr);

    
    return 0;
}


