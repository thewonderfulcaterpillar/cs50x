#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


int main(int argc, string argv[])
{
    if (argc!=2){
        printf("Please enter key to map from! Exiting... Only 2 arguments allowed! Exiting...\n");
        return 1;
    }
    string userKey=argv[1];
    int alphabetSet[26];
    if (strlen(userKey)!=26){
        printf("Your key is of length %lu",strlen(userKey));
        printf("Key must be 26 characters long! Exiting...\n");
        return 1;
    }
    for (int i = 0; i < 26; i++){
        if (!isalpha(userKey[i])){
        printf("Key must only contain alphabets a-z A-Z! Exiting...\n");
        return 1;
        }
        else{
            char c=tolower(userKey[i]);
            if (alphabetSet[(int) c - 97]==1){
                printf("Key has duplicate keys! Exiting...\n");
                return 1;
            }
            alphabetSet[(int) c - 97]=1;
        }
    }
    string x = get_string("plaintext:");
    for (int i = 0; i<strlen(x); i++ ){
        if (isalpha(x[i])){
            char c=tolower(x[i]);
            if (isupper(x[i])){
                x[i]=toupper(userKey[(int) c - 97]);
            }
            else{
                x[i]=tolower(userKey[(int) c - 97]);
            }
        }
    }
    printf("ciphertext:%s",x);
    printf("\n");
    return 0;

}