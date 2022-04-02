#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int LFSR_enc(char *str){
    int16_t lfsr = 0xA331;
    int8_t bit;
    int8_t zero;

        for (int i = 0; i < strlen(str); i++){
            printf("%c", str[i]);
            for (int j = 0; j < 8; j++){
            bit = (
                ((lfsr >> 0) & 1) //16th bit
                ^ ((lfsr >> 2) & 1) //14th bit
                ^ ((lfsr >> 3) & 1) //13th bit
                ^ ((lfsr >> 5) & 1)   //11th bit
                ); 
            bit = bit << 1; //adds bit to bit shifted left
            lfsr = (lfsr >> 1); //shifts lfsr right 1 to make space for bit
            }
            //bit = bit | zero;
            bit = bit ^ str[i];
            lfsr = (bit << 8); //shifts the bits in bit to weave in with the bits shifted right in LFSR     
        }       

    return lfsr;

}


int main(){
    FILE *fp;
    int len;

    fp =  fopen("Password.txt", "r");

    char string[2048]; //initializes the place holder character array to hold file data

    fgets(string, 2048, fp); //gets the data from the file and places it in the string
    
    printf("%s\n", string); //prints the string
    
    len = strlen(string); //returns the length of the string

    printf("%d\n", len);

    int32_t lfsrVal;

    lfsrVal = LFSR_enc(string); //call to the lfsr function

    printf("\n%x", lfsrVal);

    fclose(fp); //closes the file

}

