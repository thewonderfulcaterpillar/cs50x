#include <cs50.h>
#include <stdio.h>
#include <math.h>
int checkLen(long x);
int first2Letter(long x);
bool checkSum(long x);
int main(void)
{
    long x = get_long ("Enter your credit card number:\n");
    int xLen = checkLen(x);
    int xStart = first2Letter(x);
    string cardType = "INVALID\n";
    if (xLen==15 && (xStart==37 || xStart ==34)){
        cardType = "AMEX\n";
    }
    else if (xLen==16 && xStart>=51 && xStart <=55){
        cardType = "MASTERCARD\n";
    }
    else if ((xLen==13 || xLen==16) && (xStart>=40 && xStart <=49)){
        cardType = "VISA\n";
    }
    else{
        printf ("INVALID\n");
        return 0;
    }
    bool y = checkSum(x);
    if (y){
        printf("%s",cardType);
        return 0;
    }
    else{
        printf ("INVALID\n");
        return 0;
    }

}

int checkLen(long x){
    int stringLen=0;
    while (x>=1){
        x=x/10;
        stringLen++;
    }
    return stringLen;
}

int first2Letter(long x){
    while (x>=100){
        x=x/10;
    }
    return (int) x;
}

bool checkSum(long x){
    bool odd=true;
    int xSum=0;
    while (x>=1){
        if (odd){
            xSum+=x%10;
        }
        else{
            int y=(x%10)*2;
            xSum += (int) y/10;
            xSum += y%10;
        }
        x=x/10;
        x=(long) floor(x);
        odd=!odd;
    }

    return xSum%10==0;
}