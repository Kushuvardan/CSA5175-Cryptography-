#include <stdio.h>
#include <string.h>
#define MAX_TEXT_LENGTH 500
void decrypt(char ciphertext[]) {
    char symbols[] = "‡†*;:¶)()—]";  
    char letters[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";  
    
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        int j = 0;
        while (symbols[j] != '\0') {
            if (ciphertext[i] == symbols[j]) {
                printf("%c", letters[j]);  
                break;
            }
            j++;
        }
        
        if (ciphertext[i] == ' ') {
            printf(" ");  
        }
    }
    printf("\n");
}
int main() {
    char ciphertext[MAX_TEXT_LENGTH];

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    
    printf("\nDecrypted Text: \n");
    decrypt(ciphertext);  

    return 0;
}

