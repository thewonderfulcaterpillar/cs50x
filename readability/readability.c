#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int strLen=0;

int main(void)
{
    string x = get_string("Please input a string for the readability test:");
    strLen=strlen(x);
    int letters = count_letters(x);
    int words = count_words(x);
    int sentences=count_sentences(x);
    float L = (float) letters / (float) words * 100;
    float S = (float) sentences /(float)  words * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    if (index<1)
    {
        printf("Before Grade 1\n");
    }
    else if (index>16)
    {
        printf("Grade 16+\n");
    }
    else{
        int grade = (int) round(index);
        printf("Grade %i\n",grade);
    }
    return 0;
}
//can do it in one pass, but problem statement requires 2 functions to be defined
int count_letters(string text){
    int letterCount=0;
    for (int i = 0; i < strLen; i++){
        int c = tolower(text[i]) - 97;
        if (c<26 && c>=0){
            letterCount++;
        }

    }
    return letterCount;
}
int count_words(string text){
    int wordCount=1;
    for (int i = 0; i < strLen; i++){
        if (text[i]==' '){
            wordCount++;
        }

    }
    return wordCount;
}

int count_sentences(string text){
    int sentenceCount=0;
    for (int i = 0; i < strLen; i++){
        if (text[i]=='!' || text[i]=='.' || text[i]=='?'){
            sentenceCount++;
        }

    }
    return sentenceCount;
}