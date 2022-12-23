// Omar Alshafei
// 10/12/2022

// This program calculates an 8, 16, or 32 bit checksum on an ASCII input file

// Library functions
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLEN 1024

// This function calculates and returns a 32 bit checksum
unsigned long int checkSum_32bit(char *arr){
    unsigned long int checkSum = 0;

    int countChars = strlen(arr);
    unsigned long int val;

    // pad with X
    while((countChars % 4) != 0)
        arr[countChars++] = 'X';

    arr[countChars] = '\0';
    // calculates 32 bit checksum 
    for(int i = 0; i < countChars; i += 4){
        val = (arr[i] << 24) + (arr[i + 1] << 16) + (arr[i + 2] << 8) + arr[i + 3];
        checkSum += val;
    }
    // %= 2^32
    checkSum %= 4294967296;
    // returns checksum
    return checkSum;
}

// This function calculates and returns a 16 bit checksum
unsigned long int checkSum_16bit(char *arr){
    unsigned long int checkSum = 0;

    int countChars = strlen(arr);
    unsigned long int val;
    
    // pad with X
    if((countChars % 2) != 0){
        arr[countChars++] = 'X';
        arr[countChars] = '\0';
    }
    // calculates 16 bit checksum 
    for(int i = 0; i < countChars; i += 2){
        val = (arr[i] << 8) + arr[i + 1];
        checkSum += val;
    }
    // %= 2^16
    checkSum %= 65536;
    // returns the checksum
    return checkSum;
}

// This function calculates and returns a 16 bit checksum
unsigned long int checkSum_8bit(char *arr){
    
    unsigned long int checkSum = 0;
    int i = 0;
    // calculates 8 bit checksum 
    while(arr[i] != '\0'){
        checkSum += arr[i++];
    }
    // %= 2^8
    checkSum %= 256;
    // returns the checksum
    return checkSum;
}

// Main function
int main(int argc, char *argv[]){
    
    FILE *ifp;
    FILE *ofp;
    char arr[MAXLEN] = {0};
    // variable for checksum size (8 bit, 16 bit, 32 bit)
    int csSIZE;
    // variable to count the number of characters
    int characterCount = 0;
    unsigned long int checksum;
    
    // if statement to check the number of arguments within the command line
    if(argc != 3)
        return 1;
    else{
        // convert string to int
        csSIZE = atoi(argv[2]);
        
        if(csSIZE == 8 || csSIZE == 16 || csSIZE == 32){
            ifp = fopen(argv[1], "r");
            // if statement if file is NULL
            if(ifp == NULL){
            printf("File unable to open\n");
            return(1);
            }
            else {
            ofp = fopen("out.txt", "w");
            
            // scans in a line of text and checks to see if it is valid
            if(fgets(arr, MAXLEN - 1, ifp) == NULL){
                return 1;
            }
                // this switch calls checkSum functions to calculate the checksum
            switch(csSIZE){
                case 8:
                checksum = checkSum_8bit(arr);
                break;
                case 16:
                checksum = checkSum_16bit(arr);
                break;
                case 32:
                checksum = checkSum_32bit(arr);
                break;
                } // end of switch

            characterCount = strlen(arr);

            for(int i = 0; i < characterCount; i++){
                // if statement to allow a new line to be printed after 80 characters
                if(i % 80 == 0){
                printf("\n");
                fprintf(ofp, "\n");
                }
                printf("%c", arr[i]);  
                fprintf(ofp, "%c", arr[i]); 
            }
            printf("\n");
            fprintf(ofp, "\n");
            
            printf("%2d bit checksum is %8lx for all %4d chars\n", csSIZE, checksum, characterCount);
            fprintf(ofp, "%2d bit checksum is %8lx for all %4d chars\n", csSIZE, checksum, characterCount);

            fclose(ifp);
            fclose(ofp);
            }
        }
        else{
            printf("Valid checksum checkSumSizes are 8, 16, or 32\n");
            fprintf(stderr,"Valid checksum checkSumSizes are 8, 16, or 32\n");
        }
    }
    return 0;
}
