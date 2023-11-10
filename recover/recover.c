#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;
int main(int argc, char *argv[])
{

    if (argc!=2){
        printf("%s\n","Please input file directory");
        return 1;
    }

        FILE *file=fopen(argv[1],"r");
        if (file==NULL){
            printf("INVALID FILE!");
            return 2;}
        BYTE array[512];
        char *filename=malloc(8 * sizeof(char));
        FILE* imagefile=NULL;
        int z=0;

        while (fread(array,sizeof(char),512,file)){
             if (array[0] == 0xff && array[1] == 0xd8 && array[2] == 0xff && (array[3] & 0xf0) == 0xe0){
                 sprintf(filename,"%03i.jpg",z);
                 imagefile=fopen(filename,"w");
                 z++;
             }
            if (imagefile!=NULL){
                  fwrite(array,sizeof(char),512,imagefile);
                 }

             }
            fclose(imagefile);
            fclose(file);
            free(filename);
            return 0;

}



