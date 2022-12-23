// Omar Alshafei
// 11/28/2022

// This program encryps a plaintext file using the Vigenere cipher

// Library function
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function prototypes
char* scanTextFiles(FILE * file, int num);
char* encryptText(char *plainText, char *key);
void displayText(char* key, char* plainText, char* cipherText);
void freeMemory(char* key, char* plainText, char* cipherText);


// The main function opens the text files and then calls all other files
int main(int argc, char **argv){
    
	FILE *plainFile, *keyFile;
	char *plainText, *cipherText, *key;
    
	// Open the key file
    keyFile = fopen(argv[1], "r");
	// Open the plaintext file
	plainFile = fopen(argv[2], "r");
    
    // Call the scanTextFiles function with key
	key = scanTextFiles(keyFile, 1);
    // Call the scanTextFiles function with the plain text
    plainText = scanTextFiles(plainFile, 2);
    // Call encryptText function with the plain text and the key in order to encrypt the plain text
    cipherText = encryptText(plainText, key);
    
    // Call the displayText function to print out the key, plaintext, and ciphertext
	displayText(key, plainText, cipherText);
	
    // Call the freeMemory function to free the dynamically stored memory of the key, plaintext, and ciphertext
    freeMemory(key, plainText, cipherText);

	return 0;
}

// This function scans in the key file and the plaintext file then returns them to main
char* scanTextFiles(FILE * file, int num){
	// dynamically allocate memory for the text
    char* text = malloc(sizeof(char) * 513);    
    
	char character;
    int i = 0, max = 512;
	
    // Loop while file has not ended and index i is less then the max
	while (fscanf(file,"%c",&character) != EOF && i < max) {
		if(isalpha(character)){
            // converts uppercase character to lowercase and then places character into text
			text[i] = tolower(character);
			i++;
		}
	}
	// Expression for key
	if (num == 1){
        // Adds null character to end of the array
		text[i] = '\0';
	}
    // Expression for plaintext
	if (num == 2) {
	    for (i; i < max; i++){
            // Pads the end of the array with x
			text[i] = 'x';
		}
		text[max] = '\0';
	}
	
	return text;
}

// This function encrypts the plaintext using the key and returns the ciphertext
char * encryptText(char *plainText, char *key){
    
    // dynamically allocate memory for the ciphertext
	char* cipherText = malloc(sizeof(char) * 513);
	int i;
    // Loop for the length of the plain text	
	for (i = 0; i < strlen(plainText); i++) {
        // Encrypting the key against the plaintext
		int x = (plainText[i] - 97 + key[i % strlen(key)] - 97) % 26  + 97;
		// Filling in the ciphertext
		cipherText[i] = x;
	}
	// Adds null character to the end of the ciphertext
	cipherText[i] = '\0';
	return cipherText;
}

// This function displays the key, plaintext, and ciphertext
void displayText(char* key, char* plainText, char* cipherText){
        
        printf("\n\nVigenere Key:\n");
    // Loop to print the key
    for (int i = 0; i < strlen(key); i++){
		if (i % 80 == 0)
			printf("\n");
		    printf("%c",key[i]);
	}
        printf("\n\n\nPlaintext:\n");
    // Loop to print the plaintext
    for (int i = 0; i < strlen(plainText); i++){
		if (i % 80 == 0)
			printf("\n");
		    printf("%c",plainText[i]);
	}
        printf("\n\n\nCiphertext:\n");
    // Loop to print the ciphertext    
    for (int i = 0; i < strlen(cipherText); i++){
		if (i % 80 == 0)
			printf("\n");
		    printf("%c",cipherText[i]);
	}
}

// This function frees all the dynamically stored memory
void freeMemory(char* key, char* plainText, char* cipherText){
    // Frees key
    free(key);
    // Frees plaintext
	free(plainText);
    // Frees ciphertext
	free(cipherText);
}
