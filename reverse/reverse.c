#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc!=3){
        printf("Usage: ./reverse input.wav output.wav");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE* input = fopen(argv[1],"r");
    if (input==NULL){
        return 1;
    }

    // Read header
    // TODO #3
    WAVHEADER header ;
    fread(&header,sizeof(WAVHEADER),1,input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header)==1){
        return 1;
    }
    // Open output file for writing
    // TODO #5
    FILE* output = fopen(argv[2],"w");
    if (output==NULL){
        return 1;
    }
    // Write header to file
    // TODO #6
    fwrite(&header,sizeof(WAVHEADER),1,output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int blockSize=get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    fseek(input,0,SEEK_END);
    long audio = ftell(input)-sizeof(WAVHEADER);
    long blocks = (int)audio/blockSize-1;
    unsigned char buffer[blockSize];

    while (blocks>=0){
        fseek(input,blocks*blockSize+sizeof(WAVHEADER),SEEK_SET);
        blocks-=1;
        fread(&buffer,blockSize,1,input);
        fwrite(&buffer,blockSize,1,output);
    }
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    if (header.format[0]=='W'&&header.format[1]=='A'&&header.format[2]=='V'&&header.format[3]=='E'){
        return 0;
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    return (header.numChannels*(header.bitsPerSample/8));
}
